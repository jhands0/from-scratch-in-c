# container

A program to create linux containers, written in c.

## Getting Started

### Prerequisites

Install both libcap and libseccomp.

#### Debian/Ubuntu

#### Fedora

#### From Source

### Installation

1. Clone the repo

```sh
git clone -b <container> https://github.com/jhands0/from-scratch-in-c.git
```

2. Build the program

```sh
make release
```

## Usage

```sh
sudo ./out -m <linux-image> -u <container-uid> -c <command-to-run>
```

### Examples

```sh
sudo ./out -m ~/misc/busybox-img/ -u 0 -c /bin/sh
```

Note that the image's linux kernel version should be between 4.7.x and 4.8.x, other versions have not been tested.
