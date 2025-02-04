[PcdsFixedAtBuild.common]
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|3048
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|2032

# Smbios Info
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemBrand|"Xiaomi"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Pad 6 S"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"Xiaomi Pad 6S"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Sheng"
gAndromedaPkgTokenSpaceGuid.PcdABLProduct|"Xiaomi Pad 6S"

# Display Caller
gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerExitDisableDisplay|TRUE
gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerStallBeforeEnable|2000

[PcdsDynamicDefault.common]
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|3048
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|2032
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|3048
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|2032
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|381     # = 3048 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|106        # = 2032 / EFI_GLYPH_HEIGHT(19)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|381          # = 3048 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|106             # = 2032 / EFI_GLYPH_HEIGHT(19)
