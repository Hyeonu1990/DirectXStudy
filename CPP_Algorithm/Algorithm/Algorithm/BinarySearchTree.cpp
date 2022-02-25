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
	// 전위 순회 (preoder traverse)
	// 중위 순회 (inoder traverse)
	// 후위 순회 (postoder traverse)

	//   [중]
	// [좌][우]

	if (node == _nil)
		return;

	// 전위 : [중]이 앞에 온다
	// 중위 : [중]이 중간에 온다
	// 후위 : [중]이 마지막에 온다
	Print_Inorder(node->left);
	cout << node->key << endl; // [중]
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

	// 검사
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red;

	InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{
	// 1) p = red, uncle = red
	// -> p = black, uncle = black, pp = red로 바꿈
	// 2) p = red, uncle = black (triangle)
	// -> 회전을 통해서 case 3) 으로 바꿈
	// 3) p = red, uncle = black (list)
	// -> 색상 변경 + 회전

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
				node = node->parent->parent; // 다음 확인할 노드
			}
			else
			{
				//          [pp(B)]
				//     [p(R)]     [u(B)]    2) Triangle 타입
				//        [n(R)]
				//            l
				//            V
				//          [pp(B)]
				//     [n(R)]     [u(B)]    3) list 타입
				//  [p(R)]
				if (node == node->parent->right) // 2) Triangle 타입
				{
					// 2) Triangle 타입 -> 3) List 타입 변경
					node = node->parent;
					LeftRotate(node);
				}

				//          [pp(B)]
				//     [p(R)]     [u(B)]    3) list 타입
				//  [n(R)]
				//            l
				//            V
				//          [p(B)]
				//     [n(R)]     [pp(R)]    3) list 타입
				//                    [u(R)]
				// 3) List 타입
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
				node = node->parent->parent; // 다음 확인할 노드
			}
			else
			{
				//          [pp(B)]
				//     [u(B)]     [p(R)]    2) Triangle 타입
				//             [n(R)]
				//            l
				//            V
				//          [pp(B)]
				//     [u(B)]     [n(R)]    3) list 타입
				//                  [p(R)]
				if (node == node->parent->left) // 2) Triangle 타입
				{
					// 2) Triangle 타입 -> 3) List 타입 변경
					node = node->parent;
					RightRotate(node);
				}

				//          [pp(B)]
				//     [u(B)]     [p(R)]    3) list 타입
				//                  [n(R)]
				//            l
				//            V
				//          [p(B)]
				//     [pp(R)]     [n(R)]
				//   [u(B)]
				// 3) List 타입
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
		}
	}
	// 일종의 공식...

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
		// 자식이 하나인 레드노드는 삭제해도 경로별 블랙노드 갯수 일정하게 유지됨
		if (color == Color::Black)
			DeleteFixup(right);
	}
	else if (node->right == _nil)
	{
		Color color = node->color;
		Node* left = node->left;
		Replace(node, left);
		// 자식이 하나인 레드노드는 삭제해도 경로별 블랙노드 갯수 일정하게 유지됨
		if (color == Color::Black)
			DeleteFixup(left);
	}
	else
	{
		// 다음 데이터 찾기
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void BinarySearchTree::DeleteFixup(Node* node)
{
	// BST 삭제 실행
	// - Case1) 삭제할 노드가 Red -> 그냥 삭제
	// - Case2) root가 DB(이하 Double Black) -> 그냥 추가 Black 삭제
	// - Case3) DB의 sibling(형제) 노드가 Red
	// -- s = black, p = red (s <-> p 색상 교환)
	// -- DB 방향으로 rotate(p)
	// -- goto other case
	// - Case4) DB의 sibling 노드가 Black && sibling의 양쪽 자식도 Black
	// -- 추가 Black을 parent에게 이전
	// --- p가 Red면 Black됨
	// --- p가 Black이면 DB됨
	// -- s = red
	// -- p를 대상으로 알고리즘 이어서 실행 (DB가 여전히 존재하면)
	// - Case5) DB의 sibling 노드가 Black && sibling의 near child = red, far child = black
	// -- s <-> near 색상 교환
	// -- far 방향으로 rotate(s)
	// -- goto case 6
	// - Case6) DB의 sibling 노드가 Black && sibling의 far child = red
	// -- p <-> s 색상 교환
	// -- far = black
	// -- rotate(p) (DB방향으로)
	// -- 추가 Black 제거

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
	if (y->left != _nil)y->left->parent = x; // [2]가 nil이 아니면 부모재설정

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
	if (x->right != _nil) x->right->parent = y; // [2]가 nil이 아니면 부모재설정

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
