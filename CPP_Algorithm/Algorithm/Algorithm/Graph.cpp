#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

#pragma region Graph Basic
void CreateGraph_1()
{
    struct Node
    {
        Node* prev;
        Node* next;
        int data;
    };

    struct Vertex // 정점
    {
        vector<Vertex*> edges; // 간선 목록
        // int data;
    };

    vector<Vertex> v;
    v.resize(6);

    v[0].edges.push_back(&v[1]);
    v[0].edges.push_back(&v[3]);
    v[1].edges.push_back(&v[0]);
    v[1].edges.push_back(&v[2]);
    v[1].edges.push_back(&v[3]);
    v[3].edges.push_back(&v[4]);
    v[5].edges.push_back(&v[4]);

    // Q) 0번 -> 3번 정점이 연결되어 있나요?
    bool connected = false;
    for (Vertex* edge : v[0].edges)
    {
        if (edge == &v[3])
        {
            connected = true;
            break;
        }
    }
    cout << "Connected 0 -> 3 : " << connected << endl;
}

void CreateGraph_2()
{
    struct Vertex // 정점
    {
        // int data;
    };

    vector<Vertex> v;
    v.resize(6);

    // 연결된 간선 목록을 따로 관리

    vector<vector<int>> adjacent(6);
    adjacent[0] = { 1, 3 };
    adjacent[1] = { 0, 2, 3 };
    adjacent[3] = { 4 };
    adjacent[5] = { 4 };

    // Q) 0번 -> 3번 정점이 연결되어 있나요?
    // A1) Loop
    bool connected = false;
    for (int vertex : adjacent[0])
    {
        if (vertex == 3)
        {
            connected = true;
            break;
        }
    }
    cout << "Connected 0 -> 3 : " << connected << endl;
    // A2) STL
    vector<int>& adj = adjacent[0];
    bool connected2 = std::find(adj.begin(), adj.end(), 3) != adj.end();
    cout << "Connected 0 -> 3 : " << connected2 << endl;

    // 정점이 100개
    // - 지하철 노선도 -> 서로 드문 드문 연결 (보통 양옆, 환승역이라면 좀 더 ++)
    // - 페이스북 친구 -> 서로 빽빽하게 연결
}

void CreateGraph_3()
{
    struct Vertex // 정점
    {
        // int data;
    };

    vector<Vertex> v;
    v.resize(6);

    // 연결된 간선 목록을 따로 관리
    // [X][0][X][0][X][X]
    // [0][X][0][0][X][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][O][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][O][X]

    // adjacent[from][to]
    // 행렬을 이용한 그래프 표현 (2차원 배열)
    // 메모리 소모가 심하지만, 빠른 접근이 가능하다
    // (간선이 많은 경우 이점인 방법)
    vector<vector<bool>> adjacent(6, vector<bool>(6, false));
    adjacent[0][1] = true;
    adjacent[0][3] = true;
    adjacent[1][0] = true;
    adjacent[1][2] = true;
    adjacent[1][3] = true;
    adjacent[3][4] = true;
    adjacent[5][4] = true;

    // Q) 0번 -> 3번 정점이 연결되어 있나요?
    // A1) Loop
    bool connected = adjacent[0][3];
    cout << "Connected 0 -> 3 : " << connected << endl;

    ///////////////////////////////////////////

    // 가중치 추가
    vector<vector<int>> adjacent2 =
    {
        vector<int> { -1, 15, -1, 35, -1, -1},
        vector<int> { 15, -1, +5, 10, -1, -1},
        vector<int> { -1, -1, -1, -1, -1, -1},
        vector<int> { -1, -1, -1, -1, +5, -1},
        vector<int> { -1, -1, -1, -1, -1, -1},
        vector<int> { -1, -1, -1, -1, +5, -1},
    };

    // Q) 0번 -> 3번 정점이 연결되어 있나요?
    // A1) Loop
    bool connected2 = adjacent2[0][3] > 0;
    cout << "Connected 0 -> 3 : " << connected2 << endl;
}
#pragma endregion
// DFS (Depth First Search) 깊이 우선 탐색 - 간선이 연결되어있으면 쭉 진행하며 탐색
// BFS (Breadth First Search) 너비 우선 탐색 - 정점을 기준으로 한칸씩 탐색
struct Vertex
{
    // int data;
};
vector<Vertex> vertices;
vector<vector<int>> adjacent;
void CreateGraph(bool IsArrayType = false)
{
    vertices.resize(6);
    adjacent = vector<vector<int>>(6);

    if (IsArrayType == false)
    {
        //인접리스트
        adjacent[0].push_back(1);
        adjacent[0].push_back(3);
        adjacent[1].push_back(0);
        adjacent[1].push_back(2);
        adjacent[1].push_back(3);
        adjacent[3].push_back(4);
        adjacent[5].push_back(4);
    }
    else
    {
        // 인접 행렬 리스트
        adjacent = vector<vector<int>>
        {
            { 0, 1, 0, 1, 0, 0},
            { 1, 0, 1, 1, 0, 0},
            { 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 1, 0},
            { 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 1, 0},
        };
    }
}
#pragma region DFS
vector<bool> visited;
void Dfs(int here, bool IsArrayType = false)
{
    visited[here] = true;
    cout << "Visited : " << here << endl;

    if (IsArrayType == false)
    {
        // 인접 리스트 version
        // 모든 인접 정점을 순회한다
        for (int i = 0; i < adjacent[here].size(); i++)
        {
            int there = adjacent[here][i];
            if (visited[there] == false)
                Dfs(there);
        }
    }
    else
    {
        // 인접 행렬 version
        for (int there = 0; there < 6; there++)
        {
            if (adjacent[here][there] == 0)
                continue;

            if (visited[there] == false)
                Dfs(there);
        }
    }
}
void DfsAll(bool IsArrayType = false)
{
    visited = vector<bool>(6, false);

    for (int i = 0; i < 6; i++)
        if (visited[i] == false)
            Dfs(i, IsArrayType);
}
#pragma endregion
#pragma region BFS
vector<bool> discovered;
void Bfs(int here, bool IsArrayType = false)
{
    // 누구에 의해 발견 되었는지 ?
    vector<int> parent(6, -1);
    // 시작점에서 얼만큼 떨어져 있는지?
    vector<int> distance(6, -1);

    queue<int> q;
    q.push(here);
    discovered[here] = true;

    parent[here] = here;
    distance[here] = 0;

    while (q.empty() == false)
    {
        here = q.front();
        q.pop();

        cout << "Visited : " << here << ", Parent : " << parent[here] << ", Distance : " << distance[here] << endl;

        if (IsArrayType == false)
        {
            for (int there : adjacent[here])
            {
                if (discovered[there])
                    continue;

                q.push(there);
                discovered[there] = true;

                parent[there] = here;
                distance[there] = distance[here] + 1;
            }
        }
        else
        {
            for (int there = 0; there < 6; there++)
            {
                if (adjacent[here][there] == 0)
                    continue;

                if (discovered[there])
                    continue;

                q.push(there);
                discovered[there] = true;

                parent[there] = here;
                distance[there] = distance[here] + 1;
            }
        }
    }
}

void BfsAll(bool IsArrayType = false)
{
    for (int i = 0; i < 6; i++)
    {
        if (discovered[i] == false)
            Bfs(i, IsArrayType);
    }
}
#pragma endregion
#pragma region Dijiksta (다익스트라) 알고리즘
void CreateGraph2()
{
    vertices.resize(6);
    adjacent.clear();
    adjacent = vector<vector<int>>(6, vector<int>(6, -1));

    adjacent[0][1] = 15;
    adjacent[0][3] = 35;
    adjacent[1][0] = 15;
    adjacent[1][2] = 5;
    adjacent[1][3] = 10;
    adjacent[3][4] = 5;
    adjacent[5][4] = 5;
}

void Dijikstra(int here)
{
    struct VertexCost
    {
        int vertex;
        int cost;
    };

    list<VertexCost> discovered; // 발견 목록(탐색할 Vertex 리스트)
    vector<int> best(vertices.size(), INT32_MAX); // 각 정점별로 지금까지 발견한 최소 거리
    vector<int> parent(6, -1);

    discovered.push_back(VertexCost{ here, 0 });
    best[here] = 0;
    parent[here] = here;

    while (discovered.empty() == false)
    {
        // 제일 좋은 후보를 찾는다
        list<VertexCost>::iterator bestIt;
        int bestCost = INT32_MAX;

        for (auto it = discovered.begin(); it != discovered.end(); it++)
        {
            const int vertex = it->vertex;
            const int cost = it->cost;

            if (cost < bestCost)
            {
                bestCost = cost;
                bestIt = it;
            }
        }

        int cost = bestIt->cost;
        here = bestIt->vertex;
        discovered.erase(bestIt);

        // 더 짧은 경로가 있었다면 방문 스킵
        if (best[here] < cost)
            continue;

        // 방문
        for (int there = 0; there < vertices.size(); there++)
        {
            // 연결되지 않아쓰면 스킵
            if (adjacent[here][there] == -1)
                continue;

            // 더 좋은 경로를 과거에 찾았으면 스킵
            int nextCost = best[here] + adjacent[here][there];
            if (nextCost >= best[there])
                continue;

            best[there] = nextCost;
            parent[there] = here;

            //(3, 35) (3, 25) 이렇게 들어가게 되는 부분이 있으니 처리단계에서 조심
            discovered.push_back(VertexCost{ there, nextCost });
            cout << there << ", " << nextCost << endl;
        }
    }

    for (int i = 0; i < best.size(); i++)
        if (best[i] != INT32_MAX)
            cout << i << ", " << best[i] << ", parent : " << parent[i] << endl;
}
#pragma endregion

int GraphTest()
{
    //CreateGraph_1();
    //CreateGraph_2();
    //CreateGraph_3();
    bool _isArrayType = true;
    CreateGraph(_isArrayType);

    //DFS
    //visited = vector<bool>(6, false);
    //Dfs(0, _isArrayType);
    //DfsAll(_isArrayType);

    //BFS
    //discovered = vector<bool>(6, false);
    //Bfs(0, _isArrayType);
    //BfsAll(_isArrayType);

    //Dijikstra
    CreateGraph2();
    Dijikstra(0);


    return 0;
}