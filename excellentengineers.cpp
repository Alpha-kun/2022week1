#include <bits/stdc++.h>

using namespace std;
typedef tuple<int, int, int> p3;

struct Node {
    Node *lc, *rc;
    int l, r, mini;

    Node(int lb, int rb) {
        l = lb, r = rb;
        mini = INT32_MAX;
        if (lb == rb) {
            lc = rc = nullptr;
        } else {
            int mid = (lb + rb) / 2;
            lc = new Node(lb, mid);
            rc = new Node(mid + 1, rb);
        }
    }
};

void update(Node *n, int x, int val) {
    if (n->l == n->r)
        n->mini = val;
    else {
        int mid = (n->l + n->r) / 2;
        if (x <= mid) update(n->lc, x, val);
        else update(n->rc, x, val);
        n->mini = min(n->lc->mini, n->rc->mini);
    }
}

int query(Node *n, int l, int r) {
    if (n->l == l && n->r == r)
        return n->mini;
    else {
        int mid = (n->l + n->r) / 2;
        if (r <= mid) return query(n->lc, l, r);
        else if (mid + 1 <= l) return query(n->rc, l, r);
        else return min(query(n->lc, l, mid), query(n->rc, mid + 1, r));
    }
}

Node *rt;

void testcase() {
    int n, x, y, z;
    cin >> n;
    vector<p3> v;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y >> z;
        v.push_back(make_tuple(x, y, z));
    }
    sort(v.begin(), v.end());
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (query(rt, 0, get<1>(v[i])) > get<2>(v[i])) cnt++;
        update(rt, get<1>(v[i]), get<2>(v[i]));
    }
    cout << cnt << endl;
    for (int i = 0; i <= 100001; ++i) {
        update(rt, i, INT32_MAX);
    }
}

int main() {
    rt = new Node(0, 100001);
    int t;
    cin >> t;
    while (t--) {
        testcase();
    }
    return 0;
}
