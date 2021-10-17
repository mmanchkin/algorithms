#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <map>
#include <unordered_map>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vl = vector<long long>;
using mm = unordered_map<int, unordered_map<int, int>>;
const long long INF = 1000000000000;


void min_tree(vl& dist, int s, vvi& graph, mm& ed, vb& used, vi& from, int n, int& ans) {
    dist[s] = 0;
    from[s] = 0;
    priority_queue<tuple<long long, int>> q;
    for (int i = 1; i < n + 1; i++) {
        q.push({-dist[i], i});
    }
    while (!q.empty()) {
        tuple<long long, int> v_p = q.top();
        q.pop();
        int v = get<1>(v_p); long long d = -get<0>(v_p);
        if (used[v]) {
            continue;
        }
        if (d == INF) {
            break;
        }
        used[v] = true;
        ans += dist[v];
        for (auto& u : graph[v]) {
            if (ed[v][u] < dist[u]) {
                dist[u] = ed[v][u];
                q.push({-dist[u], u});
                from[u] = v;
            }
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    vvi graph(n + 1);
    mm ed;
    for (int i = 0; i < m; i++) {
        int u, v, l;
        cin >> v >> u >> l;
        graph[v].push_back(u); graph[u].push_back(v);
        ed[v][u] = l; ed[u][v] = l;
    }
    vl dist(n + 1, INF);
    vb used(n + 1, false);
    vi from(n + 1, -1);
    int ans = 0;
    min_tree(dist, 1, graph, ed, used, from, n, ans);
    cout << ans << endl;
}
