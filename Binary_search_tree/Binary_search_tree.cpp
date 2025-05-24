#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct node {
	int data;
	node* left, * right;
	node(int key) {
		data = key;
		left = right = NULL;
	}
};

// Dung de quy
void insert1(node* &root, int key) {
	if (root == NULL) {
		root = new node(key);
		return;
	}
	if (root->data == key) return;
	else if (root->data < key) {
		insert1(root->right, key);
	}
	else insert1(root->left, key);
}

// Khong dung de quy
void insert2(node* &root, int key) {
	if (root == NULL) {
		root = new node(key);
		return;
	}
	node* current = root;
	while (current) {
		if (current->data == key) return;
		else if (current->data < key) {
			if (current->right == NULL) {
				current->right = new node(key);
				return;
			}
			else current = current->right;
		}
		else {
			if (current->left == NULL) {
				current->left = new node(key);
				return;
			}
			else current = current->left;
		}
	} 
}

// Dung de quy va tra ve con tro
node* insert3(node* root, int key) {
	if (root == NULL) {
		return new node(key);
	}
	else if (root->data < key) 
	{
		root->right = insert3(root->right, key);
	}
	else if (root->data > key) 
	{
		root->left = insert3(root->left, key);
	}
	else {
		return root;
	}
	return root;
}


// Dung de quy
bool search1(node* root, int key) {
	if (root == NULL) return false;
	if (root->data < key) return search1(root->right, key);
	if (root->data > key) return search1(root->left, key);
	return true; // Found
}

// Khong dung de quy
bool search2(node* root, int key) {
	if (root == NULL) return false;
	node* cur = root;
	while (cur) {
		if (cur->data < key) {
			cur = cur->right;
		}
		else if (cur->data > key) {
			cur = cur->left;
		}
		else return true;
	}
	return false;
}

// Dung de quy va tra ve con tro
node* search3(node* root, int key) {
	if (root == NULL) return root;
	if (root->data < key) return search3(root->right, key);
	if (root->data > key) return search3(root->left, key);
	return root;
}

node* minVal(node* root)
{
	node* current = root;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

void replaced(node*& x, node*& y) {
	if (y->left != NULL) {
		replaced(x, y->left);
	}
	else {
		x->data = y->data;
		x = y;
		y = y->right;
	}
}

// Xoa dung de quy
void remove1(node*& root, int key)
{
	if (root == NULL) return;
	if (root->data < key) {
		remove1(root->right, key);
	}
	else if (root->data > key) {
		remove1(root->left, key);
	}
	else {
		// Tim thay
		node* temp;
		if (root->left == NULL) {
			temp = root;
			root = root->right;
		}
		else if (root->right == NULL) {
			temp = root;
			root = root->left;
		}
		else {
			replaced(temp, root->right);
		}
		delete temp;
	}
}

// Xoa khong dung de quy
void remove2(node*& root, int key)
{
	if (root == NULL) return;
	node* parent = NULL;
	node* cur = root;
	// Step 1: Find the node with value == key
	while (cur != NULL && cur->data != key) 
	{
		parent = cur;
		if (cur->data < key) cur = cur->right;
		else cur = cur->left;
	}

	if (cur == NULL) return; //  Khong tim thay phan tu voi key da cho

	// Step 2: The node has 1 child or 0 child
	if ((cur->left == NULL) || (cur->right == NULL)) {
		node* child = ((cur->left != NULL) ? cur->left : cur->right);

		if (parent == NULL) {
			delete root;
			root = child;
		}
		else {
			if (parent->left == cur) {
				parent->left = child;
			}
			else parent->right = child;
			delete cur;
		}
	}

	else {
		// Step 3: The node has 2 child 
		node* succParent = cur;
		node* succ = cur->right;

		while (succ->left != NULL) {
			succ = succ->left;
		}

		cur->data = succ->data; // Gan lai gia tri cua cur
		if (succParent->left == succ) {
			succParent->left = succ->right;
		}
		else {
			succParent->right = succ->right;
		}
		delete succ;
	}
}

// Xoa dung de quy va tra ve con tro
node* remove3(node*& root, int key)
{
	if (root == NULL) return root;
	if (root->data < key) {
		root->right = remove3(root->right, key);
	}
	else if (root->data > key) {
		root->left = remove3(root->left, key);
	}
	else {
		// Tim thay
		if ((root->left == NULL) || (root->right == NULL)) {
			node* child = ((root->left != NULL) ? root->left : root->right);
			delete root;
			return child;
		}
		else {
			node* tmp = minVal(root->right);
			root->data = tmp->data;
			root->right = remove3(root->right, key);
		}
	}
	return root;
}


// Tim ra phan tu dau tien <= key
int floor(node* root, int key) {
	int ans = -1;
	node* cur = root;
	while (cur) {
		if (cur->data == key) return cur->data;
		if (cur->data < key) {
			ans = cur->data;
			cur = cur->right;
		}
		else {
			cur = cur->left;
		}
	}
	return ans;
}

// Tim ra phan tu dau tien >= key
int ceil(node* root, int key) {
	int ans = -1;
	node* cur = root;
	while (cur) {
		if (cur->data == key) return cur->data;
		if (cur->data > key) {
			ans = cur->data;
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	return ans;
}

int MaxTree(node* root) {
	if (root == NULL) return -1;
	node* cur = root;
	while (cur->right != NULL) {
		cur = cur->right;
	}
	return cur->data;
}

int MinTree(node* root) {
	if (root == NULL) return -1;
	node* cur = root;
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur->data;
}

void inOrder(node* root) {
	if (root != NULL) {
		inOrder(root->left);
		cout << root->data << " ";
		inOrder(root->right);
	}
}

void preOrder(node* root) {
	if (root != NULL) {
		cout << root->data << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

void postOrder(node* root) {
	if (root != NULL) {
		postOrder(root->left);
		postOrder(root->right);
		cout << root->data << " ";
	}
}

void xoanoc(node* root) {
	if (root == NULL) return;
	stack<node* > s1;
	stack<node* > s2;
	s1.push(root);
	while (!s1.empty() || !s2.empty()) {
		while (!s1.empty())
		{
			node* top = s1.top(); s1.pop();
			cout << top->data << " ";
			if (top->right != NULL) s2.push(top->right);
			if (top->left != NULL) s2.push(top->left);
		}
		while (!s2.empty()) {
			node* top = s2.top(); s2.pop();
			cout << top->data << " ";

			if (top->left != NULL) s1.push(top->left);
			if (top->right != NULL) s1.push(top->right);
		}
	}
}

void levelOrder(node* root) {
	queue<node*> q;
	if (root != NULL) {
		q.push(root);
		while (!q.empty()) {
			node* top = q.front(); q.pop();
			cout << top->data << " ";
			if (top->left != NULL) q.push(top->left);
			if (top->right != NULL) q.push(top->right);
		}
	}
}

void menu(node*& root, vector<int>& arr) 
{ 
	while (true) {
		system("cls");
		cout << " ---------------- MENU ---------------- " << endl;
		cout << "0. Exit." << endl;
		cout << "1. Insert 1 (recursive)." << endl;
		cout << "2. Insert 2 (non-recursive)." << endl;
		cout << "3. Insert 3 (recursive, returns node)." << endl;
		cout << "4. Search 1 (recursive)." << endl;
		cout << "5. Search 2 (non-recursive)." << endl;
		cout << "6. Search 3 (recursive, returns node)." << endl;
		cout << "7. Delete 1 (recursive)." << endl;
		cout << "8. Delete 2 (non-recursive)." << endl;
		cout << "9. Delete 3 (recursive, returns node)." << endl;
 		cout << "10. Find floor (greatest value <= key)." << endl;
		cout << "11. Find ceil (smallest value >= key)." << endl;
		cout << "12. Find maximum value in BST." << endl;
		cout << "13. Find minimum value in BST." << endl;
		cout << "14. Print tree (all-orders traversal)." << endl;
		cout << " --------------------------------------- " << endl;
		cout << "Enter your choice: ";
		int choice;
		cin >> choice;
		if (choice == 0) {
			break;
		}
		else if (choice == 1) 
		{
			for (int x : arr) {
				insert1(root, x);
			}
		}
		else if (choice == 2) {
			for (int x : arr) {
				insert2(root, x);
			}
		}
		else if (choice == 3) {
			for (int x : arr) {
				root = insert3(root, x);
			}
		}
		else if (choice == 4) {
			cout << "Enter your key need to search: ";
			int value;
			cin >> value;
			if (search1(root, value)) {
				cout << "Found" << endl;
			}
			else cout << "Not Found" << endl;
			system("pause");
		}
		else if (choice == 5) {
			cout << "Enter your key need to search: ";
			int value;
			cin >> value;
			if (search2(root, value)) {
				cout << "Found" << endl;
			}
			else cout << "Not Found" << endl;
			system("pause");
		}
		else if (choice == 6) {
			cout << "Enter your key need to search: ";
			int value;
			cin >> value;
			if (search3(root, value)) {
				cout << "Found" << endl;
			}
			else cout << "Not Found" << endl;
			system("pause");
		}
		else if (choice == 7) {
			cout << "Enter your key need to delete: ";
			int value;
			cin >> value;
			remove1(root, value);
		}
		else if (choice == 8) {
			cout << "Enter your key need to delete: ";
			int value;
			cin >> value;
			remove2(root, value);
		}
		else if (choice == 9) {
			cout << "Enter your key need to delete: ";
			int value;
			cin >> value;
			root = remove3(root, value);
		}
		else if (choice == 10) {
			cout << "Enter your key to search floor: ";
			int value; cin >> value;
			int ans = floor(root, value);
			if (ans == -1) {
				cout << "No exist" << endl;
			}
			else cout << ans << endl;
			system("pause");
		}
		else if (choice == 11) {
			cout << "Enter your key to search ceil: ";
			int value; cin >> value;
			int ans = ceil(root, value);
			if (ans == -1) {
				cout << "No exist" << endl;
			}
			else cout << ans << endl;
			system("pause");
		}
		else if (choice == 12) {
			int ans = MaxTree(root);
			if (ans != -1) {
				cout << "Max = " << ans << endl;
			}
			else cout << "Empty" << endl;
			system("pause");
		}
		else if (choice == 13) {
			int ans = MinTree(root);
			if (ans != -1) {
				cout << "Min = " << ans << endl;
			}
			else cout << "Empty" << endl;
			system("pause");
		}
		else if (choice == 14)
		{
			cout << "InOrder: ";
			inOrder(root); 
			cout << "\nPreOrder: ";
			preOrder(root);
			cout << "\nPostOrder: ";
			postOrder(root);
			cout << "\nXoanOc: ";
			xoanoc(root);
			cout << "\nLevelOrder: ";
			levelOrder(root);
			cout << endl;
			system("pause");
		}
		else {
			cout << "Error. Try again!" << endl;
			system("pause");
		}
	}
}
int main() {
	node* root = NULL;
	vector<int> arr = { 5, 3, 4, 1, 6, 8, 7, 11, 12, 15 };
	menu(root, arr);
	system("pause");
	return 0;
}