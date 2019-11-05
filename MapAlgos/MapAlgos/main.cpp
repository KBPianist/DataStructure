//
//  main.cpp
//  MapAlgos
//
//  Created by 杜家昊 on 2019/9/25.
//  Copyright © 2019 杜家昊. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <queue>
#define INF 0xffff
#include "queue.h"

using namespace std;

typedef struct ArcNode {
    int adjvex;
    int weight = 10000;
    struct ArcNode *next;
}ArcNode;

typedef struct VNode {
    char data;
    ArcNode *first;
}VNode, AdjList[100];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;

bool visited[100];
SqQueue Q;

void CreatGraph(ALGraph &G) {
    ArcNode *e1;
    cin >> G.vexnum >> G.arcnum;
    for(int i = 1; i <= G.vexnum; i++) {
        cin >> G.vertices[i].data;
        G.vertices[i].first = NULL;
    }
    for(int k = 0; k < G.arcnum; k++) {
        int a, b, c;
        cin >> a >> b >> c;
        e1 = (ArcNode*)malloc(sizeof(ArcNode));
        e1->adjvex = b;
        e1->next = G.vertices[a].first;
        e1->weight = c;
        G.vertices[a].first = e1;
        /*无向图*/
//        e2 = (ArcNode*)malloc(sizeof(ArcNode));
//        e2->adjvex = a;
//        e2->next = G.vertices[b].first;
//        e2->weight = c;
//        G.vertices[b].first= e2;
    }
}

int FirstNeighbor(ALGraph &G, int v) {
    ArcNode *node = G.vertices[v].first;
    if (node != NULL) return node->adjvex;
    else return -1;
}

int NextNeighbor(ALGraph &G, int v, int w) {
    ArcNode *tmp =  G.vertices[v].first;
    while (tmp->adjvex != w) {
        tmp = tmp->next;
    }
    if (tmp->next != NULL) return tmp->next->adjvex;
    else return -1;
    
}

void BFS(ALGraph &G, int v) {
    visit(v);
    visited[v] = true;
    
    EnQueue(&Q, v);
    while (!isEmpty(Q)) {
        DeQueue(&Q, &v);
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w]) {
                visit(w);
                visited[w] = true;
                EnQueue(&Q, w);
            }
        }
    }
}

void BFSTraverse(ALGraph &G) {
    for (int i = 1; i <= G.vexnum; ++i) visited[i] = false;
    
    InitQueue(&Q);
    
    for (int i = 1; i <= G.vexnum; ++i) {
        if (!visited[i]) {
            BFS(G, i);
        }
    }
}

void DFS(ALGraph &G, int v) {
    visit(v);
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]) {
            DFS(G, w);
        }
    }
}

void DFSTraverse(ALGraph &G) {
    for (int i = 1; i <= G.vexnum; ++i) visited[i] = false;
    
    for (int i = 1; i <= G.vexnum; ++i) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
}

int lowcost[100];
int mst[100];

int getWeight(ALGraph &G, int m, int n){
    ArcNode *node = G.vertices[m].first;
    while(node){
        if(node->adjvex == n){
            return node->weight;
        }
        node = node->next;
    }

    return INF;
}

void Prim(ALGraph &G, int v) {
    for (int i = 1; i <= G.vexnum; i++) {
        lowcost[i] = getWeight(G, v, i);
        mst[i] = v;
    }
    mst[v] = -1;
    
    int sum_mst = 0;
    for(int i = 1; i <= G.vexnum; i++) {
        int minn = INF;
        int w = -1;
        
        for(int j = 1; j <= G.vexnum; j++) {
            if(mst[j] != -1 && lowcost[j] < minn) {
                w = j;
                minn = lowcost[j];
            }
        }
        if(w != -1) {
            cout << mst[w] << " " << w << " " << lowcost[w] << endl;
            mst[w] = -1;
            sum_mst += lowcost[w];
            for(int j = 1; j <= G.vexnum; j++) {
                int value = getWeight(G, w, j);
                if(mst[j] != -1 && lowcost[j] > value) {
                    lowcost[j] = value;
                    mst[j] = w;
                }
            }
        }
    }
    cout << "sum:" << sum_mst << endl;
}

typedef struct node{
    int id;
    int weight;
    friend bool operator < (node a, node b) {
        return a.weight > b.weight;
    }
}node;

int parent[100]; //每个顶点的父亲节点，可以用于还原最短路径树
node d[100];     //源点到每个顶点估算距离，最后结果为源点到所有顶点的最短路。
priority_queue<node> q;

void Dijkstra(ALGraph &G, int s) {
    for(int i = 1; i <= G.vexnum; i++) { //初始化
        d[i].id = i;
        d[i].weight = INF;    //估算距离置INF
        parent[i] = -1;          //每个顶点都无父亲节点
        visited[i] = false;      //都未找到最短路
    }
    d[s].weight = 0;            //源点到源点最短路权值为0
    q.push(d[s]);               //压入队列中
    while(!q.empty()) {          //算法的核心，队列空说明完成了操作
        node cd = q.top();      //取最小估算距离顶点
        q.pop();
        int u = cd.id;
        if(visited[u]) continue;  //注意这一句的深意，避免很多不必要的操作
        visited[u] = true;
        ArcNode *p = G.vertices[u].first;
        while(p != NULL) {   //找所有与他相邻的顶点，进行松弛操作，更新估算距离，压入队列。
            int v = p->adjvex;
            if(!visited[v] && d[v].weight > d[u].weight + p->weight) {
                d[v].weight = d[u].weight + p->weight;
                parent[v] = u;
                q.push(d[v]);
            }
            p = p->next;
        }
    }
    
}

typedef struct FloydGraph{
    int vexnum, arcnum;
    int edges[4][4];
}FloydGraph;


void Floyd(FloydGraph &G, int path[][100]) {
    int A[G.vexnum][G.vexnum];

    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            A[i][j] = G.edges[i][j];
            path[i][j] = -1;
        }
    }
    
    for (int k = 0; k < G.vexnum; k++) {
        for (int i = 0; i < G.vexnum; i++) {
            for (int j = 0; j < G.vexnum; j++) {
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

void PrintPath(int u, int v, int path[][100]) {
    if (path[u][v] == -1) {
        cout << v << " " << endl;
    }
    else {
        int mid = path[u][v];
        PrintPath(u, mid, path);
        PrintPath(mid, v, path);
    }
}

bool TopologicalSort() {
    return true;
}

void CriticalPath() {
    
}

int main(int argc, const char * argv[]) {
    // ALGraph G;
    FloydGraph FG;
    FG.arcnum = 4;
    FG.vexnum = 4;
    for (int i = 0; i < FG.vexnum; i++) {
        for (int j = 0; j < FG.vexnum; j++) {
            cin >> FG.edges[i][j];
        }
    }
    /*
    CreatGraph(G);
    DFSTraverse(G);
    Prim(G, 1);
    int s, e;
    cin >> s >> e;
    Dijkstra(G, s);
    if(d[e].weight != INF)
        printf("最短路径权值为：%d\n", d[e].weight);
    else
        printf("不存在从顶点%d到顶点%d的最短路径。\n", s, e);
     */
    return 0;
}
