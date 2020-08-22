# `TAP::String`

字符串类，直接继承于 `TAP::Vector<char>`   

注意：所有字符串操作方法均会生成一个新的字符串，而不是在原有的字符串中进行就该。

## 构造函数
* String(const char *str)       
创建一个包含 str 的字符串。

* String()
默认构造函数，创建一个空字符串。

## 内置方法
* `int size()`    
返回字符串长度，不包含 `\0`    

* `const char *c_str()`     
返回原生  `const char *` 字符串

* `int find(const char *subString)`     
寻找子字符串的位置


* `int find(String &subString)`
寻找子字符串的位置

* `String &append(const char *str)`     
追加

* `String &append(String &str)`     
追加

* `String &subString(int start, int end = -1)`          
获取子字符串

* `String &replace(const char *oldString, const char *newString)`
    
    替换字符串

* `std::vector<String> &split(const char *split)`

    分割字符串
        

## 重载运算符
* 重载 `+` 运算符，拼接字符串。
* 重载 `=` 运算符，可直接使用const char* 字符串赋值。
