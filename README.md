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
```bash
curl --proto '=https' --tlsv1.2 -sSf -L https://install.determinate.systems/nix | sh -s -- install
```
For more information on installing and uninstalling Nix, you can check <https://zero-to-nix.com/start/install>.

Clone the repo and run the installer script:
```bash
git clone 'https://github.com/rayanamal/timelock'
# Inspect the installer script now if you want to
timelock/install.sh
```

Note: It may take a very long time to build the first time you do it, without any visible progress. Be patient.
After the installation completes, you should have `dtlp` and `etlp` binaries in your current directory.

## Usage
Run commands per the below to see their usage:

`./etlp -h`

`./dtlp -h`


#### Important! The timing system is not perfectly accurate. Even though the decryption process is deterministic, the measurements taken from the system during the encryption to determine CPU performance may be affected by other programs running at the same time. Furthermore other programs running during the decryption may delay it too. In extreme cases, it may take up to 2-3 times the encryption duration to decrypt the data.

## Status

This project remains in active use by myself from its inception (iirc, ~2021) to today as of 1 Jan 2025. As an individual with attention issues, I rely on Screen Time controls on my electronic devices to function in the society, and those controls rely on this program for their PIN/password. There is currently no reason to think I won't use it unless I develop something to replace the functionality, or achieve all-day total mindfullness somehow.

### TODOs

* Rewrite it in Rust, easily installable with cargo.
* Make a tutorial.
* Store every X time the non-resolved puzzle in a cache file for resume-ability.
* Combine two programs into one and rename it to "timelock".
* More explanatory and clean usage info.
* Decryption progess bar.
* Encrypt from any kind of data, not just text.
* Hour, min, second is asked to the user separately and can be provided separately as command option.
* Option to delete the data automatically from places warned after encryption.
* If possible, shorten the encrypted result (might help with storing physically on paper).
* Encrypted data formatted in a way that it's possible for someone with no knowledge of the algorithm can write a program and decrypt it. Ck, a, t, n values are clear and human-readable, along with the link to the paper above. Still supporting copy-pasting to decryption prompt.
* Don't use key as message, use a symmetric encryption algorithm to encrypt the data with the randomly generated key, time-lock the key, and output encrypted data and time-locked key, like the original algorithm.
* Inform me on your improved version (Especially about the feature above.).
