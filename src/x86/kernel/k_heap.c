#include <rhKernel/heap.h>

inline void *kmalloc(size_t _size)
{
	return region_request_alloc(_size);
}

inline void kfree(void *_ptr)
{
	region_request_free(_ptr);
}
