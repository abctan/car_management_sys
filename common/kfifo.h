#ifndef __KFIFO_H
#define __KFIFO_H


struct __kfifo {
	unsigned int	in;      // 入列的时候增加的位置
	unsigned int	out;     // 出列的时候增加的位置
	unsigned int	mask;    // 巧妙的 mask 设计，同时包含了数据的个数信息
	unsigned int	esize;   // 元素的大小
	void            *data;   // 数据
};


int __kfifo_alloc(struct __kfifo *fifo, unsigned int size,
	              unsigned long esize);
int __kfifo_init(struct __kfifo *fifo, void *buffer,
		         unsigned int size, unsigned long esize);
void __kfifo_free(struct __kfifo *fifo);
unsigned int __kfifo_in(struct __kfifo *fifo,
		                const void *buf, unsigned int len);
unsigned int __kfifo_out(struct __kfifo *fifo,
		                 void *buf, unsigned int len);


#endif /* __KFIFO_H */