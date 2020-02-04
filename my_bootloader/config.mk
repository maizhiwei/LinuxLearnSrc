# 避免重复加载
ifeq ($(CONFIG_MK),LIVE)

else
        CONFIG_MK = LIVE

        
		CROSS_COMPILE = arm-linux-

# 保存make指令
		MAKE = make
# 保存编译命令
		CC      = $(CROSS_COMPILE)gcc
# 保存链接命令
		LD      = $(CROSS_COMPILE)ld
# 保存打包库文件命令
		AR      = $(CROSS_COMPILE)ar

# 保存可执行文件格式转换命令
# 用来复制一个目标文件的内容到另一个文件中.
# 此选项可以进行格式的转换.在实际编程的,用的最多的就是
# 将ELF格式的可执行文件转换为二进制文件
		OBJCOPY = $(CROSS_COMPILE)objcopy

# 保存可执行文件转反汇编代码命令
#常用来显示二进制文件信息,常用来查看反汇编代码
		OBJDUMP = $(CROSS_COMPILE)objdump

		CPP		= $(CC) -E
		AR		= $(CROSS_COMPILE)ar
		NM		= $(CROSS_COMPILE)nm

		STRIP		= $(CROSS_COMPILE)strip

# 打包库文件命令参数
		ARFLAGS = crv

# 编译参数（头文件路径）
		INC_PATH =
# 加载 头文件路径变量配置文件
sinclude $(TOPDIR)/inc_path.mk

# C代码编译 参数

		CFLAGS 		:= -Wall -O2 -nostdinc  -fno-builtin  
		CFLAGS      += $(INC_PATH)
# CPP代码编译 参数
		CPPFLAGS   	:= 

# 链接命令 参数
		LDFLAGS := -Bstatic 

# 链接命令 参数（库文件路径）
		LIBS_PATH := -L /usr/lib


 
export MAKE CC LD AR OBJCOPY OBJDUMP CPP AR NM STRIP ARFLAGS CFLAGS CPPFLAGS LDFLAGS LIBS_PATH

endif

