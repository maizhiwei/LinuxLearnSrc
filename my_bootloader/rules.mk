.PHONY : .depend _depend

_depend:	.depend

# 目标--生成依赖关系文件.depend
# 过程: 1. 删除.depend文件
#             2. 针对目录下所有的.c文件，逐一生成依赖关系，并写入到.depend文件中
.depend:	Makefile $(TOP_DIR)/config.mk $(CRCS) $(SRCS)
		@rm -f $@
		@for f in $(CRCS); do \
			g=`basename $$f | sed -e 's/\(.*\)\.\w/\1.o/'`; \
			$(CC) -M $(INC_PATH) $(CFLAGS) $(CPPFLAGS) -MQ $$g $$f >> $@ ; \
		done
		@for f in $(SRCS); do \
			g=`basename $$f | sed -e 's/\(.*\)\.\w/\1.o/'`; \
			$(CC) -M $(INC_PATH) $(CFLAGS) $(CPPFLAGS) -MQ $$g $$f >> $@ ; \
		done