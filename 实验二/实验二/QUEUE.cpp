#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;


class QUEUE {
    int* const  elems;	//elems申请内存用于存放队列的元素
    const  int  max;	//elems申请的最大元素个数为max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
public:
    QUEUE(int m);		//初始化队列：最多申请m个元素
    QUEUE(const QUEUE& q); 			//用q深拷贝初始化队列
    QUEUE(QUEUE&& q)noexcept;		//用q移动初始化队列
    virtual operator int() const noexcept	//返回队列的实际元素个数
    {
        if (tail >= head)
            return tail - head;
        return max + tail - head;
    }
    virtual int size() const noexcept		//返回队列申请的最大元素个数max
    {
        return max;
    }
    virtual QUEUE& operator<<(int e)  	//将e入队列尾部，并返回当前队列
    {
        if (head == (tail + 1) % max)
            throw "QUEUE is full!";
        else {
            elems[tail] = e;
            tail = (tail + 1) % max;
        }
        return *this;
    }
    virtual QUEUE& operator>>(int& e) 	//从队首出元素到e，并返回当前队列
    {
        if (head == tail) {
            e = 0;
            throw "QUEUE is empty!";
        }
        else {
            e = elems[head];
            head = (head + 1) % max;
        }
        return *this;
    }
    virtual QUEUE& operator=(const QUEUE& q)//深拷贝赋值并返回被赋值队列
    {
        if (this == &q)
            return *this;
        if (elems)
            delete[]elems;
        (int&)max = q.max;
        (int*&)elems = new int[q.max];
        head = q.head;
        tail = q.tail;
        for (int i = 0; i < max; i++)
            *(elems+i) = *(q.elems+i);
        return *this;
    }
    virtual QUEUE& operator=(QUEUE&& q)noexcept//移动赋值并返回被赋值队列
    {
        if (this == &q)
            return *this;
        if (elems)
            delete[]elems;
        head = q.head;
        tail = q.tail;
        *(int*)&max = q.max;
        *(int**)&elems = q.elems;
        *(int**)&q.elems = 0;
        *(int*)&q.max = 0;
        q.head = q.tail = 0;
        return *this;
    }
    virtual char* print(char* s) const noexcept//打印队列至s尾部并返回s：s[0]=’\0’
    {
        int num_len = 0, num, i;
        for ( i = head; i !=tail; i=(i+1)%max) {
            num = elems[i];
            char* s_num = new char[0];
            _itoa(num, s_num, 10);
            strcpy(s + num_len, s_num);
            num_len += strlen(s_num);
            s[num_len++] = ' ';
        }
        s[num_len - 1] = '\0';
        //cout << s << endl;
        return s;
    }
    virtual ~QUEUE() 					//销毁当前队列
    {
        if (elems) {
            delete[] elems;
            (int*&)elems = 0;
            tail = 0;
            head = 0;
            (int*&)(max) = 0;
        } 
    }
};

QUEUE::QUEUE(int m) : elems(new int[m]), max(m) {
    head = tail = 0;
}

QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]),max(q.max) { 			//用q深拷贝初始化队列
    head = q.head;
    tail = q.tail;
    for (int i = 0; i < max; i++)
        *(elems+i) = q.elems[i];
}

QUEUE::QUEUE(QUEUE&& q)noexcept : elems(q.elems), max(q.max), head(q.head), tail(q.tail) {
    *(int**)&q.elems = 0;
    *(int*)&q.max = 0;
    q.head = q.tail = 0;
}
extern const char* TestQUEUE(int& s);
int main() {
    int a = 0;
    const char* b;
    b = TestQUEUE(a);
    cout << b;
    cout << a;
}