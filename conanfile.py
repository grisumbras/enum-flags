from conans import (
    ConanFile,
    python_requires,
    tools,
)
import os
import re


b2 = python_requires("b2-helper/0.5.0@grisumbras/stable")


def get_version():
    try:
        content = tools.load("jamroot.jam")
        match = re.search(r"constant\s*VERSION\s*:\s*(\S+)\s*;", content)
        return match.group(1)
    except:
        pass


@b2.build_with_b2
class EnumFlagsConan(ConanFile):
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
        "exports/*.jam",
        "*.hpp",
        "*.cpp",
        "LICENSE*",
    )
    no_copy_source = True
    build_requires = "boost_build/[>=4.0]@bincrafters/testing"

    def package_info(self):
        self.info.header_only()

        pkgconfig_dir = os.path.join(self.package_folder, "lib", "pkgconfig")
        self.env_info.PKG_CONFIG_PATH.append(pkgconfig_dir)

        self.env_info.CMAKE_PREFIX_PATH.append(self.package_folder)
