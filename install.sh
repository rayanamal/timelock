#!/usr/bin/env nix-shell
#! nix-shell -i bash --pure
#! nix-shell -I https://github.com/NixOS/nixpkgs/archive/01f116e4df6a15f4ccdffb1bcd41096869fb385c.tar.gz
#! nix-shell --packages bash gcc gnumake gmp

# Exit immediately if a command exits with a non-zero status
set -e

if [[ ! -e "../timelock" || ! -e ".gitignore" ]]; then
    echo "Error: Are you in the repository directory?"
    exit 1
fi

main() {
    make -C src/
    mkdir -p $HOME/.local/bin
    mv etlp dtlp $HOME/.local/bin/
}

main "$@"
