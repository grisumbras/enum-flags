#!/bin/sh -l

eval "$(pyenv init -)"
eval "$(pyenv virtualenv-init -)"
if [ x != "x$CONAN_UPLOAD" ]; then
  conan remote add upload_repo $CONAN_UPLOAD
fi
python build.py
