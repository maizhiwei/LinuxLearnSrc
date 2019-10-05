# ����makeָ��
MAKE = make
# �����������
CC      = arm-linux-gcc
# ������������
LD      = arm-linux-ld
# ���������ļ�����
AR      = arm-linux-ar

# �����ִ���ļ���ʽת������
# ��������һ��Ŀ���ļ������ݵ���һ���ļ���.
# ��ѡ����Խ��и�ʽ��ת��.��ʵ�ʱ�̵�,�õ����ľ���
# ��ELF��ʽ�Ŀ�ִ���ļ�ת��Ϊ�������ļ�
OBJCOPY = arm-linux-objcopy

# �����ִ���ļ�ת������������
#��������ʾ�������ļ���Ϣ,�������鿴��������
OBJDUMP = arm-linux-objdump

# ������ļ��������
ARFLAGS = crv

# C������� ����
CFLAGS 		:= -Wall -O2
# CPP������� ����
CPPFLAGS   	:= -nostdinc  -fno-builtin #-nostdlibs 

# �������� ����
LDFLAGS := -Bstatic 

# �������� ���������ļ�·����
LIBS_PATH := -L /usr/lib

# ���������ͷ�ļ�·����
INC_PATH =

# ���� ͷ�ļ�·�����������ļ�
sinclude $(TOP_DIR)/inc_path.mk

# .c -> .o   .S -> .o ���ɹ���
%.o:%.c
	${CC} $(INC_PATH) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(INC_PATH) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<