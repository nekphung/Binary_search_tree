#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node {
	int data;
	node* left, * right;
	node(int val) {
		data = val;
		left = right = NULL;
	}
};

void insert(node*& root, int val) {
	if (root == NULL) { 
		root = new node(val);
		return;
	}
	if (root->data == val) return;
	else if (root->data < val) {
		insert(root->right, val);
	}
	else insert(root->left, val);
}


node* search(node* root, int val) {
	if (root == NULL) return root;
	if (root->data == val) {
		return root; 
	}
	else if (root->data < val)
		return search(root->right, val);
	else
		return search(root->left, val);
}



void duyet(node* root) {
    if (!root) return;
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            node* curr = q.front(); q.pop();
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << endl;
    }
}


int main() {
	node* root = NULL;
	vector<int> arr = { 15, 10, 20, 9, 14, 19, 25};
	for (int x : arr) {
		insert(root, x);
	}
	duyet(root);
	int t; cin >> t;
	while(t--) 
	{
		int x; cin >> x;
		node* ans = search(root, x);
		if (ans) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}