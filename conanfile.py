from conans import (
    ConanFile,
    python_requires,
    tools,
)
import os
import re


b2 = python_requires("b2-helper/0.3.0@grisumbras/testing")


def get_version():
    try:
        content = tools.load("jamroot.jam")
        match = re.search(r"constant\s*VERSION\s*:\s*(\S+)\s*;", content)
        return match.group(1)
    except:
        pass


class EnumFlagsConan(b2.B2.Mixin, ConanFile):
    name = "enum-flags"
    version = get_version()
    description = "Bit flags for C++ scoped enums"
    topics = "bit-mask", "bit-flag",
    author = "Dmitry Arkhipov <grisumbras@gmail.com>"
    license = "MIT"
    url = "https://github.com/grisumbras/enum-flags"
    homepage = url

    exports_sources = (
        "jamroot.jam",
        "*build.jam",
        "*.hpp",
        "*.cpp",
        "LICENSE*",
        "b2/*",
    )
    no_copy_source = True
    build_requires = "boost_build/[>=1.68]@bincrafters/stable"

    def b2_setup_builder(self, builder):
        builder.properties.install_prefix = self.package_folder
        return builder

    def package_info(self):
        self.info.header_only()

        pkgconfig_dir = os.path.join(self.package_folder, "lib", "pkgconfig")
        self.env_info.PKG_CONFIG_PATH.append(pkgconfig_dir)

        self.env_info.CMAKE_PREFIX_PATH.append(self.package_folder)
