# �����*.o�Ĺ���
CC      = arm-linux-gcc
# ��*.o���ӳɿ�ִ�еĶ������ļ�
LD      = arm-linux-ld
# �Ѷ��*.o�ļ�����*.a���ļ�
AR      = arm-linux-ar
# ��������һ��Ŀ���ļ������ݵ���һ���ļ���.
# ��ѡ����Խ��и�ʽ��ת��.��ʵ�ʱ�̵�,�õ����ľ���
# ��ELF��ʽ�Ŀ�ִ���ļ�ת��Ϊ�������ļ�
OBJCOPY = arm-linux-objcopy
#��������ʾ�������ļ���Ϣ,�������鿴��������
OBJDUMP = arm-linux-objdump

CFLAGS 		:= -Wall -O2
CPPFLAGS   	:= -nostdinc  -fno-builtin #-nostdlibs

objs := Start.o init.o boot.o

bootloader.bin: $(objs)
# $@--Ŀ���ļ���$^--���е������ļ���$<--��һ�������ļ���
# $^ ���� Start.o init.o boot.o
# ���ɿ�ִ���ļ�bootloader.elf
	${LD} -Tbootloader.lds -o bootloader.elf $^ -Map Bootloader.map
# $@ ���� bootloader.bin
# ��bootloader.elf ת����bootloader.bin
	${OBJCOPY} -O binary -S bootloader.elf $@
# ���ɷ������Ϣ
	${OBJDUMP} -D -m arm bootloader.elf > bootloader.dis
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.bin *.elf *.dis