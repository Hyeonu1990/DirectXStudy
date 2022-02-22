#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

#pragma region Tree Basic
using NodeRef = shared_ptr<struct Node>;
struct Node
{
    Node() { }
    Node(const string& data) : data(data) { }
    string data;
    vector<NodeRef> children;
};

NodeRef CreateTree()
{
    NodeRef root = make_shared<Node>("R1 개발실");
    {
        NodeRef node = make_shared<Node>("디자인팀");
        root->children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("전투");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("경제");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("스토리");
            node->children.push_back(leaf);
        }
    }
    {
        NodeRef node = make_shared<Node>("프로그래밍팀");
        root->children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("서버");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("클라");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("엔진");
            node->children.push_back(leaf);
        }
    }
    {
        NodeRef node = make_shared<Node>("아트팀");
        root->children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("배경");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("캐릭터");
            node->children.push_back(leaf);
            {
                NodeRef leaf2 = make_shared<Node>("모델러");
                leaf->children.push_back(leaf2);
            }
            {
                NodeRef leaf2 = make_shared<Node>("애니메이터");
                leaf->children.push_back(leaf2);
            }
        }
    }

    return root;
}

void PrintTree(NodeRef root, int depth)
{
    for (int i = 0; i < depth; i++)
        cout << "-";
    cout << root->data << endl;

    for (NodeRef& child : root->children)
    {
        PrintTree(child, depth + 1);
    }
}

// 깊이(depth) : 루트에서 어떤 노드에 도달하기 위해 거쳐야 하는 간선의 수 (몇 층?)
// 높이(height) : 가장 깊숙히 있는 노드의 깊이 (max(depth))
int GetHeight(NodeRef root)
{
    int height = 1;

    for (NodeRef& child : root->children)
    {
        height = max(height, GetHeight(child) + 1);
    }

    return height;
}
#pragma endregion

#pragma region Priority Queue (힙 구조)
template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:

    void push(const T& data)
    {
        // 우선 힙 구조부터 맞춰준다.
        _heap.push_back(data);

        // 도장깨기 시작
        int now = static_cast<int>(_heap.size()) - 1;
        // 루트 노드까지 시도
        while (now > 0)
        {
            // 부모 노드의 데이터와 비교해서 더 작으면 패배
            int parent = (now - 1) / 2;
            /*if (_heap[now] < _heap[parent])
                break;*/
            if (_predicate(_heap[now], _heap[parent]))
                break;

            // 데이터 교체
            ::swap(_heap[now], _heap[parent]);
            now = parent;
        }
    }

    void pop()
    {
        _heap[0] = _heap.back();
        _heap.pop_back();

        int now = 0;
        while (true)
        {
            int left_child = now * 2 + 1;
            int right_child = left_child + 1;

            // 리프에 도달한 경우
            if (left_child >= _heap.size())
                break;

            int next = now;

            // 왼쪽과 비교
            /*if (_heap[next] < _heap[left_child])
                next = left_child;*/
            if (_predicate(_heap[next], _heap[left_child]))
                next = left_child;

            // 둘 중 승자를 오른쪽과 비교
            /*if (right_child < _heap.size() && _heap[next] < _heap[right_child])
                next = right_child;*/
            if (right_child < _heap.size() && _predicate(_heap[next], _heap[right_child]))
                next = right_child;

            if (next == now)
                break;

            ::swap(_heap[now], _heap[next]);
            now = next;
        }
    }

    T& top()
    {
        return _heap[0];
    }

    bool empty()
    {
        return _heap.empty();
    }

private:
    Container _heap = { }; // vector<T> _heap = {};
    Predicate _predicate = {};
};
#pragma endregion

int Test()
{
    /*NodeRef root = CreateTree();
    PrintTree(root, 0);
    cout << "Tree Height ; " << GetHeight(root) << endl;*/

    PriorityQueue<int, vector<int>, greater<int>> pq;//priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(100);
    pq.push(300);
    pq.push(200);
    pq.push(500);
    pq.push(400);
    while (pq.empty() == false)
    {
        int value = pq.top();
        pq.pop();

        cout << value << endl;
    }

    return 0;
}