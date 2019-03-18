#!/bin/sh -l

eval "$(pyenv init -)"
eval "$(pyenv virtualenv-init -)"
conan remote add upload https://api.bintray.com/conan/grisumbras/conan
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan create . grisumbras/testing
