//
//  main.cpp
//  String
//
//  Created by 杜家昊 on 2019/2/27.
//  Copyright © 2019 杜家昊. All rights reserved.
//

#include <iostream>
#include <string>
#define MAXLENGTH 20
using namespace std;

int nextval[MAXLENGTH];

int index_KMP(string s, string t, int pos) {
    int i = pos, j = 1;
    while (i <= s.length() - 1 && j <= t.length() - 1) {
        if (j == 0 || s[i] == t[j]) {
            ++i;
            ++j;
        }
        else j = nextval[j];
    }
    if (j > t.length() - 1) return i - int(t.length() - 1);
    else return 0;
}

void get_nextval(string t) {
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < t.length() - 1) {
        if (j == 0 || t[i] == t[j]) {
            ++i;
            ++j;
            if (t[i] != t[j]) nextval[i] = j;
            else nextval[i] = nextval[j];
        }
        else j = nextval[j];
    }
}

int main(int argc, const char * argv[]) {
    string x = "*acabaabaabcacaabc";
    string y = "*abaabcac";
    get_nextval(y);
    int pos = index_KMP(x, y, 1);
    cout << pos << endl;
    for (int i = 1; i < MAXLENGTH; i++) {
        cout << nextval[i] << " ";
    }
    return 0;
}
