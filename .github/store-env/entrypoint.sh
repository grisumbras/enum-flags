#!/bin/sh -l

for e in $(env); do
  k=$(echo $e | cut -d= -f1)
  v=$(echo $e | sed 's/^.*=//')
  if [ "x$k" = "x${k#GITHUB_}" ]; then
    echo "export $k='$v'" >>~/.profile
  fi
done
