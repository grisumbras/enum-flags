from conans import (
    ConanFile,
    python_requires,
)
import os


b2 = python_requires("b2-helper/0.2.0@grisumbras/testing")


class EnumFlagsTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch", "cppstd",
    build_requires = (
        "boost_build/[>=1.68]@bincrafters/stable",
        "boost_core/[>1.60]@bincrafters/stable",
    )
    generators = "b2"

    def test(self):
        builder = b2.B2(self)
        builder.build_folder = os.path.join(self.build_folder, "base")
        builder.configure()
        builder.build()

        builder = b2.B2(self)
        builder.source_folder = os.path.join(self.source_folder, "pkgconfig")
        builder.build_folder = os.path.join(self.build_folder, "pkgconfig")
        builder.configure()
        builder.build()
