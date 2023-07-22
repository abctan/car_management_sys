#ifndef __TYPES_H
#define __TYPES_H

/* bsd */
typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned int		u_int;
typedef unsigned long		u_long;

/* sysv */
typedef unsigned char		unchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

typedef unsigned char       bool;
#define FALSE               0
#define TRUE                1
#define SUCCESS             0
#define FAILURE             (-1)

/* 基本颜色 */
typedef enum {
    RED = 0,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    VIOLET,
    COLOR_BUTT
} color_e;

#endif // !__TYPES_H