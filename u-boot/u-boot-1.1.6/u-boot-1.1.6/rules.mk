#
# (C) Copyright 2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

#########################################################################

_depend:	$(obj).depend

#basename $f 意思是去掉路径后的文件名
#sed -e 's/\(.*\)\.\w/\1.o/';  
#  /匹配字符/替换字符/
# (.*).\w: (.*):代表任意个任意字符,小括将其标识为\1, 
# \. : \代表脱义符，\.代表 符号.
# \w : 代表[A-Za-z0-9]
# \1.o : 对应着把匹配上/1.w 替换成 1.o
# 以下shell命令用于生成 依赖关系，并输出到 .depend 文件 
# $(CC) -M $(HOST_CFLAGS) $(CPPFLAGS) -MQ $(obj)$g $f >> $@ ;

# 生成依赖文件只需要.c即可，不需要.o文件

$(obj).depend:	$(src)Makefile $(TOPDIR)/config.mk $(SRCS)
		@echo $(SRCS)
		@echo “This is depend here\n\r”
		@rm -f $@
		@for f in $(SRCS); do \
			g=`basename $$f | sed -e 's/\(.*\)\.\w/\1.o/'`; \
			$(CC) -M $(HOST_CFLAGS) $(CPPFLAGS) -MQ $(obj)$$g $$f >> $@ ; \
		done

#########################################################################
