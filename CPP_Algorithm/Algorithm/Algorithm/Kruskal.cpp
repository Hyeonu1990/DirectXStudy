#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

// 최소 스패닝 트리 (Minimum Spanning Tree, MST)

class DisjointSet
{
public:
    DisjointSet(int n) : _parent(n), _rank(n, 1)
    {
        for (int i = 0; i < n; i++)
        {
            _parent[i] = i;
        }
    }

    // 유저의 대장 찾기
    int Find(int u)
    {
        if (u == _parent[u])
            return u;

        return _parent[u] = Find(_parent[u]);
    }

    void Merge(int u, int v)
    {
        u = Find(u);
        v = Find(v);

        if (u == v)
            return;

        if (_rank[u] > _rank[v])
            swap(u, v);

        _parent[u] = v;

        // [1]     [3]
        // [2]  [4][5][1]
        // [6]     [0][2]
        //            [6]
        if (_rank[u] == _rank[v])
            _rank[v]++;
    }

private:
    vector<int> _parent;
    vector<int> _rank;
};

struct Vertex_MST
{
    // int data;
};

vector<Vertex_MST> vertices;
vector<vector<int>> adjacent_MST; // 인접 행렬

void CreateGraph()
{
    vertices.resize(6);
    adjacent_MST = vector<vector<int>>(6, vector<int>(6, -1));

    adjacent_MST[0][1] = adjacent_MST[1][0] = 15;
    adjacent_MST[0][3] = adjacent_MST[3][0] = 35;
    adjacent_MST[1][2] = adjacent_MST[2][1] = 5;
    adjacent_MST[1][3] = adjacent_MST[3][1] = 10;
    adjacent_MST[3][4] = adjacent_MST[4][3] = 5;
    adjacent_MST[3][5] = adjacent_MST[5][3] = 10;
    adjacent_MST[5][4] = adjacent_MST[4][5] = 5;

}

struct CostEdge
{
    int cost;
    int u;
    int v;

    bool operator<(CostEdge& other)
    {
        return cost < other.cost;
    }
};
int Kruskal(vector<CostEdge>& selected)
{
    int ret = 0;

    selected.clear();

    vector<CostEdge> edges;

    for (int u = 0; u < adjacent_MST.size(); u++)
    {
        for (int v = 0; v < adjacent_MST[u].size(); v++)
        {
            if (u > v) // 역방향은 일단 거르기
                continue;

            int cost = adjacent_MST[u][v];
            if (cost == -1)
                continue;

            edges.push_back(CostEdge{ cost, u, v });
        }
    }

    std::sort(edges.begin(), edges.end());

    DisjointSet sets(vertices.size());

    for (CostEdge& edge : edges)
    {
        // 같은 그룹이면 스킵 (안그러면 사이클 발생)
        if (sets.Find(edge.u) == sets.Find(edge.v))
            continue;

        // 두 그룹을 합친다
        sets.Merge(edge.u, edge.v);
        selected.push_back(edge);
        ret += edge.cost;

        // NOTE : 그룹이 하나로 될때까지 DisjointSet 내용

        // [0] [1] [2] [3] [4] [5]
        //          V
        // [0]     [2] [3] [4] [5]
        //         [1]
        //          V
        // [0]     [2] [3]     [5]
        //         [1] [4]
        //          V
        // [0]     [2] [3]
        //         [1] [4] [5]
        //          V
        // [0]         [3]
        //         [2] [4] [5]
        //         [1]
        //          V
        //             [3]
        //     [0] [2] [4] [5]
        //         [1]
    }

    return ret;
}

int KruskalTest()
{
    CreateGraph();

    vector<CostEdge> selected;
    int cost = Kruskal(selected);

    return 0;
}