[PcdsFixedAtBuild.common]
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1080
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|2400

# Smbios Info
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemBrand|"Redmi"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemModel|"K40 Pro"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"haydn"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"MP"

gAndromedaPkgTokenSpaceGuid.PcdABLProduct|"Redmi K40 Pro"

# Display Caller
# gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerExitDisableDisplay|FALSE
# gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerStallBeforeEnable|2000000

[PcdsDynamicDefault.common]
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1080
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|2400
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1080
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|2400
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|99  # = 1080 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|170    # = 2400 / EFI_GLYPH_HEIGHT(19)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|99       # = 1080 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|170         # = 2400 / EFI_GLYPH_HEIGHT(19)
