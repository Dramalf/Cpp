#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;


class QUEUE {
    int* const  elems;	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	//elems��������Ԫ�ظ���Ϊmax
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
public:
    QUEUE(int m);		//��ʼ�����У��������m��Ԫ��
    QUEUE(const QUEUE& q); 			//��q�����ʼ������
    QUEUE(QUEUE&& q)noexcept;		//��q�ƶ���ʼ������
    virtual operator int() const noexcept	//���ض��е�ʵ��Ԫ�ظ���
    {
        if (tail >= head)
            return tail - head;
        return max + tail - head;
    }
    virtual int size() const noexcept		//���ض�����������Ԫ�ظ���max
    {
        return max;
    }
    virtual QUEUE& operator<<(int e)  	//��e�����β���������ص�ǰ����
    {
        if (head == (tail + 1) % max)
            throw "QUEUE is full!";
        else {
            elems[tail] = e;
            tail = (tail + 1) % max;
        }
        return *this;
    }
    virtual QUEUE& operator>>(int& e) 	//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
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
    virtual QUEUE& operator=(const QUEUE& q)//�����ֵ�����ر���ֵ����
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
    virtual QUEUE& operator=(QUEUE&& q)noexcept//�ƶ���ֵ�����ر���ֵ����
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
    virtual char* print(char* s) const noexcept//��ӡ������sβ��������s��s[0]=��\0��
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
    virtual ~QUEUE() 					//���ٵ�ǰ����
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

QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]),max(q.max) { 			//��q�����ʼ������
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