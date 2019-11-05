//
//  main.cpp
//  SortAlgos
//
//  Created by 杜家昊 on 2019/9/22.
//  Copyright © 2019 杜家昊. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

void InsertSort(vector<int> &arr) {
    int temp, j;
    for (int i = 0; i < arr.size(); i++) {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && temp < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void mySwap(int *pa, int *pb) {
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

void BubbleSort(vector<int> &arr, int begin, int end) {
    bool isLoop = true;
    for (int i = end; true == isLoop && i > begin; --i) {
        isLoop = false;
        for (int j = begin + 1; j < i; ++j) {
            if (arr[j] < arr[j - 1]) {
                mySwap(&arr[j], &arr[j - 1]);
                isLoop = true;
            }
        }
    }
}

/*快速排序
 1.以第一个元素为标杆
 2.从后端开始找第一个小于标杆的元素，放到数组的最前面
 3.从前端开始找第一个大于标杆的元素，放到数组的最后面
 4.当所有比标杆小的元素全在数组头部，大的q元素全在数组尾部时，此时的begin值即为标杆应该插入的位置
 5.以标杆的位置分成两组，再分别进行上述操作
 */

int Partition(vector<int> &arr, int begin, int end) {
    int pivot = arr[begin];
    while (begin < end) {
        while (begin < end && arr[end] >= pivot) --end;
        arr[begin] = arr[end];
        while (begin < end &&arr[begin] <= pivot) ++begin;
        arr[end] = arr[begin];
    }
    arr[begin] = pivot;
    return begin;
}

void QuickSort(vector<int> &arr, int begin, int end) {
    if (begin < end) {
        int PiotPosition = Partition(arr, begin, end);
        
        QuickSort(arr, begin, PiotPosition - 1);
        QuickSort(arr, PiotPosition + 1, end);
    }
}

/*堆排序
 1.建堆：从最后一个非叶子结点开始调整，m若不满足条件，每次选大的叶子结点与根结点交换，
        然后检查交换后的子树是否满足条件
 2.输出根节点，并与与arr[end]结点进行交换，然后调整
 */

void AdjustDown(vector<int> &arr, int begin, int end) {
    int parent = begin;
    int child = begin * 2 + 1;

    for ( ; child < end; parent = child, child = parent * 2 + 1) {
        if ((child < end - 1) && (arr[child] < arr[child + 1])) ++child;
        
        if (arr[child] > arr[parent]) mySwap(&arr[child], &arr[parent]);
        else break;
    }
}

void BuildMaxHeap(vector<int> &arr, int begin, int end) {
    if (begin >= end - 1)
        return;

    int parent = end / 2 - 1;
    while (parent >= 0) {
        AdjustDown(arr, parent, end);
        --parent;
    }
}

void HeapSort(vector<int> &arr, int begin, int end) {
    BuildMaxHeap(arr, begin, end);
    
    while(end > 1) {
        mySwap(&arr[0], &arr[--end]);
        AdjustDown(arr, 0, end);
    }
}

void InsertSort(vector<int> &arr, int begin, int end) {
    for (int i = begin + 1; i < end; i++) {
        if (arr[i] < arr[i - 1]) {
            int temp = arr[i];
            int j;
            for (j = i - 1; temp < arr[j]; --j) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = temp;
        }
    }
}

/*希尔排序
 1.将数组分成(end-begin)/2组
 2.从i=0位置开始，该组内若有小的排在后面了，就寻找插入的位置，即该组内第一个比该值大的d数字的位置
 */

void ShellSort(vector<int> &arr, int begin, int end) {
    for (int step = (end - begin) / 2; step > 0; step /= 2) {
        for (int i = step; i < end; ++i) {
            if (arr[i] < arr[i - step]) {
                int temp = arr[i];
                int j;
                for (j = i - step; j >= 0 && arr[j] > temp; j -= step) {
                    arr[j + step] = arr[j];
                }
                arr[j + step] = temp;
            }
        }
    }
}

/*基数排序
 1.找到最大值，然后根据最大值的位数确定循环次数
 2.从个位数开始计算个位数字相同的个数
 3.从0开始计算排名，比如：个位数字小于0的有几个，小于1的有几个
 4。按排名将实际要排序的数字存入临时数组后再转存到arr
 */

int max(vector<int> &arr) {
    int m = 0;
    for (int i = 0; i  < arr.size(); i++) {
        m = arr[i] > m ? arr[i] : m;
    }
    return m;
}

void CountSort(vector<int> &arr) {
    int m = max(arr);
    int *pTemp = new int[arr.size()];
    for (int i = 1; m / i != 0; i *= 10) {
        int bucket[10] = {0};
        
        for (auto const val : arr) ++bucket[(val / i) % 10];
        for (int j = 1; j < 10; ++j) bucket[j] += bucket[j - 1];
        for (int j = 0; j < 10; j++) cout << "bucket:" << bucket[j] << endl;
        for (int j = 0; j < arr.size(); j++) pTemp[ --bucket[(arr[j] / i) % 10] ] = arr[j];
        for (int j = 0; j < arr.size(); j++) cout << "arr:" << pTemp[j] << endl;
        for (int j = 0; j < arr.size(); j++) arr[j] = pTemp[j];
    }
    delete [] pTemp;
}

/*归并排序
 1.将arr平均分成两组
 2.将arr赋值给临时数组
 3.将已经有序的两组按大小顺序将原数组arr中的值替换
 4.将未插入的值直接接在arr后面
 */

void MergeSortInOrder(vector<int> &arr, int begin, int mid, int end) {
    int *B = (int*)malloc((end - begin) * sizeof(int));
    for (int i = begin; i <= end; i++) {
        B[i] = arr[i];
    }
    int i, j , k;
    for (i = begin, j = mid + 1, k = begin; i <= mid && j <= end; k++) {
        if (B[i] <= B[j]) arr[k] = B[i++];
        else arr[k] = B[j++];
    }
    while (i <= mid) arr[k++] = B[i++];
    while (j <= end) arr[k++] = B[j++];
}

void MergeSort(vector<int> &arr, int begin, int end) {
    if (begin > end - 1) return;

    int mid = (begin + end) / 2;
    MergeSort(arr, begin, mid);
    MergeSort(arr, mid + 1, end);
    MergeSortInOrder(arr, begin, mid, end);
}

int main(int argc, const char * argv[]) {
    vector<int> array = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    HeapSort(array, 0, 10);
    for (int i = 0; i < 10; i ++) {
        cout << array[i] << " ";
    }
    return 0;
}
