# `TAP::Vector<T>`

可变长度数组，内部使用连续内存存储。

## 私有属性
```cpp
 //存储空间
 T *_arr = nullptr;

 //存储空间长度
 int _max_size;

 //当前存放的元素个数
 int _size;
```

## 构造函数

* `Vector()`   
默认构造函数，创建一个空的列表。

* `Vector(int size)`    
创建一个初始尺寸大小为size的列表。

* `Vector(int size, const T &initValue)`    
创建一个初始尺寸大小为size的列表，并且用initValue初始化。

* `Vector(const T *begin, const T *end)`    
创建一个包含array中begin到end所有元素的vector。

## 内置方法
* `int size() const`    
返回列表中元素的个数

* `int capicity() const`    
返回当前列表所能容纳的最大元素值

* `bool empty() const`  
判断列表是否为空，若为空，则列表中无元素

* `void clear()`    
清空所有元素

* `void push_back(const T &x)`  
在列表结尾添加

* `T &pop_back()`   
删除列表结尾的元素

* `iterator begin()`    
返回列表第一个元素的指针。注：`iterator`实际上就是 `T *` 的别名，定义在公共区，`typedef T *iterator`。可用于迭代遍历。

* `iterator end()`  
返回列表最后一个元素+1的指针

## 重载运算符
* `T &operator[](int index)`
重载下标索引，允许直接通过下标索引    

* `friend std::ostream &operator<<(std::ostream &out, const Vector &vector)`    
重载输出流，允许直接通过引用打印整个列表

* `friend std::ostream &operator<<(std::ostream &out, const Vector *vector)`
重载输出流，允许直接通过指针打印整个列表
