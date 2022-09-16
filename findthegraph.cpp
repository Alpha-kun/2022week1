#include <bits/stdc++.h>

using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> d(n + 1);
    for (int i = 1; i <= n; ++i) {
        cout << "? 1 " << i << endl;
        cin >> d[i];
    }
    bool A[51][51] = {false};
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int s;
            cout << "? 2 " << i << ' ' << j << endl;
            cin >> s;
            if (s == d[i] + d[j] - 2) A[i][j] = A[j][i] = true;
        }
    }
    cout << '!' << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << (A[i][j] ? "1 " : "0 ");
        }
        cout << endl;
    }
    return 0;
}
