#!/usr/bin/env nix-shell
#! nix-shell -i bash --pure
#! nix-shell -I https://github.com/NixOS/nixpkgs/archive/63dacb46bf939521bdc93981b4cbb7ecb58427a0.tar.gz
#! nix-shell --packages fish bash gcc gnumake gmp git cacert curl

curl -sSLf --proto '=https' 'https://github.com/aerbil313/timelock/raw/main/src/install.fish' | fish -c "source - $PATH"
