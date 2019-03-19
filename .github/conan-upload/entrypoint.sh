#!/bin/sh -l

eval "$(pyenv init -)"
eval "$(pyenv virtualenv-init -)"
conan user -p $CONAN_PASSWORD -r upload_repo $CONAN_LOGIN_USERNAME

PACKAGE_NAME=$(conan inspect . -a name | cut -d\  -f2)
PACKAGE_VERSION=$(conan inspect . -a version | cut -d\  -f2)
CONAN_REFERENCE=$PACKAGE_NAME/$PACKAGE_VERSION

conan upload -r upload_repo -c $CONAN_REFERENCE
