#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// 640 kB
#define HEAP_CAPACITY 640000

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

// Insert heap chunk at end of sorted list, use reverse bubble sort to make new list sorted, time complexity O(n)
void heap_chunk_list_insert(heap_chunk_list *list, void *ptr, size_t size)
{
    assert(list->count < CHUNKS_CAPACITY);
    list->chunks[list->count].start = ptr;
    list->chunks[list->count].size = size;

    for (size_t i = list->count; i > 0 && list->chunks[i].start < list->chunks[i-1].start; i--)
    {
        heap_chunk temp = list->chunks[i];
        list->chunks[i] = list->chunks[i-1];
        list->chunks[i-1] = temp;
    }

    list->count += 1;
}

void heap_chunk_list_remove(heap_chunk_list *list, size_t index)
{

}

void print_heap_chunk_list(const heap_chunk_list *list)
{
    printf("%zu Chunk(s):\n", list->count);
    for (size_t i = 0; i < list->count; i++)
    {
        printf("#%zu: start: %p, size: %zu\n", i, list->chunks[i].start, list->chunks[i].size);
    }
}




// Primary heap array
char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

// Secondary and tertiary lists that store heap chunks, which reference allocated and freed spaces in the heap
heap_chunk_list allocated_chunks = {0};
heap_chunk_list freed_chunks = {0};

void *heap_alloc(size_t size)
{
    if (size <= 0) return NULL;

    assert(heap_size + size <= HEAP_CAPACITY);
    void *result = heap + heap_size;
    heap_size += size;

    heap_chunk_list_insert(&allocated_chunks, result, size);

    return result;
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

void print_all_chunks()
{
    printf("ALLOCATED CHUNKS:\n");
    print_heap_chunk_list(&allocated_chunks);
    printf("\nFREED CHUNKS:\n");
    print_heap_chunk_list(&freed_chunks);
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

    print_all_chunks();

    return 0;
}
