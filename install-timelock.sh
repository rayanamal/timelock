#!/usr/bin/env nix-shell
#! nix-shell -i bash --pure
#! nix-shell -I https://github.com/NixOS/nixpkgs/archive/057f9aecfb71c4437d2b27d3323df7f93c010b7e.tar.gz
#! nix-shell --packages fish bash gcc gnumake gmp git cacert curl

curl -sSLf --proto '=https' 'https://github.com/aerbil313/timelock/raw/main/src/install.fish' | fish -c "source - $PATH"
