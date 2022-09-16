#include<bits/stdc++.h>

using namespace std;

int N, K;
vector<string> store[100001];
map<string, int> itemrank;

bool compare(string &s1, string s2) {
    return itemrank[s1] < itemrank[s2];
}

int main() {
    cin >> N >> K;
    int id;
    string item;
    for (int i = 0; i < K; ++i) {
        cin >> id >> item;
        store[id].push_back(item);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> item;
        itemrank[item] = i + 1;
    }

    vector<int> lst;
    for (int i = 0; i < N; ++i) {
        vector<string> screen;
        for (string itm : store[i]) {
            if (itemrank.find(itm) != itemrank.end()) screen.push_back(itm);
        }
        sort(screen.begin(), screen.end(), compare);
        for (string x : screen) {
            lst.push_back(itemrank[x]);
        }
    }

    int head = 0;
    int amb = 0;
    for (int i = 0; i < lst.size(); ++i) {
        if (head == lst[i])
            amb = 1;
        if (head + 1 == lst[i])
            head++;
    }

    if (head == m) {
        cout << (amb ? "ambiguous" : "unique") << endl;
    } else {
        cout << "impossible" << endl;
    }
    return 0;
}
