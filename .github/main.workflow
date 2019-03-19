workflow "CI" {
  on = "push"
  resolves = "build"
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
    CONAN_PRINT_RUN_COMMANDS = "1"
    CONAN_REMOTES = "https://api.bintray.com/conan/bincrafters/public-conan"
    CONAN_UPLOAD = "https://api.bintray.com/conan/grisumbras/conan"
    CONAN_USERNAME = "grisumbras"
  }
}
