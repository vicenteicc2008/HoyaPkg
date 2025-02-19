#ifndef _QC_SEC_PROTOCOLS_LOCATOR_SEC_LIB_H_
#define _QC_SEC_PROTOCOLS_LOCATOR_SEC_LIB_H_
#include <IndustryStandard/PeImage.h>
#include <Library/BaseMemoryLib.h>
#include <Uefi.h>

/* ADRP Instruction */
typedef struct arm64_adrp {
  UINT32 Val;
  // instruction instructure
  UINT8  Rd;
  UINT32 immhi;
  UINT8  op2;
  UINT8  immlo;
  UINT8  op1;
  // extra data
  UINT32 imm;
  UINT64 pc;
  UINT64 RdAfterExecution;
} Arm64Adrp;

/* ADD Instruction */
typedef struct arm64_add {
  UINT32 Val;
  // instruction instructure
  UINT8  Rd;
  UINT8  Rn;
  UINT16 imm12;
  UINT8  sh;
  UINT8  op2;
  UINT8  s;
  UINT8  op1;
  UINT8  sf;
  // extra data
  UINT32 imm;
  UINT64 pc;
  UINT64 RdAfterExecution;
} Arm64Add;

/* MASKs to get args value in adrp */
#define ADRP_RD(Ins) ((Ins) & 0x1F)
#define ADRP_IMMHI(Ins) (((Ins) >> 5) & 0x7FFFF)
#define ADRP_OP2(Ins) (((Ins) >> 24) & 0x1F)
#define ADRP_IMMLO(Ins) (((Ins) >> 29) & 0x3)
#define ADRP_OP1(Ins) (((Ins) >> 31) & 0x1)

/* MASKs to get args value in ADD */
#define ADD_RD(Ins) ((Ins) & 0x1F)
#define ADD_RN(Ins) (((Ins) >> 5) & 0x1F)
#define ADD_IMM12(Ins) (((Ins) >> 10) & 0xFFF)
#define ADD_SH(Ins) (((Ins) >> 22) & 0x1)
#define ADD_OP2(Ins) (((Ins) >> 23) & 0x3F)
#define ADD_S(Ins) (((Ins) >> 29) & 0x1)
#define ADD_OP1(Ins) (((Ins) >> 30) & 0x1)
#define ADD_SF(Ins) (((Ins) >> 31) & 0x1)

/* A Union for uni operations of instructions */
typedef union Ins {
  Arm64Adrp adrp;
  Arm64Add  add;
  UINT32    val;
} INST;

// TE informations
typedef struct {
  union {
    VOID                *TEBuffer;
    EFI_TE_IMAGE_HEADER *teHeader;
  };
  VOID *programBuffer;
  UINTN teSize;
  UINTN fileSize;
} TE_INFO_STRUCT;

#endif /* _QC_SEC_PROTOCOLS_LOCATOR_SEC_LIB_H_ */
