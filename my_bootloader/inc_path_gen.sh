#!/bin/bash
# ɾ��֮ǰ���ɵ��ļ�
rm -f inc_path.mk
# Ѱ��Ŀ¼�����е�ͷ�ļ�����ȡ�����·���������˵��ظ���·��
find -name '*.h' | sed 's#^.#'${PWD}'#g' | sed 's#/[^/]*.h##g' | sed 's#^.*$#INC_PATH += -I &#' | sort | uniq > inc_path.mk

#���õĹ���:����Ŀ¼������include �� inc��Ŀ¼����ת�ɱ���ѡ��
#find -type d -name 'include' | sed 's#^.#'${PWD}'#g'| sed 's#^.*$#INC_PATH += -I &#' > inc_path.mk
#find -type d -name 'inc' | sed 's#^.#'${PWD}'#g'| sed 's#^.*$#INC_PATH += -I &#' >> inc_path.mk
