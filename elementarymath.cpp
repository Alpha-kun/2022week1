#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define MAXN 15000
#define INF 1000000009

struct Edge {
    int v, w, cap, f;

    Edge(int a, int b, int c) : v(a), w(b), cap(c), f(0) {}

    int other(int s) { return s == v ? w : v; }

    int getRez(int s) { return s == v ? cap - f : f; }

    void addFlow(int s, int d) {
        if (s == v) f += d;
        else f -= d;
    }
};

bool marked[MAXN];
vector<Edge *> graph[MAXN];

int dfs(int s, int t, int f) {
    if (s == t) return f;
    marked[s] = true;
    for (Edge *edge: graph[s]) {
        int to = edge->other(s);
        if (!marked[to] && edge->getRez(s) > 0) {
            int d = dfs(to, t, min(f, edge->getRez(s)));
            if (d > 0) {
                edge->addFlow(s, d);
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int totalFlow = 0;
    while (true) {
        memset(marked, false, sizeof(marked));
        int inc = dfs(s, t, INF);
        if (inc == 0) break;
        totalFlow += inc;
    }
    return totalFlow;
}

int main() {
    int n;
    cin >> n;
    ll a[n], b[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    map<ll, int> id;
    vector<ll> res;
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        ll sum = a[i] + b[i];
        if (id.find(sum) == id.end()) {
            id[sum] = idx++;
            res.push_back(sum);
        }
        Edge *e = new Edge(i, 2500 + id[sum], 1);
        graph[i].push_back(e);
        graph[2500 + id[sum]].push_back(e);

        ll diff = a[i] - b[i];
        if (id.find(diff) == id.end()) {
            id[diff] = idx++;
            res.push_back(diff);
        }
        e = new Edge(i, 2500 + id[diff], 1);
        graph[i].push_back(e);
        graph[2500 + id[diff]].push_back(e);

        ll prod = a[i] * b[i];
        if (id.find(prod) == id.end()) {
            id[prod] = idx++;
            res.push_back(prod);
        }
        e = new Edge(i, 2500 + id[prod], 1);
        graph[i].push_back(e);
        graph[2500 + id[prod]].push_back(e);
    }
    for (int i = 0; i < n; ++i) {
        Edge *e = new Edge(14000, i, 1);
        graph[14000].push_back(e);
        graph[i].push_back(e);
    }
    for (int i = 0; i < idx; ++i) {
        Edge *e = new Edge(2500 + i, 14001, 1);
        graph[2500 + i].push_back(e);
        graph[14001].push_back(e);
    }
    int flow = maxFlow(14000, 14001);
    if (flow < n) {
        cout << "impossible" << endl;
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        for (Edge *e: graph[i]) {
            if (e->f > 0) {
                int oid = e->w - 2500;
                if (res[oid] == a[i] + b[i]) {
                    printf("%d + %d = %lld\n", a[i], b[i], res[oid]);
                } else if (res[oid] == a[i] - b[i]) {
                    printf("%d - %d = %lld\n", a[i], b[i], res[oid]);
                } else {
                    printf("%d * %d = %lld\n", a[i], b[i], res[oid]);
                }
                break;
            }
        }
    }

    return 0;
}
