#ifndef __TYPES_H
#define __TYPES_H

#define SUCCESS (0)
#define FAILURE (-1)

/* 返回值 */
typedef enum {
    FALSE = 0,
    TRUE  = 1
} bool;

/* 基本颜色 */
typedef enum {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    VIOLET,
    COLOR_BUTT
} color_e;

#endif // !__TYPES_H