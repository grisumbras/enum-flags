import os
from conans import (
    ConanFile,
    python_requires,
)


b2 = python_requires("b2-helper/0.2.0@grisumbras/dev")


class EnumFlagsConan(b2.B2.Mixin, ConanFile):
    name = "enum-flags"
    version = "0.1.0"
    description = "Bit flags for C++ scoped enums"
    topics = "bit-mask", "bit-flag",
    author = "Dmitry Arkhipov <grisumbras@gmail.com>"
    license = "MIT"
    url = "https://github.com/grisumbras/enum-flags"
    homepage = url

    settings = "os", "compiler", "build_type", "arch", "cppstd"
    no_copy_source = True

    def config_options(self):
        if not self.develop:
            del self.settings.os
            del self.settings.compiler
            del self.settings.build_type
            del self.settings.arch

    def build_requirements(self):
        if self.develop:
            self.build_requires("boost_core/[>1.60]@bincrafters/stable")

    def package_info(self):
        self.info.header_only()
