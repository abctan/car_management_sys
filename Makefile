# 工程名称
TARGET := car

# print little=@ more=
Q = @
export Q
# 头文件相对路径，以MakeFile所在文件为根目录
# 这个变量留给用户去配置，后面会将INC_DIRS转换成绝对路径，因为编译器只能识别到绝对路径，
# 之所以填入相对路径，是因为这样对用户来说更加简洁明了。
# 谨记：将丑陋留给自己，把复杂藏在内部
INC_DIRS := include common
# 源文件相对路径，以MakeFile所在文件为根目录
# 同上
SUB_DIRS := common\
			source/car
			

# 静态/动态库路径
LIB_DIRS := lib

# .o文件输出目录，以MakeFile所在文件为根目录
# 同上，以根目录下的output为.o文件输出目录
OUTPUT := output

# CFLAGS += -Wall -Os -g
# CLIBS  += -lpthread

# 将相对路径转换为绝对路径
CUR_DIRS = $(shell pwd)
INC_DIRS := $(patsubst %, $(CUR_DIRS)/%, $(INC_DIRS))
OUTPUT   := $(patsubst %, $(CUR_DIRS)/%, $(OUTPUT))

# 指定编译器工具名称前缀
CROSS_COMPILE ?=
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AS = $(CROSS_COMPILE)as
NM = $(CROSS_COMPILE)nm
MAKE := make

export CC LD AS NM MAKE OUTPUT
# CFLAGS用于C编译器的编译选项。
CFLAGS += $(patsubst %,-I%,$(INC_DIRS))
# CFLAGS += $(patsubst %,-L%,$(LIB_DIRS))
export CFLAGS

ROOTDIR := $(CUR_DIRS)
export ROOTDIR
###############

all: $(TARGET)

$(TARGET): $(OUTPUT) $(SUB_DIRS)
	$(Q)$(CC) $(OUTPUT)/*.o -o $(TARGET)
	$(if $(Q), $(Q)$(info LD   $@ -o $(TARGET)), )

# 创建中间件输出目录
$(OUTPUT):
	mkdir -p $(OUTPUT)

# 执行子目录Makefile
$(SUB_DIRS):
	$(Q)$(MAKE) -C $@

# 清除规则
clean:
	rm -rf $(OUTPUT)/* $(TARGET)

test:
	@echo "${TARGET}"
	@echo "${INC_DIRS}"
	@echo "${SUB_DIRS}"
	@echo "${OUTPUT}"
	@echo "${MAKE}"

.PHONY: all clean $(SUB_DIRS) test