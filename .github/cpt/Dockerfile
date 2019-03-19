FROM conanio/gcc8 AS base

LABEL "com.github.actions.name"="conan-build"
LABEL "com.github.actions.description"="Builds a Conan package"

LABEL "maintainer"="Dmitry Arkhipov <grisumbras@gmail.com>"

USER root
ADD entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
