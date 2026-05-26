# rle

A program to compress and restore files using run length encoding.

## Getting Started

1. Clone the repo

```sh
git clone -b rle https://github.com/jhands0/from-scratch-in-c.git
```

2. Build the program

```sh
make release
```

## Usage

```sh
./out [compress|decompress] < <file>
```

### Examples

```sh
./out compress < "file.txt"

./out compress < "input_file.txt" > "output_file.txt"

./out decompress < "compressed_image.ppm > "restored_image.ppm"
```
