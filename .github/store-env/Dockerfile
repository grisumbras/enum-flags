FROM alpine AS base

LABEL "com.github.actions.name"="store-env"
LABEL "com.github.actions.description"="Stores environment variables in .profile"
LABEL "description"="Stores environment variables in .profile"
LABEL "maintainer"="Dmitry Arkhipov <grisumbras@gmail.com>"

USER root
ADD entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
