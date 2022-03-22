#pragma once

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
