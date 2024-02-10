#!/usr/bin/env fish

set PATH (string split ":" $argv[1])
set tmp_dir (mktemp -d)
git clone "https://github.com/aerbil313/timelock" $tmp_dir
make --directory $tmp_dir/src
mv $tmp_dir/{dtlp,etlp} .
