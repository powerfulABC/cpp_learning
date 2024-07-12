# > 将main.c编译为可重定向目标文件main.o
# gcc -c: 表示只进行编译和汇编，不执行链接
gcc -c main.c -o main.o

# > 统计main.o的字节数
# wc可以统计文件的字节数/字符数, 行数和单词数
# -c , --bytes, --chars: 表示统计文件的字节数
# -l , --lines: 表示统计文件的行数
# -w, --words: 表示统计文件的字数
wc -c main.o


# > 查看elf header具体内容
readelf -h main.o > main.elfheader

# > 打印sections信息
readelf -S main.o > main.elfsectionheaders

# > 将可重定向文件反汇编成汇编代码
# objdump: 可以用来查看不同格式的二进制文件（如 ELF、PE/COFF 等）的多种信息，包括但不限于程序的汇编代码、符号表、重定位信息等。
# -s, --full-contents: 显示二进制文件的完整内容，即文件的每一个字节都会以十六进制的形式打印出来，并且每行之后跟随着相应的 ASCII 表示
# -d, --disassemble: 反汇编二进制文件的可执行部分
objdump -s -d main.o > main.s