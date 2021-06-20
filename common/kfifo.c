#include "kfifo.h"
#include <stdlib.h>
#include <string.h>
#include "errno.h"

#define min(x,y) ((x) < (y) ? x : y)

static inline int is_power_of_2(unsigned int n)
{
    return !((n - 1) & n);
}

unsigned int roundup_pow_of_two(unsigned int n)
{
    if(is_power_of_2(n))
        return n;

    int i = 32;
    while(i--)
    {
        if((n >> i) & 1)
            break;
    }

    n = 1 << (i + 1);
    return n;
}

static inline void *kmalloc_array(unsigned n, size_t s)
{
	return malloc(n * s);
}

int __kfifo_alloc(struct __kfifo *fifo, unsigned int size,
	              unsigned long esize)
{
	/*
	 * round up to the next power of 2, since our 'let the indices
	 * wrap' technique works only in this case.
	 */
	size = roundup_pow_of_two(size);
 
	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = esize;
 
	if (size < 2) {
		fifo->data = NULL;
		fifo->mask = 0;
		return -EINVAL;
	}
 
	fifo->data = kmalloc_array(esize, size);
 
	if (!fifo->data) {
		fifo->mask = 0;
		return -ENOMEM;
	}
	fifo->mask = size - 1;
 
	return 0;
}


int __kfifo_init(struct __kfifo *fifo, void *buffer,
		         unsigned int size, unsigned long esize)
{
	size /= esize;
 
	size = roundup_pow_of_two(size);
 
	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = esize;
	fifo->data = buffer;
 
	if (size < 2) {
		fifo->mask = 0;
		return -EINVAL;
	}
	fifo->mask = size - 1;
 
	return 0;
}

void __kfifo_free(struct __kfifo *fifo)
{
	free(fifo->data);
	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = 0;
	fifo->data = NULL;
	fifo->mask = 0;
}

/*
 * internal helper to calculate the unused elements in a fifo
 */
static inline unsigned int kfifo_unused(struct __kfifo *fifo)
{
	return (fifo->mask + 1) - (fifo->in - fifo->out);
}
 
static void kfifo_copy_in(struct __kfifo *fifo, const void *src,
		                  unsigned int len, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int l;
 
	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		len *= esize;
	}
	l = min(len, size - off);
 
	memcpy(fifo->data + off, src, l);
	memcpy(fifo->data, src + l, len - l);
}
 
unsigned int __kfifo_in(struct __kfifo *fifo,
		const void *buf, unsigned int len)
{
	unsigned int l;
 
	l = kfifo_unused(fifo);
	if (len > l)
		len = l;
 
	kfifo_copy_in(fifo, buf, len, fifo->in);
	fifo->in += len;
	return len;
}

static void kfifo_copy_out(struct __kfifo *fifo, void *dst,
		unsigned int len, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int l;
 
	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		len *= esize;
	}
	l = min(len, size - off);
 
	memcpy(dst, fifo->data + off, l);
	memcpy(dst + l, fifo->data, len - l);
}
 
unsigned int __kfifo_out_peek(struct __kfifo *fifo,
		void *buf, unsigned int len)
{
	unsigned int l;
 
	l = fifo->in - fifo->out;
	if (len > l)
		len = l;
 
	kfifo_copy_out(fifo, buf, len, fifo->out);
	return len;
}
 
unsigned int __kfifo_out(struct __kfifo *fifo,
		void *buf, unsigned int len)
{
	len = __kfifo_out_peek(fifo, buf, len);
	fifo->out += len;
	return len;
}