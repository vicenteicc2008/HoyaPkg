#include "QcSecProtocolsLocatorSecLib.h"
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryMapHelperLib.h>
#include <Library/PlatformHobs.h>
#include <Library/PlatformMemoryMapLib.h>
#include <Library/SecProtocolFinderLib.h>

/**
 * Find the buffer to the header of XBLCore.te
 *
 * @param TEInfo provide filePath, will also set TEBuffer in it.
 * @return EFI_STATUS EFI_SUCCESS if found, EFI_NOT_FOUND if not found.
 */
EFI_STATUS FindTeAddr(TE_INFO_STRUCT *TEInfo)
{
  ARM_MEMORY_REGION_DESCRIPTOR_EX PreFD  = {0};
  EFI_STATUS                      Status = EFI_SUCCESS;

  // Get Previous UEFI FD Address
  Status = LocateMemoryMapAreaByName("FD Reserved I", &PreFD);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "Failed to locate \"FD Reserved I\", search \"UEFI FD\" instead.\n"));
    Status = LocateMemoryMapAreaByName("UEFI FD", &PreFD);
    if (EFI_ERROR(Status)) {
      DEBUG((DEBUG_ERROR, "Failed to find \"UEFI FD\"\n"));
      return Status;
    }
  }

  // Find Signature 0x565A 'VZ' And Arch 0x64AA 'd'
  PreFD.Address += 0x1000; // Add 0x1000 here to skip useless data
  for (UINT64 i = 0; i < PreFD.Length; i += 4) {
    if (*(UINT32 *)(PreFD.Address + i) == 0xAA645A56) {
      // Store Address
      TEInfo->TEBuffer = (VOID *)(i + PreFD.Address);
      break;
    }
  }

  if (TEInfo->TEBuffer == 0)
    DEBUG((DEBUG_ERROR, "XBLCore.te not found\n"));

  // Reach end of header
  TEInfo->programBuffer =
      TEInfo->TEBuffer + sizeof(EFI_TE_IMAGE_HEADER) +
      EFI_IMAGE_SIZEOF_SECTION_HEADER * TEInfo->teHeader->NumberOfSections;

  // Jump over ALIGN
  while (*(UINT32 *)TEInfo->programBuffer == 0x0)
    TEInfo->programBuffer += 4;

// Print Header information
#if 0
  DEBUG(
      (DEBUG_WARN,
       "Signature              0x%08X\n"
       "Machine                0x%08X\n"
       "NumberOfSections       0x%08X\n"
       "Subsystem              0x%08X\n",
       TEInfo->teHeader->Signature, TEInfo->teHeader->Machine,
       TEInfo->teHeader->NumberOfSections, TEInfo->teHeader->Subsystem));

  DEBUG(
      (DEBUG_WARN,
       "StrippedSize           0x%08X\n"
       "AddressOfEntryPoint    0x%08X\n"
       "BaseOfCode             0x%08X\n"
       "ImageBase              0x%08lX\n"
       "Program offset:        0x%08lX\n",
       TEInfo->teHeader->StrippedSize, TEInfo->teHeader->AddressOfEntryPoint,
       TEInfo->teHeader->BaseOfCode, TEInfo->teHeader->ImageBase,
       TEInfo->programBuffer - TEInfo->TEBuffer));
#endif
  return Status;
}

/**
 * @param TEInfo TE information struct.
 * @param KeyGuid is the buffer need to find in buffer.
 * @retval offset of guid in buffer.
 **/
UINTN find_guid_in_buffer(TE_INFO_STRUCT *TEInfo, GUID *KeyGuid)
{
  for (UINTN i = 0; i <= TEInfo->teSize - 16; i++) {

    if (CompareMem(TEInfo->programBuffer + i, KeyGuid, 16) == 0) {
      return i;
    }
  }
  return -EFI_NOT_FOUND; // Not found
}

BOOLEAN validate_adrp(INST *inst)
{
  // Store Values by macros
  inst->adrp.op1   = ADRP_OP1(inst->val);
  inst->adrp.op2   = ADRP_OP2(inst->val);
  inst->adrp.Rd    = ADRP_RD(inst->val);
  inst->adrp.immhi = ADRP_IMMHI(inst->val);
  inst->adrp.immlo = ADRP_IMMLO(inst->val);
  return (inst->adrp.op1 == 1 && inst->adrp.op2 == 16 && inst->adrp.Rd <= 30);
}

BOOLEAN validate_add(INST *inst)
{
  // Store Values by macros
  inst->add.op1   = ADD_OP1(inst->val);
  inst->add.op2   = ADD_OP2(inst->val);
  inst->add.Rd    = ADD_RD(inst->val);
  inst->add.Rn    = ADD_RN(inst->val);
  inst->add.imm12 = ADD_IMM12(inst->val);
  inst->add.s     = ADD_S(inst->val);
  inst->add.sf    = ADD_SF(inst->val);
  inst->add.sh    = ADD_SH(inst->val);
  return (inst->add.op1 == 0 && inst->add.s == 0 && inst->add.op2 == 34);
}

VOID parse_adrp(INST *inst, UINT32 offset)
{
  // Store immediate number
  inst->adrp.imm = (inst->adrp.immhi << 2 | inst->adrp.immlo) << 12;
  // Store PC and Register(after executing adrp) address
  inst->adrp.pc               = offset;
  inst->adrp.RdAfterExecution = ((inst->adrp.pc >> 12) << 12) + inst->adrp.imm;
};

UINT64 find_protocol_scheduler(TE_INFO_STRUCT *Binary, GUID *KeyGuid)
{
  // Find Guid Offset
  UINT32 guid_offset = find_guid_in_buffer(Binary, KeyGuid);
  if (guid_offset < 0) {
    DEBUG((DEBUG_WARN, "Schduler guid not found in buffer\n"));
    return -EFI_NOT_FOUND;
  }

  // Find all ADRP function
  for (UINT32 offset = 0;
       offset < Binary->fileSize - 8 - sizeof(EFI_TE_IMAGE_HEADER);
       offset += 4) {

    INST instruction = {.val = *(UINT32 *)(Binary->TEBuffer + offset)};
    // Check adrp
    if (validate_adrp(&instruction)) {
      // Found a valid adrp instruction
      parse_adrp(&instruction, offset);
      // Check if there is an add function at next next instruction
      INST nnInst = {.val = *(UINT32 *)(Binary->TEBuffer + offset + 8)};
      if (validate_add(&nnInst)) {

        // Get target address
        UINT32 target_address =
            instruction.adrp.RdAfterExecution + nnInst.add.imm12;
        if (target_address == guid_offset) {
          // Get the adrp instruction before current adrp.
          INST bInst = {.val = *(UINT32 *)(Binary->TEBuffer + offset - 4)};
          // Check adrp
          if (validate_adrp(&bInst)) {
            // Found a valid adrp instruction
            parse_adrp(&bInst, offset);

            // Check Add
            INST nInst = {.val = *(UINT32 *)(Binary->TEBuffer + offset + 4)};
            if (validate_add(&nInst)) {
              // Get target address
              return bInst.adrp.RdAfterExecution + nInst.add.imm12 +
                     Binary->teHeader->BaseOfCode + Binary->teHeader->ImageBase;
            }
          }
        }
      }
    }
  }
  DEBUG((DEBUG_WARN, "Scheduler Protocol Address not found\n"));
  return -EFI_NOT_FOUND;
}

UINT64 find_protocol_xbldt(TE_INFO_STRUCT *Binary, GUID *KeyGuid)
{
  // Find Guid Offset
  UINT32 guid_offset = find_guid_in_buffer(Binary, KeyGuid);
  if (guid_offset == -1) {
    DEBUG((DEBUG_WARN, "XBLDT guid not found in buffer\n"));
    return -EFI_NOT_FOUND;
  }

  // Find all ADRP function
  for (UINT32 offset = 0;
       offset < Binary->fileSize - 8 - sizeof(EFI_TE_IMAGE_HEADER);
       offset += 4) {
    INST instruction = {.val = *(UINT32 *)(Binary->TEBuffer + offset)};

    // Check adrp
    if (validate_adrp(&instruction)) {
      // Found a valid adrp instruction
      parse_adrp(&instruction, offset);

      // Check if there is an add function at next instruction
      INST nInst = {.val = *(UINT32 *)(Binary->TEBuffer + offset + 4)};
      if (validate_add(&nInst)) {
        // Get target address
        UINT32 target_address =
            instruction.adrp.RdAfterExecution + nInst.add.imm12;
        if (target_address == guid_offset) {
          // Get the adrp instruction at 3 instructions before current one.
          INST bbbInst = {.val = *(UINT32 *)(Binary->TEBuffer + offset - 12)};
          // Check adrp
          if (validate_adrp(&bbbInst)) {
            // Found a valid adrp instruction
            parse_adrp(&bbbInst, offset);

            // Check Add
            INST bbInst = {.val = *(UINT32 *)(Binary->TEBuffer + offset - 8)};
            if (validate_add(&bbInst)) {
              // Get target address
              return bbbInst.adrp.RdAfterExecution + bbInst.add.imm12 +
                     Binary->teHeader->BaseOfCode + Binary->teHeader->ImageBase;
            }
          }
        }
      }
    }
  }
  DEBUG((DEBUG_WARN, "XBLDT Protocol Address not found\n"));
  return -EFI_NOT_FOUND;
}

// Declare TE info struct
STATIC UINTN ScheIntrAddr = 0;
STATIC UINTN SecDTOpsAddr = 0;

VOID InitProtocolFinder(
    IN EFI_PHYSICAL_ADDRESS *ScheAddr, IN EFI_PHYSICAL_ADDRESS *XBLDTOpsAddr)
{
  // Do search only once
  if (ScheIntrAddr != 0 || SecDTOpsAddr != 0) {
    if (NULL != ScheAddr)
      *ScheAddr = ScheIntrAddr;
    if (NULL != XBLDTOpsAddr)
      *XBLDTOpsAddr = SecDTOpsAddr;
    return;
  }

  TE_INFO_STRUCT CoreTE = {0};

  // Find and fill TE info in memory
  if(EFI_ERROR(FindTeAddr(&CoreTE))){
    DEBUG((DEBUG_ERROR, "Failed to find TE address\n"));
    return;
  };

  // Find Scheduler address
  if (NULL != ScheAddr) {
    ScheIntrAddr = find_protocol_scheduler(&CoreTE, &gEfiSchedIntfGuid);
    ASSERT(ScheIntrAddr > 0);
    // Fill caller's address
    *ScheAddr = ScheIntrAddr;
  }

  // Find XBLDT address
  if (NULL != XBLDTOpsAddr) {
    SecDTOpsAddr = find_protocol_xbldt(&CoreTE, &gEfiSecDtbGuid);
    ASSERT(SecDTOpsAddr > 0);
    // Fill caller's address
    *XBLDTOpsAddr = SecDTOpsAddr;
  }
}
