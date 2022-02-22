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
    NodeRef root = make_shared<Node>("R1 ���߽�");
    {
        NodeRef node = make_shared<Node>("��������");
        root->children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("����");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("����");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("���丮");
            node->children.push_back(leaf);
        }
    }
    {
        NodeRef node = make_shared<Node>("���α׷�����");
        root->children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("����");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("Ŭ��");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("����");
            node->children.push_back(leaf);
        }
    }
    {
        NodeRef node = make_shared<Node>("��Ʈ��");
        root->children.push_back(node);
        {
            NodeRef leaf = make_shared<Node>("���");
            node->children.push_back(leaf);
        }
        {
            NodeRef leaf = make_shared<Node>("ĳ����");
            node->children.push_back(leaf);
            {
                NodeRef leaf2 = make_shared<Node>("�𵨷�");
                leaf->children.push_back(leaf2);
            }
            {
                NodeRef leaf2 = make_shared<Node>("�ִϸ�����");
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

// ����(depth) : ��Ʈ���� � ��忡 �����ϱ� ���� ���ľ� �ϴ� ������ �� (�� ��?)
// ����(height) : ���� ����� �ִ� ����� ���� (max(depth))
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

#pragma region Priority Queue (�� ����)
template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:

    void push(const T& data)
    {
        // �켱 �� �������� �����ش�.
        _heap.push_back(data);

        // ������� ����
        int now = static_cast<int>(_heap.size()) - 1;
        // ��Ʈ ������ �õ�
        while (now > 0)
        {
            // �θ� ����� �����Ϳ� ���ؼ� �� ������ �й�
            int parent = (now - 1) / 2;
            /*if (_heap[now] < _heap[parent])
                break;*/
            if (_predicate(_heap[now], _heap[parent]))
                break;

            // ������ ��ü
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

            // ������ ������ ���
            if (left_child >= _heap.size())
                break;

            int next = now;

            // ���ʰ� ��
            /*if (_heap[next] < _heap[left_child])
                next = left_child;*/
            if (_predicate(_heap[next], _heap[left_child]))
                next = left_child;

            // �� �� ���ڸ� �����ʰ� ��
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