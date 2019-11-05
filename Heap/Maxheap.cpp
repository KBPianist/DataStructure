#include "MaxHeap.h"

bool MaxHeapConstructByBuffer(MaxHeap *heap,MAXHEAP_ELEM buff[],int length)
{
    int i;
    if(NULL != heap->iDatas)
    {
        return false;
    }
    heap->iHeapCapacity=length;
    heap->iHeapSize=0;
    heap->iDatas = (MAXHEAP_ELEM*)malloc(sizeof(MAXHEAP_ELEM)*length);
    for(i=0;i<length;i++)
    {
        MaxHeap_push(heap,buff[i]);
    }
    return true;
}

bool MaxHeapDesturct(MaxHeap *heap)
{
    if(NULL == heap->iDatas)
    {
        return false;
    }
    free(heap->iDatas);
    return true;
}

bool MaxHeap_getSize(MaxHeap *heap)
{
    return heap->iHeapSize;
}

bool MaxHeap_isFull(MaxHeap *heap)
{
    if(heap->iHeapCapacity == heap->iHeapSize)
    {
        return true;
    }
    return false;
}

bool MaxHeap_isEmpty(MaxHeap *heap)
{
    if(0 == heap->iHeapSize)
    {
        return true;
    }
    return false;
}

void MaxHeap_swap(MAXHEAP_ELEM *a,MAXHEAP_ELEM *b)
{
    MAXHEAP_ELEM temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void MaxHeap_floating(MaxHeap *heap,int index)
{
    int i;
    for(i=index;i>0;i=(int)(i*0.5))
    {
        if(heap->iDatas[i-1] > heap->iDatas[(int)(i*0.5-1)] )
        {
            MaxHeap_swap(&heap->iDatas[i-1],&heap->iDatas[(int)(i*0.5-1)]);
        }
        else 
        {
            break;
        }
    }    
}


void MaxHeap_sink(MaxHeap *heap, int index)
{
    int i=index;

    while(i*2<=heap->iHeapSize)
    {
        if(heap->iDatas[i-1] < heap->iDatas[i*2-1])//it compare to left child
        {
            MaxHeap_swap(&heap->iDatas[i-1],&heap->iDatas[i*2-1]);
            if(i*2+1<=heap->iHeapSize && heap->iDatas[i-1] < heap->iDatas[i*2])//it compare to right child
            {
                MaxHeap_swap(&heap->iDatas[i-1],&heap->iDatas[i*2]);            
            }
            /*index*/
            i=i*2;
        }
        else if(i*2+1<=heap->iHeapSize && heap->iDatas[i-1] < heap->iDatas[i*2])//it compare to right child
        {
            MaxHeap_swap(&heap->iDatas[i-1],&heap->iDatas[i*2]);
            i=i*2+1;
        }
        else
        {
            break;
        }
    }    
}

bool MaxHeap_push(MaxHeap *heap,MAXHEAP_ELEM data)
{
    if( MaxHeap_isFull(heap))
        return false;
    heap->iDatas[heap->iHeapSize]=data;
    heap->iHeapSize++;
    MaxHeap_floating(heap,heap->iHeapSize);

    return true;
}

bool MaxHeap_pop(MaxHeap *heap,int index)
{
    if(MaxHeap_isEmpty(heap))
        return false;
    heap->iDatas[index]=heap->iDatas[heap->iHeapSize-1];
    heap->iHeapSize--;
    MaxHeap_sink(heap,index+1);

    return true;
}

void MaxHeap_printfAll(MaxHeap *heap)
{
    int i;
    printf("heap:");
    for( i=0;i<heap->iHeapSize;i++)
    {
        printf("%d ",heap->iDatas[i]);
    }
    printf("\r\n");
}