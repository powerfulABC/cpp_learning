# stream
流的优点
- 更好的类型安全性（对流字符串的类型进行检查）
- 可扩展
- 具有面向对象特性

缺点
- 比较啰嗦
- 运行比较慢



## 什么是流
流是一维单方向的，流向固定，可以通过长度得到固定的流字符串

||Input|Output|Header|
|:----|:----|:----|:----|
|Generic|istream|ostream|\<iostream>|
|File|ifstream|ofstream|\<fstream>|
|C string|istringstream|ostringstream|\<sstream>|
||

## 流操作
- Extractors
    - 从流中读值
    - 重载 >> operator
- Inserters
    - 往流中插入值
- Manipulators
    -改变流的状态(比如精度，宽度设定等)


## 流的类型
- 文本流(解析和格式化)
    - 处理ascii文本
    - 执行字符串转换
    - 包括
        - 文件
        - 字符缓冲区
- 二进制
    - 二进制数据
    - 不进行转换

## 预先定义的流对象
- cin
    - standard input
- cout
    - standard output
- cerr
    - unbuffered error(debugging) output
- clog
    - buffered error(debugging) output

## Manipulators

|manipulator|effect|type|
|:----|:----|:----|
|dec,hex, oct|set numeric conversion|I, O|
|endl|insert newline and flush|O|
|flush|flush stream|O|
|setw(int)|setfield width|I, O|
|setfill(ch)|change fill character|I, O|
|setbase(int)|set number base|O|
|ws|skip whitespace|I|
|setprecision(int)|set floating point precision|O|
|setiosflags(long)|turn on specified flags|I, O|
|resetiosflags(long)|turn off specified flags|I, O|
||

创建manipulators

        // skeleton for an output stream manipulator
        ostream& tab(ostream& out)
        {   
            return out << '\t';
        }
## Stream flags control formatting

|flag|purpose(when set)|
|:----|:----|
|ios::skipws|skip leading white space|
|ios::left, ios::right|justification|
|ios::interal|pad between sign and value|
|ios::dec, ios::oct, ios::hex|format for numbers|
|ios::showbase|show base of number|
|ios::showpoint|always show decimal point|
|ios::uppercase|put base in uppercase|
|ios::showpos|display+on positive numbers|
|ios::scientific, ios::fixed|floating point format|
|ios::unitbuf|flush on every write|
||

- Using manipulators set flags
    - setiosflags(flags);
    - resetiosflags(flags);

- Using stream member functions
    - setf(flags)
    - unsetf(flags);