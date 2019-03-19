FROM conanio/gcc8

LABEL "com.github.actions.name"="conan-upload"
LABEL "com.github.actions.description"="Uploads a Conan package"

LABEL "maintainer"="Dmitry Arkhipov <grisumbras@gmail.com>"

USER root
ADD entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
