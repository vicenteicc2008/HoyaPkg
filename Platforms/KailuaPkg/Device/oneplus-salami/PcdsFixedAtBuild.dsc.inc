[PcdsFixedAtBuild.common]
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1080
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|2412

# Smbios Info
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemBrand|"Oneplus"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemModel|"11"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"MP"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"1"
gAndromedaPkgTokenSpaceGuid.PcdABLProduct|"Oneplus 11"

# Display Caller
gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerExitDisableDisplay|FALSE
gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerStallBeforeEnable|2000

[PcdsDynamicDefault.common]
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1080
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|2412
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1080
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|2412
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|135     # = 1080 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|126        # = 2412 / EFI_GLYPH_HEIGHT(19)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|135          # = 1080 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|126             # = 2412 / EFI_GLYPH_HEIGHT(19)
