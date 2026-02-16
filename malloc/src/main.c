#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// 640 kB
#define HEAP_CAPACITY 640000

// 1 kiB
#define CHUNKS_CAPACITY 1024



// Heap chunk structure, which can represent variable size chunks
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
    for (size_t i = 0; i < list->count; i++)
    {
        if (list->chunks[i].start == ptr) {
            return (int) i;
        }
    }
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

void heap_chunk_list_merge(heap_chunk_list *dst, const heap_chunk_list *src)
{
    dst->count = 0;
    for (size_t i = 0; i < src->count; i++)
    {
        const heap_chunk chunk = src->chunks[i];

        if (dst->count > 0)
        {
            heap_chunk *top_chunk = &dst->chunks[dst->count - 1];
            if (top_chunk->start + top_chunk->size == chunk.start)
            {
                top_chunk->size += chunk.size;
            }
            else
            {
                heap_chunk_list_insert(dst, chunk.start, chunk.size);
            }
        }
        else
        {
            heap_chunk_list_insert(dst, chunk.start, chunk.size);
        }
    }
}

// Iterate up from index, moving all heap chunks down by one index, time complexity O(n)
void heap_chunk_list_remove(heap_chunk_list *list, size_t index)
{
    assert(index < list->count);
    for (size_t i = index; i < list->count - 1; i++)
    {
        list->chunks[i] = list->chunks[i+1];
    }
    list->count -= 1;
}

void print_heap_chunk_list(const heap_chunk_list *list)
{
    printf("%zu Chunk(s):\n", list->count);
    for (size_t i = 0; i < list->count; i++)
    {
        printf("#%zu: start: %p, size: %zu\n", i+1, list->chunks[i].start, list->chunks[i].size);
    }
}




// Primary heap array
char heap[HEAP_CAPACITY] = {0};

// Secondary and tertiary lists that store heap chunks, which reference allocated and freed spaces in the heap
heap_chunk_list allocated_chunks = {0};
heap_chunk_list freed_chunks = {
    .count = 1,
    .chunks = {
        [0] = {.start = heap, .size = sizeof(heap)}
    },
};
heap_chunk_list temp_chunks = {0};

void *heap_alloc(size_t size)
{
    if (size <= 0) {
        return NULL;
    }

    heap_chunk_list_merge(&temp_chunks, &freed_chunks);
    freed_chunks = temp_chunks;

    for (size_t i = 0; i < freed_chunks.count; i++) {
        const heap_chunk chunk = freed_chunks.chunks[i];
        if (freed_chunks.chunks[i].size >= size) {
            heap_chunk_list_remove(&freed_chunks, i);

            const size_t tail_size = chunk.size - size;
            heap_chunk_list_insert(&allocated_chunks, chunk.start, size);

            if (tail_size > 0) {
                heap_chunk_list_insert(&freed_chunks, chunk.start + size, tail_size);
            }

            return chunk.start;
        }
    }

    // Out of memory, no free chunks
    return NULL;
}

void heap_free(void *ptr)
{
    if (ptr != NULL)
    {
        const int index = heap_chunk_list_find(&allocated_chunks, ptr);
        assert(index >= 0);
        assert(ptr == allocated_chunks.chunks[index].start);
        heap_chunk_list_insert(&freed_chunks, allocated_chunks.chunks[index].start, allocated_chunks.chunks[index].size);
        heap_chunk_list_remove(&allocated_chunks, (size_t) index);
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
    //char *root = heap_alloc(26);
    //for (int i = 0; i < 26; i++)
    //{
    //    root[i] = i + 'A';
    //}

    for (int i = 0; i < 10; i++)
    {
        void *ptr = heap_alloc(i);
        if (i % 2 == 0)
        {
            heap_free(ptr);
        }
    }

    print_all_chunks();

    heap_alloc(9);

    print_all_chunks();

    return 0;
}
