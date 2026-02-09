#include <stddef.h>
#include <stdio.h>
#include <assert.h>

// 640 kB
#define CAPACITY 640000

// 1 kiB
#define ALLOCATED_CHUNKS_CAPACITY 1024

// Fixed sized chunks
typedef struct
{
    void *start;
    size_t size;
} heap_chunk;

// Primary heap array
char heap[CAPACITY] = {0};
size_t heap_size = 0;

// Secondary smaller array containing heap chunks, which reference allocated spaces in heap
heap_chunk allocated_chunks[ALLOCATED_CHUNKS_CAPACITY] = {0};
size_t allocated_chunks_size = 0;

void *heap_alloc(size_t size)
{
    assert(heap_size + size <= CAPACITY);
    void *result = heap + heap_size;
    heap_size += size;

    const heap_chunk chunk = {
        .start = result,
        .size = size,
    };

    assert(allocated_chunks_size < ALLOCATED_CHUNKS_CAPACITY);
    allocated_chunks[allocated_chunks_size++] = chunk;

    return result;
}

void print_allocated_chunks(void)
{
    printf("%zu Allocated chunk(s):\n", allocated_chunks_size);
    for (size_t i = 0; i < allocated_chunks_size; i++)
    {
        printf("#%zu: start: %p, size: %zu\n", i, allocated_chunks[i].start, allocated_chunks[i].size);
    }
}

void heap_free(void* ptr)
{

}

void heap_collect()
{

}

int main()
{
    char *root = heap_alloc(26);
    for (int i = 0; i < 26; i++)
    {
        root[i] = i + 'A';
    }

    for (int i = 0; i < 50; i++)
    {
        heap_alloc(i+1);
    }

    print_allocated_chunks();

    return 0;
}
