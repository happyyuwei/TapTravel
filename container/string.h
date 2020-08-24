#ifndef TAP_STRING_H
#define TAP_STRING_H

#include <iostream>
#include <cstring>
#include <vector>
#include "vector.h"

namespace TAP
{
    //将两个char*字符串拼成一个String
    //供String内部调用
    char *combine(const char *left, const char *right)
    {
        int left_len = std::strlen(left);
        int right_len = std::strlen(right);
        //重新分配数组，不希望在原有数组上操作，每次拼接都会创建新对象
        //这边好像也内存泄漏了，依旧不知道怎么弄
        char *buff = new char[left_len + right_len + 1];
        int p = 0;
        for (int i = 0; i < left_len; i++)
        {
            buff[p] = left[i];
            p = p + 1;
        }
        for (int i = 0; i < right_len; i++)
        {
            buff[p] = right[i];
            p = p + 1;
        }
        buff[p] = '\0';
        return buff;
    }

    //字符串
    class String : public Vector<char>
    {
    public:
        //构造函数，注意给最后放一个\0的空间
        String(const char *str) : Vector<char>(str, str + std::strlen(str) + 1)
        {
        }
        //默认构造函数
        String() : Vector<char>(1)
        {
            //默认空字符串
            this->push_back('\0');
        }

        //返回字符串长度，不包含\0
        int size()
        {
            return Vector::size() - 1;
        }
        //获取 char* 字符串
        const char *c_str()
        {
            return this->begin();
        }

        //比较两个字符串,若相等返回0
        int compare(const char *str)
        {
            int strLen = std::strlen(str);
            //空字符串相等
            if (strLen == 0 && this->size() == 0)
            {
                return 0;
            }
            //非空字符串，如果长度不等则不等
            if (strLen != this->size())
            {
                return this->c_str()[0] - str[0];
            }
            //逐个比较
            for (int i = 0; i < strLen; i++)
            {
                if (this->c_str()[i] != str[i])
                {
                    return this->c_str()[i] - str[i];
                }
            }
            return 0;
        }

        //是否相等
        bool equals(const char *str)
        {
            return this->compare(str) == 0;
        }

        //寻找substring(char *)在string中的位置，找不到返回-1
        int find(const char *subString)
        {
            int subLen = std::strlen(subString);
            //如果字符串比子字符串还短，则不用比较
            if (this->size() < subLen)
            {
                return -1;
            }
            for (int i = 0; i < this->size(); i++)
            {
                int j = i;
                while (j < this->size() && (j - i) < subLen && (*this)[j] == subString[j - i])
                {
                    if ((j - i) == (subLen - 1))
                    {
                        return i;
                    }
                    j = j + 1;
                }
            }
            return -1;
        }
        //寻找substring在string中的位置，找不到返回-1
        int find(String &subString)
        {
            return this->find(subString.c_str());
        }

        //是否包含子字符串
        bool contains(const char *str)
        {
            return this->find(str) >= 0;
        }

        //追加字符串
        String &append(const char *str)
        {

            char *buffer = combine(this->c_str(), str);
            String &result = *(new String(buffer));
            //感觉导出都在内存泄漏，写个程序心惊胆战，就让他去漏吧
            delete buffer;
            return result;
        }
        String &append(String &str)
        {
            return this->append(str.c_str());
        }

        //获取子字符串，获取从 [start, end)范围的字符串
        //会生成新的对象
        String &subString(int start, int end = -1)
        {
            if (end <= start)
            {
                end = this->size();
            }
            int subLen = end - start;
            //这个buff好像内存泄漏了，我也不知道怎么弄
            char *buff = new char[subLen + 1];
            //
            for (int i = start; i < start + subLen; i++)
            {
                buff[i - start] = this->c_str()[i];
            }
            buff[subLen] = '\0';
            String &result = *(new String(buff));

            //由于buff传入String对象是拷贝一份的，buff本身没有作用了，此处删除是否可以防止内存泄漏？
            delete[] buff;
            return result;
        }
        //替换
        //不对替换当前字符串，而是重新创建于一个新的
        String &replace(const char *oldString, const char *newString)
        {
            //旧字符串索引开始
            int oldIndex = this->find(oldString);
            //如果需要替换的字符串找不到，返回一个新对象
            if (oldIndex < 0)
            {
                return this->subString(0);
            }
            else
            {
                return this->subString(0, oldIndex)
                    .append(newString)
                    .append(this->subString(oldIndex + std::strlen(oldString)));
            }
        }

        //按照分割符分割字符串
        std::vector<String> &split(const char *split)
        {

            std::vector<String> *result = new std::vector<String>();
            String *remainString = &(this->subString(0));
            int index = remainString->find(split);

            if(index<0){
                result->push_back(*(new String(this->c_str())));
            }

            int splitStrLen = std::strlen(split);

            while (index >= 0)
            {
                result->push_back(remainString->subString(0, index));
                //TODO 这里调用delete会出现 Segmentation fault (core dumped)
                //这里不该delete么？？？
                // delete remainString;
                remainString = &(remainString->subString(index + splitStrLen));
                //寻找分割符位置
                index = remainString->find(split);
            }
            return *result;
        }

        //重载加号， 拼接字符串
        friend String &operator+(String &left, String &right)
        {
            return left.append(right);
        }
        //允许直接与const  char *字符串进行拼接
        friend String &operator+(String &left, const char *right)
        {
            return left.append(right);
        }
        friend String &operator+(const char *left, String &right)
        {
            return *(new String(combine(left, right.c_str())));
        }

        // 直接打印引用中的内容
        friend std::ostream &operator<<(std::ostream &out, String &str)
        {
            return out << str.c_str();
        }
        //直接打印指针中的内容
        friend std::ostream &operator<<(std::ostream &out, String *str)
        {
            return out << str->c_str();
        }
    };

} // namespace TAP

#endif