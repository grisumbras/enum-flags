from conans import (
    ConanFile,
    python_requires,
)


b2 = python_requires("b2-helper/0.2.0@grisumbras/testing")


class EnumFlagsConan(b2.B2.Mixin, ConanFile):
    name = "enum-flags"
    version = "0.1.0"
    description = "Bit flags for C++ scoped enums"
    topics = "bit-mask", "bit-flag",
    author = "Dmitry Arkhipov <grisumbras@gmail.com>"
    license = "MIT"
    url = "https://github.com/grisumbras/enum-flags"
    homepage = url

    exports_sources = "jamroot.jam", "build.jam", "*.hpp", "*.cpp", "LICENSE*",
    no_copy_source = True
    build_requires = "boost_build/[>=1.68]@bincrafters/stable"

    def package_info(self):
        self.info.header_only()
