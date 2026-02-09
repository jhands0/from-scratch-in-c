#include <stddef.h>
#include <stdio.h>
#include <assert.h>

// 640 kB
#define CAPACITY 640000

// 1 kiB
#define CHUNKS_CAPACITY 1024

// Fixed sized chunks
typedef struct
{
    void *start;
    size_t size;
} heap_chunk;

typedef struct
{
    size_t count;
    heap_chunk chunks[CHUNKS_CAPACITY];
} heap_chunk_list;

int heap_chunk_list_find(const heap_chunk_list *list, void *ptr)
{
    return -1;
}

void heap_chunk_list_insert(heap_chunk_list *list, void *ptr, size_t size)
{

}

void heap_chunk_list_remove(heap_chunk_list *list, size_t index)
{

}


// Primary heap array
char heap[CAPACITY] = {0};
size_t heap_size = 0;

// Secondary and tertiary lists that store heap chunks, which reference allocated and freed spaces in the heap
heap_chunk_list allocated_chunks = {0};
heap_chunk_list freed_chunks = {0};

void *heap_alloc(size_t size)
{
    if (size <= 0) return NULL;

    assert(heap_size + size <= CAPACITY);
    void *result = heap + heap_size;
    heap_size += size;

    const heap_chunk chunk = {
        .start = result,
        .size = size,
    };

    assert(allocated_chunks.count < CHUNKS_CAPACITY);
    allocated_chunks.chunks[allocated_chunks.count++] = chunk;

    return result;
}

void print_allocated_chunks(void)
{
    printf("%zu Allocated chunk(s):\n", allocated_chunks.count);
    for (size_t i = 0; i < allocated_chunks.count; i++)
    {
        printf("#%zu: start: %p, size: %zu\n", i, allocated_chunks.chunks[i].start, allocated_chunks.chunks[i].size);
    }
}

// Iterates through the allocated chunks array, time complexity O(n)
void heap_free(void* ptr)
{
    for (size_t i = 0; i < allocated_chunks.count; i++)
    {
        if (allocated_chunks.chunks[i].start == ptr)
        {
            //Move chunk from allocated chunks list to freed chunks list
        }
    }
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
