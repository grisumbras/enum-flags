from conans import (
    CMake,
    ConanFile,
    python_requires,
)
import os


b2 = python_requires("b2-helper/0.5.0@grisumbras/stable")


class EnumFlagsTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch",
    build_requires = (
        "boost_build/[>=4.0]@bincrafters/testing",
        "boost_core/[>1.60]@bincrafters/stable",
        "cmake_installer/[>3.0]@conan/stable",
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

        builder = CMake(self)
        builder.configure(
            source_folder=os.path.join(self.source_folder, "cmake"),
            build_folder=os.path.join(self.build_folder, "cmake"),
        )
        builder.build()
