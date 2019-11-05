#ifndef __MAXHEAP_H
#define __MAXHEAP_H

#include <stdlib.h>
#include <stdio.h>

typedef int MAXHEAP_ELEM;
typedef struct 
{
    int iHeapCapacity;
    int iHeapSize;
    MAXHEAP_ELEM *iDatas;
}MaxHeap;

bool MaxHeapConstructByBuffer(MaxHeap *heap,MAXHEAP_ELEM buff[],int length);
bool MaxHeapDesturct(MaxHeap *heap);
bool MaxHeap_getSize(MaxHeap *heap);
bool MaxHeap_isFull(MaxHeap *heap);
bool MaxHeap_isEmpty(MaxHeap *heap);
void MaxHeap_swap(MAXHEAP_ELEM *a,MAXHEAP_ELEM *b);
void MaxHeap_floating(MaxHeap *heap,int index);
void MaxHeap_sink(MaxHeap *heap, int index);
bool MaxHeap_push(MaxHeap *heap,MAXHEAP_ELEM data);
bool MaxHeap_pop(MaxHeap *heap,int index);
void MaxHeap_printfAll(MaxHeap *heap);

#endif