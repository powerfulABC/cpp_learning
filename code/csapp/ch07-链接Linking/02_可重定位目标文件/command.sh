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
objdump -s -d main.o > main.s