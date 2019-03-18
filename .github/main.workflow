workflow "CI" {
  on = "push"
  resolves = "build"
}

action "build" {
  uses = "./.github/ci/"
}
