COMPATIBLE_MACHINE:nxp-ls1046 = "nxp-ls1046"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
SRC_URI:nxp-ls1046 = "git://github.com/nxp-qoriq/dpdk;protocol=https;nobranch=1"
SRC_URI:append:nxp-ls1046 = " \
            file://0001-meson.build-march-and-mcpu-already-passed-by-Yocto.patch \
"

MESON_BUILDTYPE:nxp-ls1046 = "release"

PACKAGECONFIG:append:nxp-ls1046 ??= "openssl"
PACKAGECONFIG[openssl] = ",,openssl"

DPDK_EXAMPLES:nxp-ls1046 = "l2fwd,l3fwd,l2fwd-crypto,ipsec-secgw,ip_fragmentation,ip_reassembly,qdma_demo,timer,multi_process/simple_mp"
EXTRA_OEMESON:append:nxp-ls1046 = " \
		-Denable_kmods=false \
		-Doptimization=3 \
		--cross-file ${S}/config/arm/arm64_poky_linux_gcc \
		-Denable_driver_sdk=true \
		${@bb.utils.contains('DISTRO_FEATURES', 'vpp', '-Dc_args="-Ofast -fPIC -ftls-model=local-dynamic"', '', d)} \
"

RDEPENDS:${PN}:append:nxp-ls1046 = " bash python3-pyelftools"
RDEPENDS:${PN}:remove:nxp-ls1046 = "kernel-module-dpdk-extras"

CVE_PRODUCT:nxp-ls1046 = "data_plane_development_kit"

do_install:append:nxp-ls1046(){
    install -d ${D}/${sysconfdir}/dpdk
    cp -rf ${S}/nxp/* ${D}/${sysconfdir}/dpdk
}
