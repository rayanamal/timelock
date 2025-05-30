# timelock

Time-lock puzzles are cryptographic algorithms which encrypt data in a way that it's not possible to decrypt it until a certain amount of time passes.

This program is designed to timelock numerical keys, which you can then use with other encryption tools like [`age`](https://github.com/FiloSottile/age) to encrypt whatever data you want. 

A good explanation of the algorithm can be found here:
https://www.cs.tufts.edu/comp/116/archive/fall2013/wclarkson.pdf

## Installation

You need Nix installed on your machine. If you don't have it, you can install it with the following command:
```bash
curl -L https://nixos.org/nix/install | sh -s -- --daemon
```

Clone the repo and run the installer script:
```bash
git clone 'https://github.com/rayanamal/timelock'
# Inspect the installer script now if you want to
timelock/install.sh
```

Note: It may take a really long time to build the first time you do it.
After the installation completes, you should have `dtlp` and `etlp` binaries in your current directory.

## Usage
Run commands per the below to see their usage:

`./etlp -h`

`./dtlp -h`


### Accuracy of the decryption duration

The program encrypts data for the CPU it is running on. Thus, many factors can affect the encryption/decryption speed:

- New CPUs with faster clock speeds will decrypt faster than older ones.
- On laptops, Power Saving vs. Performance modes can have up to 2x difference in CPU clock speed.
- Cloud providers often run virtualized CPUs, sharing a CPU between many applications, which can result in wildly varying real clock speeds.
 
When both encryption and decryption happens under same conditions, the decryption time remains highly accurate, based on my experience over the years.

## Status

This project remains in active use by (at least) myself from its inception (iirc, ~2021) to today as of 31 May 2025. As an individual with attention issues, I rely on this program to manage the [commitment devices](https://en.wikipedia.org/wiki/Commitment_device) I use every day. I expect to continue using and maintaining it for the foreseeable future.

### TODOs

- Combine two programs into one and rename it to "timelock".
- Rewrite it in Rust.
- Implement symmetric encryption, `rage` can probably be used as a library.
- A small tutorial in the README.
- Better usage info, in the CLI and the README.
- Periodically store the non-resolved puzzle in a cache file for pause-and-resume ability.
- Decryption progress bar.
- Hour, min, second is asked to the user separately and can be provided separately as command option.
- Create and use a properly specified file format.
  - Make it human readable, with instructions on how to decrypt the file, for data durability concerns.