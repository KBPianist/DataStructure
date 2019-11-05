#include "Heap.h"

Heap::Heap(int length, HEAP_ELEM buff[]) : HeapCapacity(length), HeapSize(0) {
    for(int i = 0; i < length; i++) {
        Push(buff[i]);
    }
}

Heap::~Heap() {
    free(Data);
}

bool Heap::GetSize() {
    return HeapSize;
}

bool Heap::IsFull() {
    if (HeapCapacity == HeapSize) {
        return true;
    }
    return false;
}

bool Heap::IsEmpty() {
    if(0 == HeapSize) {
        return true;
    }
    return false;
}

void Heap::Swap(HEAP_ELEM *a, HEAP_ELEM *b) {
    HEAP_ELEM temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void Heap::Floating(int index) {
    for(int i = index; i > 0; i = (int)(i * 0.5)) {
        if(Data[i - 1] > Data[(int)(i * 0.5 - 1)]) {
            Swap(&Data[i - 1], &Data[(int)(i * 0.5 - 1)]);
        }
        else break;
    }
}

void Heap::Sink(int index) {
    while(index * 2 + 1 <= HeapSize) {
        if(Data[index - 1] < Data[index * 2 - 1]) {
            Swap(&Data[index - 1], &Data[index * 2 - 1]);
            if(index * 2 + 1 <= HeapSize && Data[index - 1] < Data[index * 2]) {
                Swap(&Data[index - 1], &Data[index * 2]);            
            }
            index = index * 2;
        }
        else if(index * 2 + 1 <= HeapSize && Data[index - 1] < Data[index * 2]) {
            Swap(&Data[index - 1], &Data[index * 2]);
            index = index * 2 + 1;
        }
        else break;
    }    
}