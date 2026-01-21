# hexdump

An xxd like program that creates a hexdump of any file

## Getting Started

### Installation

1. Clone this repo

```sh
git clone -b hexdump https://github.com/jhands0/from-scratch-in-c.git
```

2. Build the program

```sh
make release
```

## Usage

```sh
echo <text> | ./out

cat <file> | ./out

./out
<text>
```

### Examples

```sh
echo "Hello!" | ./out

cat "src/main.c" | ./out

./out
"Thanks for reading!"
```
