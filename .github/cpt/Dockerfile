FROM conanio/gcc8 AS base

LABEL "com.github.actions.name"="conan-actions"
LABEL "com.github.actions.description"="GitHub Actions for building/publishing with Conan"
LABEL "description"="GitHub Actions for building/publishing with Conan"
LABEL "com.github.actions.icon"="package"
LABEL "com.github.actions.color"="blue"

LABEL "repository"="http://github.com/grisumbras/conan-actions"
LABEL "homepage"="http://github.com/grisumbras/conan-actions"
LABEL "maintainer"="Dmitry Arkhipov <grisumbras@gmail.com>"

USER root
ADD entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
