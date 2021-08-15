#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <string.h>
#include "types.h"

//接受字符串宏
#define GETLINES(string, buf) do{						\
					printf(string);						\
					fgets(buf, sizeof(buf), stdin);		\
					if (buf[strlen(buf) - 1] == '\n')	\
						buf[strlen(buf) - 1] = '\0';	\
				}while(0)


//容错宏
#define ERRP(con, string, go) do{					\
					if ((con))						\
					{								\
						printf(#string"\n");	    \
						go;						    \
					}								\
				}while(0)

// 获取数组长度
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

//打印格式
#define PRI_O(e) printf(#e" = %#o\n", e);
#define PRI_D(e) printf(#e" = %d\n", e);
#define PRI_H(e) printf(#e" = %#x\n", e);

// 获取随机数[min, max]
int com_rand(int min, int max, int *value);

#endif //common.h