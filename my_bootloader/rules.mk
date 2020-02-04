.PHONY : .depend _depend

_depend:	.depend

# Ŀ��--����������ϵ�ļ�.depend
# ����: 1. ɾ��.depend�ļ�
#             2. ���Ŀ¼�����е�.c�ļ�����һ����������ϵ����д�뵽.depend�ļ���
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