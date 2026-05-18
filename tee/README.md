# tee

A clone of the tee command, which redirects user input to both a file and stdout.

## Getting Started

### Installation

1. Clone the repo

```sh
git clone -b tee https://github.com/jhands0/from-scratch-in-c.git
```

2. Build the program

```sh
make release
```

## Usage

```sh
echo <text> | ./out <file>

cat <file> | ./out <file>

./out <file>
<text>
```

### Examples

```sh
echo "Hello" | ./out "world.txt"

cat "src/main.c" | ./out "other.c"

./out "log"
"Thanks for reading!"
```