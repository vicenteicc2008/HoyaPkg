[PcdsFixedAtBuild.common]
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1440
gAndromedaPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|3200

# Display Caller
gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerExitDisableDisplay|TRUE
gAndromedaPkgTokenSpaceGuid.PcdDisplayCallerStallBeforeEnable|1000

# Smbios Info
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemBrand|"Redmi"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemModel|"K60 Pro"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"socrates"
gAndromedaPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"MP"

gAndromedaPkgTokenSpaceGuid.PcdABLProduct|"Redmi K60 Pro"

[PcdsDynamicDefault.common]
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1440
gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|3200
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1440
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|3200
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|180  # = 1440 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|168    # = 3200 / EFI_GLYPH_HEIGHT(19)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|180       # = 1440 / EFI_GLYPH_WIDTH(8)
gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|168         # = 3200 / EFI_GLYPH_HEIGHT(19)
