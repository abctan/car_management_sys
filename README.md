# car_management_sys
重新编写大学写的管理系统

一、使用教程
    1、工程根目录下执行命令 make
    2、生成二进制文件在obj目录下，可执行文件在根目录下,执行 ./car即可运行
    3、要清理工程输入 make clean


二、工程目录细分
.
├── common      存放公共文件，例如链表
├── drv         存放各个功能目录
├── obj         存放编译生成的二进制文件
├── project     主程序目录
├── Makefile    管理整个工程的编译
└── README.md   readme文档