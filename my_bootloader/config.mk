# �����ظ�����
ifeq ($(CONFIG_MK),LIVE)

else
        CONFIG_MK = LIVE

        
		CROSS_COMPILE = arm-linux-

# ����makeָ��
		MAKE = make
# �����������
		CC      = $(CROSS_COMPILE)gcc
# ������������
		LD      = $(CROSS_COMPILE)ld
# ���������ļ�����
		AR      = $(CROSS_COMPILE)ar

# �����ִ���ļ���ʽת������
# ��������һ��Ŀ���ļ������ݵ���һ���ļ���.
# ��ѡ����Խ��и�ʽ��ת��.��ʵ�ʱ�̵�,�õ����ľ���
# ��ELF��ʽ�Ŀ�ִ���ļ�ת��Ϊ�������ļ�
		OBJCOPY = $(CROSS_COMPILE)objcopy

# �����ִ���ļ�ת������������
#��������ʾ�������ļ���Ϣ,�������鿴��������
		OBJDUMP = $(CROSS_COMPILE)objdump

		CPP		= $(CC) -E
		AR		= $(CROSS_COMPILE)ar
		NM		= $(CROSS_COMPILE)nm

		STRIP		= $(CROSS_COMPILE)strip

# ������ļ��������
		ARFLAGS = crv

# ���������ͷ�ļ�·����
		INC_PATH =
# ���� ͷ�ļ�·�����������ļ�
sinclude $(TOPDIR)/inc_path.mk

# C������� ����

		CFLAGS 		:= -Wall -O2 -nostdinc  -fno-builtin  
		CFLAGS      += $(INC_PATH)
# CPP������� ����
		CPPFLAGS   	:= 

# �������� ����
		LDFLAGS := -Bstatic 

# �������� ���������ļ�·����
		LIBS_PATH := -L /usr/lib


 
export MAKE CC LD AR OBJCOPY OBJDUMP CPP AR NM STRIP ARFLAGS CFLAGS CPPFLAGS LDFLAGS LIBS_PATH

endif

