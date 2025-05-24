#include <iostream> 
using namespace std;

struct node {
	int data;
	node* left, * right;
	node(int x) {
		data = x;
		left = right = NULL;
	}
};

void Addnode(node* &root, int x) {
	if (root == NULL) {
		root = new node(x);
	}
	else {
		if (root->data > x) {
			Addnode(root->left, x);
		}
		else if (root->data < x) {
			Addnode(root->right, x);
		}
	}
}
node* searchnode(node* root, int x) {
	if (root == NULL) return NULL;
	else 
	{
		if (x < root->data) {
			searchnode(root->left, x);
		}
		else if (x > root->data) {
			searchnode(root->right, x);
		}
		else {
			return root;
		}
	}
}

int main() 
{
	node* root = NULL;
	int n; cin >> n;
	while (n--) 
	{
		int x; cin >> x;
	    Addnode(root, x);
	}
	int y; cin >> y;
	node* temp = searchnode(root, y);
	if (temp != NULL) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
	return 0;
}