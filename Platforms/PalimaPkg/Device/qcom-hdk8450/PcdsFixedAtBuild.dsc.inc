[PcdsFixedAtBuild.common]
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1920
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|1080
#gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdMipiFrameBufferPixelBpp|32

# Display Caller
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdDisplayCallerExitDisableDisplay|FALSE
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdDisplayCallerStallBeforeEnable|1000

# Smbios Info
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemBrand|"Qualcomm"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"6"

gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosProcessorModel|"Snapdragon (TM) 8 Gen1 @ 2.995 GHz"
gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdSmbiosProcessorRetailModel|"SM8450"

gSurfaceDuoFamilyPkgTokenSpaceGuid.PcdABLProduct|"waipio"

[PcdsDynamicDefault.common]
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1920
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|1080
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1920
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|1080
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|240     # = 1920 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|56         # = 1080 / EFI_GLYPH_HEIGHT(19)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|240          # = 1920 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|56              # = 1080 / EFI_GLYPH_HEIGHT(19)
