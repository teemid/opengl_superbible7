#ifndef SB_MEMORY_H
#define SB_MEMORY_H

#include <cstdlib>

#define ALLOCATE(type, byte_count) (type *)malloc(byte_count)
#define BUFFER(type, count) (type *)malloc(sizeof(type) * count)
#define DEALLOCATE(ptr) free(ptr)

#endif
