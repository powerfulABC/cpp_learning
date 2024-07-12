# 获取static_bind.cpp的可重定位目标文件
g++ static_bind.cpp -o static_bind.o

# 读取可重定位目标文件static_bind.o的符号表
readelf -s static_bind.o > static_bind.symtab

# 读取可重定位目标文件static_bind.o的section headers
readelf -S static_bind.o > static_bind.sectionheaders

# > 将可重定向文件反汇编成汇编代码
# objdump: 可以用来查看不同格式的二进制文件（如 ELF、PE/COFF 等）的多种信息，包括但不限于程序的汇编代码、符号表、重定位信息等。
# -s, --full-contents: 显示二进制文件的完整内容，即文件的每一个字节都会以十六进制的形式打印出来，并且每行之后跟随着相应的 ASCII 表示
# -d, --disassemble: 反汇编二进制文件的可执行部分
objdump -s -d static_bind.o > static_bind.s