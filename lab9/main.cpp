#include <iostream>
#include <vector>
#include <algorithm>

class TGraph {
public:
    explicit TGraph (int);
    std::vector<std::pair<int, int>> Kuhn (int);
    bool Try_Kuhn (int);
    void addEdge (int, int);
    void sort (int);
    void make_part(int);

private:
    std::vector<std::vector<int>> g;
    std::vector<int> mt;
    std::vector<bool> used;
    std::vector<int> part;
};

TGraph::TGraph(int n) {
    g = std::vector<std::vector<int>>(n);
    mt = std::vector<int>(n, -1);
}

void TGraph::addEdge(int u, int v) {
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
}

void TGraph::sort(int n) {
    for (int i = 0; i < n; i++) {
        std::sort(g[i].begin(), g[i].end());
    }
}

std::vector<std::pair<int, int>> TGraph::Kuhn(int n) {
    for (int i = 0; i < n; i++) {
        used = std::vector<bool>(n);
        used.assign(n, false);
        if (part[i] == 0) {
            Try_Kuhn(i);
        }
    }
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < n; i++) {
        if (mt[i] != - 1) {
            if (mt[i] < i) {
                result.push_back(std::make_pair(mt[i] + 1, i + 1));
            } else {
                result.push_back(std::make_pair(i + 1, mt[i] + 1));
            }
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}


bool TGraph::Try_Kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];
        if (mt[u] == -1 or Try_Kuhn(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

void TGraph::make_part(int n) {
    std::vector<int> p(n, -1);
    std::vector<int> q(n);

    for (int st = 0; st < n; ++st) {
        if (p[st] == -1) {
            int h = 0, t = 0;
            q[t++] = st;
            p[st] = 0;
            while (h < t) {
                int v = q[h++];
                for (size_t i = 0; i < g[v].size(); ++i) {
                    int to = g[v][i];
                    if (p[to] == -1)
                        p[to] = !p[v], q[t++] = to;

                }
            }
        }
    }
    part = p;
}


int main() {
    int n, m, u, v;
    std::cin >> n >> m;
    TGraph graph(n);
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }
    graph.sort(n);
    graph.make_part(n);

    std::vector<std::pair<int, int>> result = graph.Kuhn(n);
    std::cout << result.size() << std::endl;
    for (auto & i : result) {
        std::cout << i.first << " " << i.second << std::endl;
    }
    return 0;
}
