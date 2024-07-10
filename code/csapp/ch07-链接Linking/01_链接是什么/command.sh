# > 生成main.o
# 预编译: 执行预编译指令
# cpp : c preprocessor(c预处理器)
cpp main.c -o main.i
# gcc -E main.c -o main.i


# 汇编：将ascill码文件翻译为汇编文件
# cc: c compiler(c编译器)
cc -S main.i -o main.s
# gcc -S main.i -o main.s

# 编译：将汇编文件编译为二进制文件
# as: assembler(汇编器)
as main.s -o main.o

# > 生成sum.o
gcc -E sum.c -o sum.i
gcc -S sum.i -o sum.s
as sum.s -o sum.o


# > 链接生成可执行文件
ld -static -o prog main.o sum.o /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/11/crtbeginT.o -L/usr/lib/gcc/x86_64-linux-gnu/11 -L/usr/lib --start-group -lgcc -lgcc_eh -lc --end-group /usr/lib/gcc/x86_64-linux-gnu/11/crtend.o /usr/lib/x86_64-linux-gnu/crtn.o