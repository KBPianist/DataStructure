//
//  main.cpp
//  Stack
//
//  Created by 杜家昊 on 2019/2/24.
//  Copyright © 2019 杜家昊. All rights reserved.
//

#include <iostream>
#include <string>
#define STACK_INIT_SIZE 10
#define STACK_MAX_SIZE 50
#define STACK_INCREASE_SIZE 5

using namespace std;

template <typename T>
class Stack {
public:
    Stack();
    ~Stack();
    bool IsEmpty();
    long Length();
    bool GetTop(T &e);
    bool Push(T e);
    bool Pop(T &e);
    bool Traverse();
private:
    T* base;
    T* top;
    int stacksize;
};

template <typename T>
Stack<T>::Stack() : stacksize(STACK_INIT_SIZE){
    base = (T *)malloc(STACK_INIT_SIZE * sizeof(T));
    top = base;
}

template <typename T>
Stack<T>::~Stack() {
    
}
template <typename T>
bool Stack<T>::IsEmpty() {
    if(top == base) return true;
    else return false;
}
template <typename T>
long Stack<T>::Length() {
    return top - base;
}

template <typename T>
bool Stack<T>::GetTop(T &e) {
    if (top == base) return false;
    e = *(top - 1);
    return true;
}

template <typename T>
bool Stack<T>::Push(T e) {
    if (top - base >= stacksize) {
        base = (T*)realloc(base, (stacksize + STACK_INCREASE_SIZE) * sizeof(T));
        stacksize += STACK_INCREASE_SIZE;
        top = base + STACK_INCREASE_SIZE;
    }
    *top ++ = e;
    return true;
}

template <typename T>
bool Stack<T>::Pop(T &e) {
    if (top == base) return false;
    e = * --top;
    return true;
}

int main(int argc, const char * argv[]) {
    Stack<string> test;
    test.Push("hello ");
    test.Push("world ");
    test.Push("!");
    long l = test.Length();
    cout << l << endl;
    while (!test.IsEmpty()) {
        string S;
        test.Pop(S);
        cout << S << endl;
    }
    l = test.Length();
    cout << l << endl;
    return 0;
}
