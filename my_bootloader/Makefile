# 获取顶层目录绝对路径
TOP_DIR = $(shell /bin/pwd)


# 加载编译规则
include $(TOP_DIR)/config.mk

##############以下区间的变量需按照实际项目配置######################
# 定义可执行文件前缀
OBJ_NAME = bootloader

# 定义程序入口的目标文件
START_OBJ = startup/Start.o

# 定义参与编译的各个子目录的库文件
# 注意事项：库文件名必须与当前目录名相同
#LIBS  = startup/startup.a
LIBS = boot/boot.a
LIBS += hw/hw.a

######################################

export	TOP_DIR OBJ_NAME

# 把所有目标都标记伪目标，避免因存在同名的文件导致目标不执行
.PHONY : config unconfig clean distclean $(OBJ_NAME).bin mfclean $(LIBS) $(START_OBJ)

# 总目标--生成镜像文件
ALL:   $(OBJ_NAME).bin

# 目标--把所有的库链接成镜像文件
$(OBJ_NAME).bin: $(START_OBJ)   $(LIBS)
# $@--目标文件，$^--所有的依赖文件，$<--第一个依赖文件。
# 生成可执行文件$(OBJ_NAME).elf，并输出$(OBJ_NAME).map文件
	${LD} $(LIBS_PATH) $(LDFLAGS) -T$(OBJ_NAME).lds $(START_OBJ) --start-group $(LIBS) --end-group -o $(OBJ_NAME).elf  -Map $(OBJ_NAME).map
# $@ 代表 $(OBJ_NAME).bin
# 把$(OBJ_NAME).elf 转换成$(OBJ_NAME).bin
	${OBJCOPY} -O binary -S $(OBJ_NAME).elf $@
# 生成反汇编信息
	${OBJDUMP} -D -m arm $(OBJ_NAME).elf > $(OBJ_NAME).dis

# 目标--生成程序入口目标文件
# 过程：1.进入目标子目录
#             2.判断目录下有没有Makefile，有的话，直接执行make
#             3.没有的话，则创建Makefile并链接到顶层目录下SubMakefile,执行make
$(START_OBJ):
		cd $(dir $@); \
		a=$@; \
		b=`echo $$a | awk -F '/' '{print NF}'`; \
		if [ -e Makefile ];then \
			$(MAKE); \
		else \
			c=""; \
			for i in `seq 2 $$b`; do \
		    	c=$$c../; done; \
		    c=$${c}SubMakefile; \
			ln -s $$c Makefile; \
       		$(MAKE); \
		fi
		cd $(TOP_DIR);
		
		#ln -s $(TOP_DIR)/SubMakefile Makefile; \
		#cd $(dir $@) && rm -f Makefile && ln -s $(TOP_DIR)/SubMakefile Makefile && $(MAKE) && cd $(TOP_DIR)
		#$(MAKE) -C $(dir $@)

# 测试用途-功能：进入每个.a的目录，执行make
test:
	@for f in $(LIBS); do \
			g=`echo $$f | sed 's#/[^/]*.a##g'`; \
			cd $$g; \
			$(MAKE); \
			cd $(TOP_DIR); \
	done
	
# 目标--生成各个子目录下的库文件
# 过程：1.进入目标子目录
#             2.判断目录下有没有Makefile，有的话，直接执行make
#             3.没有的话，则创建Makefile并链接到顶层目录下SubMakefile,执行make
$(LIBS):
		cd $(dir $@); \
		a=$@; \
		b=`echo $$a | awk -F '/' '{print NF}'`; \
		if [ -e Makefile ];then \
			$(MAKE); \
		else \
			c=""; \
			for i in `seq 2 $$b`; do \
		    	c=$$c../; done; \
		    c=$${c}SubMakefile; \
			ln -s $$c Makefile; \
       		$(MAKE); \
		fi
		cd $(TOP_DIR);
		
		#ln -s $(TOP_DIR)/SubMakefile Makefile; \
		#cd $(dir $@) && rm -f Makefile && ln -s $(TOP_DIR)/SubMakefile Makefile && $(MAKE) && cd $(TOP_DIR)
		#$(MAKE) -C $(dir $@)

# 目标--删除所有链接的Makefile文件
mfclean:
		find -type l \( -name Makefile \) -print0 | xargs -0 rm -f


# 目标--执行顶层的头文件路径生成shell脚本	（inc_path_gen.sh）
config: unconfig
	 $(shell $(TOP_DIR)/inc_path_gen.sh)

# 目标--删除inc_path_gen.sh所生成的路径变量配置文件（inc_path.mk）
unconfig:
	rm -f inc_path.mk

# 目标--顶层目录下的镜像文件
clean: 
	rm -f  $(OBJ_NAME).bin $(OBJ_NAME).elf $(OBJ_NAME).dis

# 目标--把所有编译链接生成的相关文件都删掉
distclean: unconfig
	find -type f \( -name .depend \
	  -o -name '*.o' -o -name '*.bin' -o -name '*.a' -o -name '*.bak' \
	   \) -print0 | xargs -0 rm -f

