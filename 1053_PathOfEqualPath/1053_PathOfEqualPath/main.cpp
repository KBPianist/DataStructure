//
//  main.cpp
//  1053_PathOfEqualPath
//
//  Created by 杜家昊 on 2019/10/28.
//  Copyright © 2019 杜家昊. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#define MAX 1000

using namespace std;

typedef struct sum{
    int s;
    vector<int> path;
    bool leaf;
}sum;

int id2num(string id) {
    if (id[0] == '0') return id[1] - '0';
    else {
        int sum = (id[0] - '0') * 10 + id[1] - '0';
        return sum;
    }
}

int main() {
    int value[MAX];
    sum ss[MAX];
    
    int N, M, S;
    cin >> N >> M >> S;
    for (int i = 0; i < N; i++) {
        cin >> value[i];
        ss[i].s = value[0];
        ss[i].path.push_back(value[0]);
        ss[i].leaf = true;
    }
    
    for (int i = 0; i < M; i++) {
        string id;
        int childnum, fid;
        cin >> id >> childnum;
        fid = id2num(id);
        for (int j = 0; j < childnum; j++) {
            string childid;
            int cid;
            cin >> childid;
            cid = id2num(childid);
            ss[fid].leaf = false;
            ss[cid].s = ss[fid].s + value[cid];
            ss[cid].path.assign(ss[fid].path.begin(), ss[fid].path.end());
            ss[cid].path.push_back(value[cid]);
        }
    }
    for (int i = 0; i < N; i++) {
        if (ss[i].s == S && ss[i].leaf == true) {
            for (int j = 0; j < ss[i].path.size() - 1; j++) {
                cout << ss[i].path[j] << " ";
            }
            cout << ss[i].path[ss[i].path.size() - 1] << endl;
        }
        //cout << ss[i].s << endl;
    }
}
