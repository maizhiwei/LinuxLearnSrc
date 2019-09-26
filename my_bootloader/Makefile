# 编译成*.o的工具
CC      = arm-linux-gcc
# 把*.o链接成可执行的二进制文件
LD      = arm-linux-ld
# 把多个*.o文件做成*.a库文件
AR      = arm-linux-ar
# 用来复制一个目标文件的内容到另一个文件中.
# 此选项可以进行格式的转换.在实际编程的,用的最多的就是
# 将ELF格式的可执行文件转换为二进制文件
OBJCOPY = arm-linux-objcopy
#常用来显示二进制文件信息,常用来查看反汇编代码
OBJDUMP = arm-linux-objdump

CFLAGS 		:= -Wall -O2
CPPFLAGS   	:= -nostdinc  -fno-builtin #-nostdlibs

objs := Start.o init.o boot.o

bootloader.bin: $(objs)
# $@--目标文件，$^--所有的依赖文件，$<--第一个依赖文件。
# $^ 代表 Start.o init.o boot.o
# 生成可执行文件bootloader.elf
	${LD} -Tbootloader.lds -o bootloader.elf $^ -Map Bootloader.map
# $@ 代表 bootloader.bin
# 把bootloader.elf 转换成bootloader.bin
	${OBJCOPY} -O binary -S bootloader.elf $@
# 生成反汇编信息
	${OBJDUMP} -D -m arm bootloader.elf > bootloader.dis
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.bin *.elf *.dis
