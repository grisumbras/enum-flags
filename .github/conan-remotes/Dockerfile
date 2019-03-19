FROM conanio/gcc8 AS base

LABEL "com.github.actions.name"="conan-remotes"
LABEL "com.github.actions.description"="Adds Conan remotes from environment variables"
LABEL "description"="Adds Conan remotes from environment variables"
LABEL "maintainer"="Dmitry Arkhipov <grisumbras@gmail.com>"

USER root
ADD entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
