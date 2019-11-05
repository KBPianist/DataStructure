#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#define maxlen 10000

using namespace std;

int TollPerMin[25];
typedef struct{
    string name;
    int month;
    int day;
    int hour;
    int minute;
    int time;
    bool status;
}record;

vector<record> records(maxlen);
map<string, vector<record> > rmap;

int cmp(record a, record b) {
    return a.name != b.name ? a.name < b.name : a.time < b.time;
}

double caculate(record x, record y) {
    int m = x.minute, d = x.day, h = x.hour;
    double v = 0;
    while (m < y.minute || d < y.day || h < y.hour) {
        m++;
        v += TollPerMin[h];
        if (m == 60) {
            m = 0;
            h++;
        }
        if (h == 24) {
            d++;
            h = 0;
        }
    }
    return v / 100.0;
}

int main() {
    for (int i = 1; i < 25; i++) cin >> TollPerMin[i];
    int recordsNum;
    cin >> recordsNum;
    for (int i = 0; i < recordsNum; i++) {
        cin >> records[i].name;
        scanf("%d:%d:%d:%d", &records[i].month, &records[i].day, &records[i].hour, &records[i].minute);
        string s;
        cin >> s;
        records[i].status = (s == "on-line") ? true : false;

        records[i].time = (records[i].day * 24 + records[i].hour) * 60 + records[i].minute;
    }

    sort(records.begin(), records.end(), cmp);
    
    for (int i = 1; i < recordsNum; i++){
        if(records[i].name == records[i - 1].name && records[i - 1].status == true) {
            rmap[records[i].name].push_back(records[i - 1]);
            rmap[records[i].name].push_back(records[i]);
        }
    }
    
    map<string, vector<record> >::iterator it;
    for (it = rmap.begin(); it != rmap.end(); it++) {
        vector<record> temp = it->second;
        cout << temp[0].name;
        printf(" %2d\n", temp[0].month);
        double total = 0;
        for (int i = 0; i < temp.size() - 1; i += 2) {
            record a = temp[i];
            record b = temp[i + 1];
            int t = b.time - a.time;
            double toll = caculate(a, b);
            total += toll;
            printf("%2d:%2d:%2d ", a.day, a.hour, a.minute);
            printf("%2d:%2d:%2d ", b.day, b.hour, b.minute);
            printf("%d $%.2f\n", t, toll);
        }
        printf("Total amount: $%.2f\n", total);
    }
}