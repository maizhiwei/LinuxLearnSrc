# 保存make指令
MAKE = make
# 保存编译命令
CC      = arm-linux-gcc
# 保存链接命令
LD      = arm-linux-ld
# 保存打包库文件命令
AR      = arm-linux-ar

# 保存可执行文件格式转换命令
# 用来复制一个目标文件的内容到另一个文件中.
# 此选项可以进行格式的转换.在实际编程的,用的最多的就是
# 将ELF格式的可执行文件转换为二进制文件
OBJCOPY = arm-linux-objcopy

# 保存可执行文件转反汇编代码命令
#常用来显示二进制文件信息,常用来查看反汇编代码
OBJDUMP = arm-linux-objdump

# 打包库文件命令参数
ARFLAGS = crv

# C代码编译 参数
CFLAGS 		:= -Wall -O2
# CPP代码编译 参数
CPPFLAGS   	:= -nostdinc  -fno-builtin #-nostdlibs 

# 链接命令 参数
LDFLAGS := -Bstatic 

# 链接命令 参数（库文件路径）
LIBS_PATH := -L /usr/lib

# 编译参数（头文件路径）
INC_PATH =

# 加载 头文件路径变量配置文件
sinclude $(TOP_DIR)/inc_path.mk

# .c -> .o   .S -> .o 生成规则
%.o:%.c
	${CC} $(INC_PATH) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(INC_PATH) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<