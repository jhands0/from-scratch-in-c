# Malloc

My attempt at implementing a variable-sized chunk memory allocator in C.

## Getting Started

### Installation

1. Clone the repo

```sh
git clone -b malloc https://github.com/jhands0/from-scratch-in-c.git
```

2. Build the program

```sh
make release
```

## Usage

Heap allocator takes a number of bytes as argument and returns a void pointer to the start of the allocated memory
If the bytes argument is 0, a null value is returned and no memory is allocated
A null value is also returned when the heap has no free memory

```c
void *heap_alloc(size_t bytes)
```

Heap free takes a pointer to allocated memory as argument and returns nothing
If a pointer with a null value is used as argument, no memory is freed

```c
void heap_free(void *ptr)
```

### Examples

```c
char *root = heap_alloc(26);
for (int i = 0; i < 26; i++)
{
    root[i] = i + 'A';
}
```
