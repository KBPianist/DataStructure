//
//  main.cpp
//  List
//
//  Created by 杜家昊 on 2019/2/22.
//  Copyright © 2019 杜家昊. All rights reserved.
//

#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;
    
    Node() = default;
    Node(T value, Node* _next) : data(value), next(_next) {}
};

template <typename T>
class List {
public:
    List();
    ~List();
    Node<T>* GetHead();
    int GetLength();
    bool IsEmpty();
    Node<T>* Insert(int index, T e);
    Node<T>* PriorPos(T e);
    void Union(Node<T>* node);
private:
    Node<T>* head;
    Node<T>* tail;
    int length;
};

/* 默认构造函数 */
template <typename T>
List<T>::List() : length(0), tail(NULL) {
    head = new Node<T>();
    head->next = NULL;
}

template <typename T>
List<T>::~List() {
}

template <typename T>
int List<T>::GetLength() {
    return length;
}

template <typename T>
bool List<T>::IsEmpty() {
    if (head->next == NULL) return false;
    else return true;
}

template <typename T>
Node<T>* List<T>::GetHead() {
    return head;
}

/*
 在指定位置之后插入新节点
 若要在指定节点之前插入新节点
 只需将新节点与指定位置的data值交换即可
 */
template <typename T>
Node<T>* List<T>::Insert(int index, T e) {
    Node<T>* p = head;
    for (int i = 0; i < index; i++) p = p->next;
    Node<T>* NewNode = new Node<T>(e, p->next);
    p->next = NewNode;
    length++;
    return NewNode;
}

template <typename T>
Node<T>* List<T>::PriorPos(T e) {
    Node<T>* p1 = head;
    Node<T>* p2 = p1->next;
    while (p2->data != e) {
        p2 = p2->next;
        p1 = p1->next;
    }
    return p1;
}

template <typename T>
void List<T>::Union(Node<T>* node) {
    Node<T>* p = head;
    Node<T>* p1 = head->next;
    Node<T>* p2 = node->next;
    while (p2 && p1) {
        if (p1->data <= p2->data) {
            p->next = p1;
            p1 = p1->next;
            p = p->next;
        }
        else {
            p->next = p2;
            p2 = p2->next;
            p = p->next;
        }
    }
    if(p1) p->next = p1;
    else p->next = p2;
}

int main(int argc, const char * argv[]) {
    List<int> test1, test2;
    for (int i = 0; i < 8; i++) test1.Insert(i, i * 2);
    test2.Insert(0, 1);
    test2.Insert(1, 3);
    test2.Insert(2, 9);
    test2.Insert(3, 13);

    Node<int>* n2 = test2.GetHead();
    test1.Union(n2);
    Node<int>* n1 = test1.GetHead();
    n1 = n1->next;
    while (n1 != NULL) {
        cout << n1->data << endl;
        n1 = n1->next;
    }
    return 0;
}
