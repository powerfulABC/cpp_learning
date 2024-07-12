# > 生成可重定位目标文件
gcc -c main.c -o main.o

# > 查看符号表
readelf -s main.o > main.symtab
