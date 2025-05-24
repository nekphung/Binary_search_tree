#include <iostream>
#include <vector>
using namespace std;

class BST
{
public:
	struct node {
		int value;
		node* left, * right;
		node(int data) {
			value = data;
			left = right = NULL;
		}
	};
private:
	node* root;

public:
	// Khoi tao cay
	BST()
	{
		root = NULL;
	}
	void insert(node* & root, int x) {
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
	void insert(int val) {
		insert(root, val);
	}
	void printTree(node* root) {
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

	void Timthangthemang(node*& x, node*& y) {
		if (y->right != NULL)
			Timthangthemang(x, y->right);
		else {
			x->value = y->value;
			x = y;
			y = y->left;
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
				Timthangthemang(x, root->left);
			}
			delete x;
		}
	}

	void DeleteNode(int value) {
		DeleteNode(root, value);
	}

};

int main()
{
	BST tree;
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		tree.insert(x);
	}
	int y; cin >> y;
	tree.DeleteNode(y);
	tree.printTree();

	return 0;
}