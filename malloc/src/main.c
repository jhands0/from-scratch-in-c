#include <stdio.h>
#include <assert.h>

// 640 kB
#define CAPACITY 640000

char heap[CAPACITY] = {0};
size_t heap_size = 0;

void *heap_alloc(size_t size)
{
    assert(heap_size + size <= CAPACITY);
    void *result = heap + heap_size;
    heap_size += size;
    return result;
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
    return 0;
}
