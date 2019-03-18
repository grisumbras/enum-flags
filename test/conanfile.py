from conans import (
    ConanFile,
    python_requires,
)


b2 = python_requires("b2-helper/0.2.0@grisumbras/dev")


class EnumFlagsTestConan(b2.B2.Mixin, ConanFile):
    settings = "os", "compiler", "build_type", "arch", "cppstd",
    build_requires = (
        "boost_build/[>=1.68]@bincrafters/stable",
        "boost_core/[>1.60]@bincrafters/stable",
    )

    def test(self):
        pass
