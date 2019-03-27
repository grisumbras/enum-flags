#!/bin/sh -l


eval "$(pyenv init -)"
eval "$(pyenv virtualenv-init -)"


# fixing issue with conan_package_tools and python_requires
if [ x != "x$CONAN_UPLOAD" ]; then
  conan remote add upload_repo $CONAN_UPLOAD
fi

i=1
old_ifs=$IFS
IFS=,
for r in $CONAN_REMOTES; do
  conan remote add env_remote_$i "$r"
  i=$(($i+1))
done
IFS=$old_ifs


python build.py
