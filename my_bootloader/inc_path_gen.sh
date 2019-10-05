#!/bin/bash
# 删除之前生成的文件
rm -f inc_path.mk
# 寻找目录下所有的头文件，提取其绝对路径，并过滤掉重复的路径
find -name '*.h' | sed 's#^.#'${PWD}'#g' | sed 's#/[^/]*.h##g' | sed 's#^.*$#INC_PATH += -I &#' | sort | uniq > inc_path.mk

#备用的功能:搜索目录下所有include 或 inc的目录，并转成编译选项
#find -type d -name 'include' | sed 's#^.#'${PWD}'#g'| sed 's#^.*$#INC_PATH += -I &#' > inc_path.mk
#find -type d -name 'inc' | sed 's#^.#'${PWD}'#g'| sed 's#^.*$#INC_PATH += -I &#' >> inc_path.mk
