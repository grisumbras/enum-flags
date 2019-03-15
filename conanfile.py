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

    no_copy_source = True
