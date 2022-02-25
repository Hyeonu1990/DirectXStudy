#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
using namespace std;

#pragma region Console
enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE
};

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}
void ShowConsoleCursor(bool flag)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
}
#pragma endregion

BinarySearchTree::BinarySearchTree()
{
	_nil = new Node(); // Black
	_root = _nil;
}

BinarySearchTree::~BinarySearchTree()
{
	delete _nil;
}

void BinarySearchTree::Print()
{
	::system("cls");
	ShowConsoleCursor(false);
	Print(_root, 30, 0);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == _nil)
		return;

	SetCursorPosition(x, y);

	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
	else
		SetCursorColor(ConsoleColor::RED);

	cout << node->key;
	Print(node->left, x - (10 / (y + 1)), y + 1);
	Print(node->right, x + (10 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
}

void BinarySearchTree::Print_Inorder(Node* node)
{
	// ���� ��ȸ (preoder traverse)
	// ���� ��ȸ (inoder traverse)
	// ���� ��ȸ (postoder traverse)

	//   [��]
	// [��][��]

	if (node == _nil)
		return;

	// ���� : [��]�� �տ� �´�
	// ���� : [��]�� �߰��� �´�
	// ���� : [��]�� �������� �´�
	Print_Inorder(node->left);
	cout << node->key << endl; // [��]
	Print_Inorder(node->right);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == _nil || key == node->key)
		return node;
	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);
}

Node* BinarySearchTree::Min(Node* node)
{
	if (node->left == _nil)
		return node;
	else
		return Min(node->left);
}

Node* BinarySearchTree::Max(Node* node)
{
	if (node->right == _nil)
		return node;
	else
		return Max(node->right);
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node->right != _nil)
		return Min(node->right);

	Node* parent = node->parent;

	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	/*if (_root == nullptr)
	{
		_root = newNode;
		return;
	}*/

	Node* node = _root;
	Node* parent = _nil;

	while (node != _nil)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;

	if (parent == _nil)
		_root = newNode;
	else if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

	// �˻�
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red;

	InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{
	// 1) p = red, uncle = red
	// -> p = black, uncle = black, pp = red�� �ٲ�
	// 2) p = red, uncle = black (triangle)
	// -> ȸ���� ���ؼ� case 3) ���� �ٲ�
	// 3) p = red, uncle = black (list)
	// -> ���� ���� + ȸ��

	while (node->parent->color == Color::Red)
	{
		if (node->parent == node->parent->parent->left)
		{
			//          [pp(B)]
			//     [p(R)]     [u(?)]
			//        [n(R)]
			Node* uncle = node->parent->parent->right;
			if (uncle->color == Color::Red)
			{
				//          [pp(B)]
				//     [p(R)]     [u(R)]
				//        [n(R)]
				//            l
				//            V
				//          [pp(R)]
				//     [p(B)]     [u(B)]
				//        [n(R)]
				node->parent->color = Color::Black; //p
				uncle->color = Color::Black; // u
				node->parent->parent->color = Color::Red; // pp
				node = node->parent->parent; // ���� Ȯ���� ���
			}
			else
			{
				//          [pp(B)]
				//     [p(R)]     [u(B)]    2) Triangle Ÿ��
				//        [n(R)]
				//            l
				//            V
				//          [pp(B)]
				//     [n(R)]     [u(B)]    3) list Ÿ��
				//  [p(R)]
				if (node == node->parent->right) // 2) Triangle Ÿ��
				{
					// 2) Triangle Ÿ�� -> 3) List Ÿ�� ����
					node = node->parent;
					LeftRotate(node);
				}

				//          [pp(B)]
				//     [p(R)]     [u(B)]    3) list Ÿ��
				//  [n(R)]
				//            l
				//            V
				//          [p(B)]
				//     [n(R)]     [pp(R)]    3) list Ÿ��
				//                    [u(R)]
				// 3) List Ÿ��
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}
		}
		else
		{
			//          [pp(B)]
			//     [u(?)]     [p(R)]
			//                  [n(R)]

			Node* uncle = node->parent->parent->left;
			if (uncle->color == Color::Red)
			{
				//          [pp(B)]
				//     [u(R)]     [p(R)]
				//                   [n(R)]
				//            l
				//            V
				//          [pp(R)]
				//     [u(B)]     [p(B)]
				//                   [n(R)]
				node->parent->color = Color::Black; //p
				uncle->color = Color::Black; // u
				node->parent->parent->color = Color::Red; // pp
				node = node->parent->parent; // ���� Ȯ���� ���
			}
			else
			{
				//          [pp(B)]
				//     [u(B)]     [p(R)]    2) Triangle Ÿ��
				//             [n(R)]
				//            l
				//            V
				//          [pp(B)]
				//     [u(B)]     [n(R)]    3) list Ÿ��
				//                  [p(R)]
				if (node == node->parent->left) // 2) Triangle Ÿ��
				{
					// 2) Triangle Ÿ�� -> 3) List Ÿ�� ����
					node = node->parent;
					RightRotate(node);
				}

				//          [pp(B)]
				//     [u(B)]     [p(R)]    3) list Ÿ��
				//                  [n(R)]
				//            l
				//            V
				//          [p(B)]
				//     [pp(R)]     [n(R)]
				//   [u(B)]
				// 3) List Ÿ��
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
		}
	}
	// ������ ����...

	_root->color = Color::Black;
}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == _nil)
		return;

	if (node->left == _nil)
	{
		Color color = node->color;
		Node* right = node->right;
		Replace(node, right);
		// �ڽ��� �ϳ��� ������� �����ص� ��κ� ����� ���� �����ϰ� ������
		if (color == Color::Black)
			DeleteFixup(right);
	}
	else if (node->right == _nil)
	{
		Color color = node->color;
		Node* left = node->left;
		Replace(node, left);
		// �ڽ��� �ϳ��� ������� �����ص� ��κ� ����� ���� �����ϰ� ������
		if (color == Color::Black)
			DeleteFixup(left);
	}
	else
	{
		// ���� ������ ã��
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void BinarySearchTree::DeleteFixup(Node* node)
{
	// BST ���� ����
	// - Case1) ������ ��尡 Red -> �׳� ����
	// - Case2) root�� DB(���� Double Black) -> �׳� �߰� Black ����
	// - Case3) DB�� sibling(����) ��尡 Red
	// -- s = black, p = red (s <-> p ���� ��ȯ)
	// -- DB �������� rotate(p)
	// -- goto other case
	// - Case4) DB�� sibling ��尡 Black && sibling�� ���� �ڽĵ� Black
	// -- �߰� Black�� parent���� ����
	// --- p�� Red�� Black��
	// --- p�� Black�̸� DB��
	// -- s = red
	// -- p�� ������� �˰��� �̾ ���� (DB�� ������ �����ϸ�)
	// - Case5) DB�� sibling ��尡 Black && sibling�� near child = red, far child = black
	// -- s <-> near ���� ��ȯ
	// -- far �������� rotate(s)
	// -- goto case 6
	// - Case6) DB�� sibling ��尡 Black && sibling�� far child = red
	// -- p <-> s ���� ��ȯ
	// -- far = black
	// -- rotate(p) (DB��������)
	// -- �߰� Black ����

	Node* x = node;

	// [Case1][Case2]
	while (x != _root && x->color == Color::Black)
	{
		//         [p]
		//   [x(B)]   [s(?)]
		if (x == x->parent->left)
		{
			// [Case3]
			Node* s = x->parent->right;
			if (x->color == Color::Red)
			{
				//         [p(B)]
				//   [x(B)]      [s(R)]
				//           l
				//           V
				//         [s(B)]
				//     [p(R)]
				//  [x(B)]
				s->color = Color::Black;
				x->parent->color = Color::Red;

				LeftRotate(x->parent);
			}

			// [Case4]
			if (s->left->color == Color::Black && s->right->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}
		}
		else
		{

		}
	}

	x->color = Color::Black;
}

void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == _nil)
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if (v)
		v->parent = u->parent;

	delete u;
}

void BinarySearchTree::LeftRotate(Node* x)
{
	//      [x]
	//   [1]   [y]
	//        [2][3]
	//       l
	//       V
	//      [y]
	//   [x]   [3]
	// [1][2]

	Node* y = x->right;

	x->right = y->left; // [2];
	if (y->left != _nil)y->left->parent = x; // [2]�� nil�� �ƴϸ� �θ��缳��

	y->parent = x->parent;

	if (x->parent == _nil)
		_root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

void BinarySearchTree::RightRotate(Node* y)
{
	//      [y]
	//   [x]   [3]
	// [1][2]
	//       l
	//       V
	//      [x]
	//   [1]   [y]
	//        [2][3]

	Node* x = y->left;

	y->left = x->right; // [2]
	if (x->right != _nil) x->right->parent = y; // [2]�� nil�� �ƴϸ� �θ��缳��

	x->parent = y->parent;

	if (y->parent == _nil)
		_root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}
