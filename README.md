# timelock

Time-lock puzzles are cryptographic algorithms which encrypt data in a way that it's not possible to decrypt encrypted data until a certain amount of time passes. A good explanation of the algorithm:
https://www.cs.tufts.edu/comp/116/archive/fall2013/wclarkson.pdf

Note that this program differs from the algorithm described in the original paper in one aspect. Original algorithm:
1. Generates a random key
2. Uses it to encrypt data with a symmetric encryption algorithm
3. Time-locks the key
4. Outputs encrypted data and time-locked key.

This program doesn't use symmetric encryption, it just time-locks the data you give it. You can use `gpg --symmetric` to symmetrically encrypt whatever data you want with a random numerical password and then use this program to time-lock the password.

## Installation

You can use this program on every single machine at any point in the future, because it's built with Nix. First install Nix:
```
curl --proto '=https' --tlsv1.2 -sSf -L https://install.determinate.systems/nix | sh -s -- install
```
For more information on installing and uninstalling Nix, you can check <https://zero-to-nix.com/start/install>.

Download and run the installer:
```
nix-shell --pure --packages cacert curl \
  -I 'https://github.com/NixOS/nixpkgs/archive/057f9aecfb71c4437d2b27d3323df7f93c010b7e.tar.gz' \
  --command "curl -sSLOf --proto '=https' 'https://github.com/aerbil313/timelock/raw/main/install-timelock.sh'" \
    && chmod +x ./install-timelock.sh \
    && ./install-timelock.sh
```

Note: It may take a very long time to build the first time you do it, without any visible progress. Be patient.
After the installation completes, you should have `dtlp` and `etlp` binaries in your current directory.

## Usage
Run commands per the below to see their usage:

`./etlp -h`

`./dtlp -h`

### TODO for the next person who is willing to take the task:

* Make a tutorial.
* Store every X time the non-resolved puzzle in a cache file.
* Combine two programs into one and rename it to "timelock".
* Make an installer.
* More explanatory and clean usage info.
* Decryption progess bar.
* Encrypt from any kind of data, not just text.
* Hour, min, second is asked to the user separately and can be provided separately as command option.
* Option to delete the data automatically from places warned after encryption.
* If possible, shorten the encrypted message.
* Encrypted data formatted in a way that it's possible for someone with no knowledge of the algorihthm can write a program and decrypt it. Ck, a, t, n values are clear and human-readable, along with the link to the paper above. Still supporting copy-pasting to decryption prompt.
* Don't use key as message, use a symmetric encryption algorithm to encrypt the data with the randomly generated key, time-lock the key, and output encrypted data and time-locked key, like the original algorithm. 
* Inform me on your improved version (I need especially the feature above.).

