workflow "CI" {
  on = "push"
  resolves = "publish"
}


action "remotes" {
  uses = "./.github/conan-remotes/"
  env = {
    CONAN_REMOTES = "https://api.bintray.com/conan/bincrafters/public-conan"
    CONAN_UPLOAD = "https://api.bintray.com/conan/grisumbras/conan"
  }
}


action "build" {
  needs = "remotes"
  uses = "./.github/cpt/"
  env = {
    CONAN_CHANNEL = "testing"
    CONAN_STABLE_BRANCH_PATTERN = "\\d+\\.\\d+(\\.\\d+[-\\w\\.]*)?"
    CONAN_PRINT_RUN_COMMANDS = "1"
    CONAN_REMOTES = "https://api.bintray.com/conan/bincrafters/public-conan"
    CONAN_UPLOAD = "https://api.bintray.com/conan/grisumbras/conan"
    CONAN_USERNAME = "grisumbras"
  }
}


action "filter-ref" {
  needs = "build"
  uses = "actions/bin/filter@master"
  args = "branch master || tag"
}

action "publish" {
  uses = "./.github/conan-upload/"
  needs = "filter-ref"
  secrets = ["CONAN_LOGIN_USERNAME", "CONAN_PASSWORD"]
}
