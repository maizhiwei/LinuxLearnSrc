
TOPDIR := $(shell pwd)

# 加载编译规则
include $(TOPDIR)/config.mk

export TOPDIR

OBJ_NAME := bootloader

START_OBJ := Start.o

#LIBS  = startup/startup.a

obj-m := $(START_OBJ)
obj-y := boot/
obj-y += hw/

.PHONY : $(OBJ_NAME).bin

# 目标--把所有的库链接成镜像文件
$(OBJ_NAME).bin:   

	make -C ./ -f $(TOPDIR)/Makefile.build
# $@--目标文件，$^--所有的依赖文件，$<--第一个依赖文件。
# 生成可执行文件$(OBJ_NAME).elf，并输出$(OBJ_NAME).map文件
	${LD}  $(LDFLAGS) -T$(OBJ_NAME).lds $(START_OBJ) built-in.o  -o $(OBJ_NAME).elf  -Map $(OBJ_NAME).map
# $@ 代表 $(OBJ_NAME).bin
# 把$(OBJ_NAME).elf 转换成$(OBJ_NAME).bin
	${OBJCOPY} -O binary -S $(OBJ_NAME).elf $@
# 生成反汇编信息
	${OBJDUMP} -D -m arm $(OBJ_NAME).elf > $(OBJ_NAME).dis


clean:
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET)

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)

	# 目标--执行顶层的头文件路径生成shell脚本	（inc_path_gen.sh）
config: unconfig
	 $(shell $(TOPDIR)/inc_path_gen.sh)

# 目标--删除inc_path_gen.sh所生成的路径变量配置文件（inc_path.mk）
unconfig:
	rm -f inc_path.mk
	