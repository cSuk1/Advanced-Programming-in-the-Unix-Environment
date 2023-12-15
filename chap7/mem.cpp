/*******************************************************
 * @file mem.cpp
 * @author Andromeda (ech0uname@qq.com)
 * @brief 存储空间分配
 * @version 0.1
 * @date 2023-12-15
 *
 *
 *******************************************************/

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>

using namespace std;

typedef struct Person
{
    int age;
    string name;
} Person;

int main(int argc, char const *argv[])
{
    // * malloc分配指定字节数的存储区，初始值不确定
    // * 返回值为void指针，需要经过强制类型转换
    Person *p = (Person *)malloc(sizeof(Person));
    p->age = 20;
    p->name = "Andromeda";
    cout << p->name << " is " << p->age << " years old." << endl;
    // * 释放内存
    free(p);

    // * calloc为指定数量指定长度的对象分配存储空间，并将其初始化为0
    Person *p1 = (Person *)calloc(3, sizeof(Person));
    // * 初始化为0
    for (int i = 0; i < 3; i++)
    {
        cout << p1[i].name << " is " << p1[i].age << " years old." << endl;
    }
    p1[0].age = 20;
    p1[0].name = "Jack";
    p1[1].age = 21;
    p1[1].name = "Tom";
    p1[2].age = 22;
    p1[2].name = "Jerry";
    for (int i = 0; i < 3; i++)
    {
        cout << p1[i].name << " is " << p1[i].age << " years old." << endl;
    }

    // * realloc重新分配内存
    // * 扩容到容纳4个Person结构
    p1 = (Person *)realloc(p1, 4 * sizeof(Person));
    p1[3].age = 23;
    p1[3].name = "Dave";
    for (int i = 0; i < 4; i++)
    {
        cout << p1[i].name << " is " << p1[i].age << " years old." << endl;
    }
    // * 释放内存
    free(p1);
    return 0;
}
