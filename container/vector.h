#ifndef TAP_VECTOR_H
#define TAP_VECTOR_H

#include <iostream>
#include <cstring>

//c++模板连接好像坑很大，所以实现干脆全部放在头文件里
namespace TAP
{
    template <class T>
    class Vector
    {
    private:
        //存储空间
        T *_arr = nullptr;
        //长度
        int _max_size;
        //当前长度
        int _size;
        //空间分配，仅仅内部调用
        void allocate()
        {
            //初始化
            if (this->_arr == nullptr)
            {
                //分配空间
                this->_arr = new T[this->_max_size];
                // std::cout << "initial array, max_size=" << _max_size << ", current size: " << _size << "\n";
            }
            //如果当前尺寸已满，则扩大两倍
            else if (this->_max_size == this->_size)
            {
                //空间分配，默认以两倍尺寸增长
                int allocate_time = 2;
                //临时分配
                T *dest = new T[allocate_time * this->_max_size];
                //拷贝原始内容
                //memcpy最后一个参数是要复制的字节数，而不是元素数，因此要计算每个元素占的字节数！！！
                //特么大坑
                std::memcpy(dest, this->_arr, this->_max_size * sizeof(T));
                //更新尺寸
                this->_max_size = allocate_time * this->_max_size;
                //删除之前的内容
                delete[] this->_arr;
                //指向新地址
                this->_arr = dest;

                //std::cout << "reallocate array: " << _max_size << ", current size: " << _size << "\n";
            }
            else
            {
                //如果当前空间够，则不分配
            }
        }

    public:
        typedef T *iterator;
        //构造函数
        //创建一个空的vector，初始大小为 1
        Vector() : _max_size{1}, _size{0}
        {
            allocate();
        }
        //创建vector，初始空间大小为自定义size
        Vector(int size) : _max_size{size}, _size{0}
        {
            allocate();
        }
        //创建一个vector，元素个数为size,且值均为initVale
        Vector(int size, const T &initValue) : _max_size{size}, _size{0}
        {
            allocate();
            //初始化
            for (int i = 0; i < this->_max_size; i++)
            {
                //不知道直接放入可不可以
                this->push_back(initValue);
            }
        }

        //创建一个包含array中begin到end所有元素的vector
        Vector(const T *begin, const T *end) : _max_size{(int)(end - begin)}, _size{(int)(end - begin)}
        {
            allocate();
            std::memcpy(this->_arr, begin, this->_max_size * sizeof(T));
        }

        //raii----------------------------------------------------------------------------------------
        //拷贝构造函数
        //现代编译器早就已经可以优化深拷贝的
        //但为了应付考试，只能输入 -fno-elide-constructors 关闭优化
        //然后自己写这几个该死的拷贝函数
        //由于今天是学习内存管理的第三天，因此用自己写的构造函数总是感到心惊胆战
        Vector(const Vector &vector)
            : _max_size{vector._max_size}, _size{vector._size}, _arr{new T[vector._max_size]}
        {
            //复制一份数组
            std::memcpy(this->_arr, vector._arr, this->_max_size * sizeof(T));
        }
        //不知道什么构造函数，抄ppt的，据说使用临时表量初始化时调用，比如把函数的返回值作为初始值。
        Vector(Vector &&vector)
            : _max_size{vector._max_size}, _size{vector._size}, _arr{vector._arr}
        {
            //将临时变量里的数组空间清空
            vector._arr = nullptr;
        }

        //在等号赋值的时候调用，愈发不知道在做什么,o(╥﹏╥)o
        Vector &operator=(Vector &&vector)
        {
            std::swap(vector._arr, this->_arr);
            std::cout << "right copy\n";
            return *this;
        }

        Vector &operator=(const Vector &vector)
        {
            std::cout << "const copy\n";
            Vector temp{vector};
            std::swap(temp._arr, this->_arr);
            return *this;
        }

        //析构
        ~Vector()
        {
            delete[] this->_arr;
        }

        //方法---------------------------------------------------------------------------------------------
        //返回向量中元素的个数
        int size() const
        {
            return this->_size;
        }
        //返回当前向量所能容纳的最大元素值
        int capicity() const
        {
            return this->_max_size;
        }
        //判断向量是否为空，若为空，则向量中无元素
        bool empty() const
        {
            return this->_size == 0;
        }
        //清空
        void clear()
        {
            //清空元素
            delete[] this->_arr;
            this->_max_size = 1;
            this->_size = 0;
            this->_arr = nullptr;
            //重新分配
            allocate();
        }
        //拷贝
        void push_back(const T &x)
        {
            //检测内存
            allocate();
            //存储
            this->_arr[this->_size] = x;
            //数量加一
            this->_size = this->_size + 1;
        }
        //删除向量中最后一个元素
        T &pop_back()
        {
            //只有当存在元素时才允许删除
            if (this->_size > 0)
            {
                this->_size = this->_size - 1;
                return this->_arr[this->_size];
            }
            throw "Out of range.";
        }

        //到数组头的指针
        iterator begin()
        {
            return &(this->_arr[0]);
        }

        //得到数组的最后一个单元+1的指针
        iterator end()
        {
            return &(this->_arr[this->_size]);
        }

        //重载运算符----------------------------------------------------------------------------------------
        //重载下标索引
        T &operator[](int index)
        {
            return this->_arr[index];
        }
        //重构输出流，我不知道为什么标准库不提供这样的方法
        //直接打印引用中的内容
        friend std::ostream &operator<<(std::ostream &out, const Vector &vector)
        {
            out << "Vector[";
            for (int i = 0; i < vector._size - 1; i++)
            {
                out << vector._arr[i] << ", ";
            }
            //修复_size等于0时数组越界的问题
            if (vector._size >= 1)
            {
                return out << vector._arr[vector._size - 1] << "]";
            }
            else
            {
                return out << "]";
            }
        }
        //直接打印指针中的内容
        friend std::ostream &operator<<(std::ostream &out, const Vector *vector)
        {
            //最后一个元素后面不用加逗号
            return out << *vector;
        }
    };
}; // namespace TAP

#endif
