#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>

typedef int HEAP_ELEM;

class Heap
{
private:
    int HeapCapacity;
    int HeapSize;
    HEAP_ELEM *Data;
public:
    Heap(int length, HEAP_ELEM buff[]);
    ~Heap();
    bool ConstructByBuffer(HEAP_ELEM buff[],int length);
    bool Desturct();
    bool GetSize();
    bool IsFull();
    bool IsEmpty();
    void Swap(HEAP_ELEM *a,HEAP_ELEM *b);
    void Floating(int index);
    void Sink(int index);
    bool Push(HEAP_ELEM data);
    bool Pop(int index);
    void PrintfAll();
};

#endif