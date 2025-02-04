[PcdsFixedAtBuild.common]
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1440
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|3200

# Smbios Info
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemBrand|"Xiaomi"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemModel|"11"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"venus"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"MP"

gAndromedaPkgTokenSpaceGuid.PcdABLProduct|"Xiaomi 11"
# Display Caller
# gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerExitDisableDisplay|FALSE
# gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerStallBeforeEnable|2000000

[PcdsDynamicDefault.common]
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1440
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|3200
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1440
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|3200
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|180  # = 1440 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|168     # = 3200 / EFI_GLYPH_HEIGHT(19)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|180       # = 1440 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|168          # = 3200 / EFI_GLYPH_HEIGHT(19)
