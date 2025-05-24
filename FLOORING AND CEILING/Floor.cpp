#include <iostream>
using namespace std;

typedef int Key;
#define NOT_FOUND -1


class BST 
{
public:
	struct node {
		Key value;
		node* left, * right;
		node(Key data) {
			value = data;
			left = right = NULL;
		}
	};
	typedef node* link;
private:
	link root;

public:
	// Khoi tao cay
	BST() 
	{
		root = NULL;
	}
	void insert(link& root, int x) {
		if (root == NULL) {
			root = new node(x);
		}
		else {
			if (root->value == x) return;
			else if (root->value < x) insert(root->right, x);
			else insert(root->left, x);
		}
	}
	// Ham giao dien
	void insert(Key val) {
		insert(root, val);
	}
	void printTree(link root) {
		if (root != NULL) {
			cout << root->value << " ";
			printTree(root->left);
			printTree(root->right);
		}
	}
	void printTree()  // Ham giao dien
	{
		printTree(root);
	}


	Key floor(node* root, int x) 
	{
		int ans = -1;
		while(root)
		{
			if (root->value == x) {
				return root->value;
			}
			if (x > root->value) {
				ans = root->value;
				root = root->right;
			}
			else {
				root = root->left;
			}
		}
		return ans;
	}

	Key ceiling(node* root, int x) 
	{
		int ans = -1;
		while (root)
		{
			if (root->value == x) {
				return root->value;
			}
			if (x < root->value) {
				ans = root->value;
				root = root->left;
			}
			else {
				root = root->right;
			}
		}
		return ans;
	}


	Key floor(int x) {
		return floor(root, x);
	}

	Key ceiling(int x) {
		return ceiling(root, x);
	}

	int height(node* root) {
		if (root == NULL) return 0;
		int l = height(root->left);
		int r = height(root->right);
		return 1 + max(l, r);
	}

	int height() {
		return height(root);
	}
	/* Cách tìm kiếm phần tử thứ nhất: */
	/*node* search(node* root, int value)
	{
		if (root == NULL) return NULL;
		if (root->value == value) return root;
		else if (root->value > value) {
			node* leftnode = search(root->left, value);
			if (leftnode != NULL) return leftnode;
		}
		return search(root->right, value);
	}*/
	/* Cách tìm kiếm phần tử thứ hai: (không dùng đệ quy) */
	/*node* Search(node* root, int value)
	{
		while (root) 
		{
			if (root->value == value) return root;
			else if (root->value < value) 
				root = root->right;
			else 	root = root->left;
		}
		return NULL;
	}*/

	/* Them mot node vao cay tim kiem nhi phan */
	/*void Insert(node*& root, int data)
	{
		node* p = root;
		while (p) {
			if (p->value == data) return;
		    if (p->value > data) {
				if (p->left == NULL) {
					p->left = new node(data);
					return;
				}
				p = p->left;
			}
			if (p->value < data) {
				if (p->right == NULL) {
					p->right = new node(data);
					return;
				}
				p = p->right;
			}
		}	
	}*/

	/*
	- Xoa node:
	   + Neu no la node la thi de
	   + Neu no co mot con thi xoa roi dich phan tu
	   + Neu no la node co du 2 node thi:
		  + Chon thang trai nhat cua cay con ben phai
		  + Chon thang phai nhat cua cay con ben trai
	*/

	void Timthangthemang(node*& x, node*& y) {
		if (y->left != NULL)
			Timthangthemang(x, y->left);
		else {
			x->value = y->value;
			x = y;
			y = y->right;
		}
	}
	void DeleteNode(node*& root, int x)
	{
		if (root == NULL) return;
		if (root->value < x) {
			DeleteNode(root->right, x);
		}
		else if (root->value > x) {
			DeleteNode(root->left, x);
		}
		else {
			// root->value == x
			node* x = root;
			if (root->left == NULL) {
				root = root->right;
			}
			else if (root->right == NULL)
			{
				root = root->left;
			}
			else {
				Timthangthemang(x, root->right);
			}
			delete x;
		}
	}

	void DeleteNode(int value) {
		DeleteNode(root, value);
	}

	/*void Insert(int data) {
		Insert(root, data);
	}	*/
};


int main() {
	BST tree;
	int n; cin >> n;
	while (n--) {
		int x; cin >> x;
		tree.insert(x);
	}
	tree.printTree();
	cout << endl;
	/*tree.Insert(100);
	tree.printTree();
	cout << endl;
	tree.Delete(100);
	tree.printTree();*/

	int x; cin >> x;
	cout << tree.floor(x) << endl;
	cout << tree.ceiling(x) << endl;
	cout << tree.height() << endl;
	return 0;
}