#@TYPE: Machine inc.
#@NAME: nxp-ls1046 layer

DEFAULTTUNE = "cortexa72"
require conf/machine/include/arm/armv8a/tune-cortexa72.inc

MACHINE_FEATURES += "usbhost jffs2 ext2 alsa vfat"

KERNEL_IMAGETYPE = "Image"
KERNEL_DEVICETREE = "freescale/fsl-ls1046a-rdb-sdk.dtb freescale/fsl-ls1046a-rdb-usdpaa.dtb \
			freescale/fsl-ls1026a-rdb-sdk.dtb freescale/fsl-ls1026a-rdb-usdpaa.dtb"

SERIAL_CONSOLE = "115200 ttyS0"

MACHINE_EXTRA_RRECOMMENDS = " kernel-modules kernel-devicetree"
IMAGE_FSTYPES += "tar.bz2 wic wic.bmap"
WKS_FILE = "nxp-ls1046-sdimage.wks"
IMAGE_INSTALL:append = " kernel-devicetree kernel-image-image"
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot"
IMAGE_BOOT_FILES ?= " Image fsl-ls1046a-rdb-sdk.dtb fsl-ls1046a-rdb-usdpaa.dtb \
			fsl-ls1026a-rdb-sdk.dtb fsl-ls1026a-rdb-usdpaa.dtb"

# multilib support
MULTILIBS ?= "multilib:lib32"
DEFAULTTUNE:virtclass-multilib-lib32 ?= "armv7athf-neon"

# it's used by many recipes in meta-freescale
MACHINE_SOCARCH = "${TUNE_PKGARCH}"

# pull in the meta-freescale layer.
BSP_NXP_DERIVED:append:nxp-ls1046  = " nxp-ls1046"

PREFERRED_PROVIDER_virtual/kernel ??= "linux-yocto"
PREFERRED_VERSION_linux-yocto ?= "6.12%"
PREFERRED_VERSION_dpdk = "22.11"
NON_MULTILIB_RECIPES:append = " dpdk"

NON_MULTILIB_RECIPES:append = " rcw"

CUSTOMER_BUILD_BOOTLOADER ?= "0"
SDK_MACHINE = "ls1046ardb"
UBOOT_CONFIG ??= "tfa-secure-boot tfa"
UBOOT_CONFIG[tfa] = "ls1046ardb_tfa_defconfig"
UBOOT_CONFIG[tfa-secure-boot] = "ls1046ardb_tfa_SECURE_BOOT_defconfig"
RCWQSPI ?= "RR_FFSSPPPH_1133_5559/rcw_1800_qspiboot"
RCWSD ?= "RR_FFSSPPPH_1133_5559/rcw_1800_sdboot"
RCWEMMC ?= "RR_FFSSPPPH_1133_5559/rcw_1800_emmcboot"
FMAN_UCODE ?= "fsl_fman_ucode_ls1046_r1.0_106_4_18.bin"
EXTRA_IMAGEDEPENDS:append = " ${@bb.utils.contains('CUSTOMER_BUILD_BOOTLOADER', '1', \
									'fm-ucode rcw qe-ucode uefi qoriq-atf ls2-phy', '', d)}"
PREFERRED_PROVIDER_u-boot ??= "u-boot-qoriq"
MACHINEOVERRIDES:prepend = "${@bb.utils.contains('CUSTOMER_BUILD_BOOTLOADER', '1', \
									'fsl-lsch2:qoriq:qoriq-arm64:ls1046a:ls1046ardb:', '', d)}"
do_image_wic[depends] += "${@bb.utils.contains('CUSTOMER_BUILD_BOOTLOADER', '1', 'secure-boot-qoriq:do_deploy', '', d)}"

# optee related configs
MACHINE_FEATURES:append = " optee"
DISTRO_FEATURES:append = " optee"
NON_MULTILIB_RECIPES:append = " optee-os-qoriq"
NON_MULTILIB_RECIPES:append = " optee-test-qoriq"
NON_MULTILIB_RECIPES:append = " optee-client-qoriq"
NON_MULTILIB_RECIPES:append = " optee-os-qoriq-tadevkit"
