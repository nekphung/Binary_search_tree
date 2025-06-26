#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct node {
	int data;
	//int items;
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

void inOrder1(node* root) {
	if (root != NULL) {
		inOrder1(root->left);
		cout << root->data << " ";
		inOrder1(root->right);
	}
}

void inOrder(node* root) 
{
	if (root == NULL) return;
	stack<node*> st;
	while (root != NULL || !st.empty()) 
	{
		while (root != NULL) {
			st.push(root);
			root = root->left;
		}

		root = st.top(); st.pop();
		cout << root->data << " ";

		root = root->right;
	}
}

void preOrder(node* root) 
{
	if (root == NULL) return;
	stack<node*> st;
	st.push(root);
	while (!st.empty()) {
		root = st.top(); st.pop();
		cout << root->data << " ";

		if (root->right) st.push(root->right);
		if (root->left) st.push(root->left);
	}

}

void postOrder(node* root) 
{
	if (root == NULL) return;
	stack<node*> st1, st2;
	st1.push(root);
	while (!st1.empty()) {
		root = st1.top(); st1.pop();
		st2.push(root);

		if (root->left) st1.push(root->left);
		if (root->right) st1.push(root->right);
	}
	while (!st2.empty()) {
		cout << st2.top()->data << " ";
		st2.pop();
	}
}

void preOrder1(node* root) {
	if (root != NULL) {
		cout << root->data << " ";
		preOrder1(root->left);
		preOrder1(root->right);
	}
}

void postOrder1(node* root) {
	if (root != NULL) {
		postOrder1(root->left);
		postOrder1(root->right);
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
			if (top->right) s2.push(top->right);
			if (top->left) s2.push(top->left);
		}
		while (!s2.empty()) {
			node* top = s2.top(); s2.pop();
			cout << top->data << " ";

			if (top->left) s1.push(top->left);
			if (top->right) s1.push(top->right);
		}
	}
}

void levelOrder(node* root) {
	queue<node*> q;
	if (root != NULL) {
		q.push(root);
		while (!q.empty()) {
			int size = q.size();
			for (int i = 0; i < size; i++)
			{
				node* top = q.front(); q.pop();
				cout << top->data << " ";
				if (top->left != NULL) q.push(top->left);
				if (top->right != NULL) q.push(top->right);
			}
			cout << endl;
		}
	}
}

void reverseInorder(node* root, int& count, int& result) {
	// Dieu kien dung cua no la gi
	if (root == NULL || count >= 2) {
		return;
	}

	reverseInorder(root->right, count, result);
	count++;
	if (count == 2) {
		result = root->data;
		return;
	}

	reverseInorder(root->left, count, result);
}

int findSecondLargest(node* root) {
	int count = 0;
	int result = -1;
	reverseInorder(root, count, result);
	return result;
}

void Bai16(node* root, int& k, int& sum) {
	if (root->left != NULL) {
		Bai16(root->left, k, sum);
	}
	if (k > 0) {
		sum += root->data;
		k--;
	}
	else {
		return;
	}
	if (root->right != NULL) {
		Bai16(root->right, k, sum);
	}
}

int Bai16(node* root, int k) {
	int sum = 0;
	Bai16(root, k, sum);
	return sum;
}

void Bai17(node* root, int n1, int n2, vector<int> &ans) {
	if (root == NULL) return;
	if (root->data > n1) {
		Bai17(root->left, n1, n2, ans);
	}
	if (root->data >= n1 && root->data <= n2) {
		ans.push_back(root->data);
	}
	if (root->data < n2) {
		Bai17(root->right, n1, n2, ans);
	}
}

void Bai17(node* root, int n1, int n2) {
	vector<int> ans;
	Bai17(root, n1, n2, ans);
	for (int x : ans) {
		cout << x << " ";
	}
}

void StoreInorder(node* root, vector<int> &res) 
{
	if (root == NULL) return;
	StoreInorder(root->left, res);
	res.push_back(root->data);
	StoreInorder(root->right, res);
}

node* Bai18(int left, int right, vector<int> &arr) {
	if (left > right) return NULL;
	int mid = (left + right) / 2;
	node* root = new node(arr[mid]);
	root->left = Bai18(left, mid - 1, arr);
	root->right = Bai18(mid + 1, right, arr);
	return root;
}

node* Bai18(node* root) {
	vector<int> res;
	StoreInorder(root, res);
	return Bai18(0, res.size() - 1, res);
}

node* Bai19(node* root, int n1, int n2) {
	if (root == NULL) return root;
	if (root->data < n1 && root->data < n2) {
		return Bai19(root->right, n1, n2);
	}
	else if (root->data > n1 && root->data > n2) {
		return Bai19(root->left, n1, n2);
	}
	return root;
}

int distance(node* root, int x) {
	if (root->data == x) {
		return 0;
	}
	if (root->data < x) {
		return 1 + distance(root->right, x);
	}
	return 1 + distance(root->left, x);
}

int Bai20(node* root, int a, int b) {
	if (root == NULL) return 0;
	if (root->data < a && root->data < b) {
		return Bai20(root->left, a, b);
	}

	if (root->data > a && root->data > b) {
		return Bai20(root->right, a, b);
	}

	return distance(root, a) + distance(root, b);
}

// Duyet theo quy tac la inorder 
int kthSmallestRecur(node* root, int& cnt, int k) {
	if (root == NULL) return -1;
	int left = kthSmallestRecur(root->left, cnt, k);
	if (left != -1) {
		return left;
	}
	cnt++;
	if (cnt == k) {
		return root->data;
	}
	int right = kthSmallestRecur(root->right, cnt, k);
	return right;
}

int Bai21(node* root, int k) {
	int cnt = 0;
	return kthSmallestRecur(root, cnt, k);
}

node* deleteAllLeaf(node* root) {
	if (root == NULL) {
		return root;
	}
	if (root->left == NULL && root->right == NULL) {
		delete root;
		return NULL;
	}
	root->left = deleteAllLeaf(root->left);
	root->right = deleteAllLeaf(root->right);
	return root;
}

void TraversalInorder(node* root, vector<int>& res) {
	if (root == NULL) return;
	TraversalInorder(root->left, res);
	res.push_back(root->data);
	TraversalInorder(root->right, res);
}

bool Bai23(node* root, int target) {
	vector<int> res;
	TraversalInorder(root, res);
	int left = 0, right = res.size() - 1;
	while (left < right) {
		int sum = res[left] + res[right];
		if (sum == target) {
			return true;
		}
		else if (sum < target) {
			left++;
		}
		else {
			right--;
		}
	}
	return false;
}

void Duyet(node* root, int a, int& ans) {
	if (root == NULL) return;
	if (root->data == a) return;
	else if (root->data < a) {
		Duyet(root->right, a, ans);
	}

}

void Duyet(node* root, int a, int b, int & ans) {
	if (root == NULL) return;
	Duyet(root->left, a, b, ans);

	if (root->data >= a && root->data <= b && root->data > ans) {
		ans = root->data;
	}

	Duyet(root->right, a, b, ans);
}

int Bai24(node* root, int a, int b) {
	if (root->data < a && root->data < b) {
		root = root->right;
	}
	if (root->data > a && root->data > b) {
		root = root->left;
	}
	int ans = INT_MIN;
	Duyet(root, a, b, ans);
	return ans;
}

bool find(node* root, int key, node* temp) {
	if (root == NULL) return false;
	node* current = root;
	while (current != NULL) {
		if (current->data == key && current != temp) {
			return true;
		}
		else if (current->data < key) {
			current = current->right;
		}
		else {
			current = current->left;
		}
	}
	return false;
}

bool Bai25(node* root, node* current, int target) {
	if (current == NULL) return false;
    
	int value = target - current->data;
	if (find(root, value, current)) {
		return true;
	}
	return Bai25(root, current->left, target) || Bai25(root, current->right, target);
}

// Cach duyet NLR
void Bai27(node* root, int& cnt) {
	if (root == NULL) return;
	if (root->left == NULL && root->right == NULL) {
		cnt++;
		return;
	}
	Bai27(root->left, cnt);
	Bai27(root->right, cnt);
}

int Bai27(node* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	return Bai27(root->left) + Bai27(root->right);
}

void Bai28(node* root) {
	queue<node*> q;
	if (root == NULL) return;
	q.push(root);
	int cnt = 0;
	while (!q.empty()) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			node* top = q.front(); q.pop();
			cout << top->data << "(" << cnt << ")" << " ";
			if (top->left) q.push(top->left);
			if (top->right) q.push(top->right);
		}
		cout << endl;
		cnt++;
	}
}

bool Bai29(node* root, int x, vector<int>& path) {
	if (root == NULL) return false;
	path.push_back(root->data);
	if (root->data == x) return true;
	if ((root->data < x && Bai29(root->right, x, path)) || (root->data > x && Bai29(root->left, x, path))) {
		return true;
	}
	path.pop_back();
	return false;
}

void Bai30(node* root, int a, int b) {
	if (root == NULL) return;
	vector<int> path_a;
	vector<int> path_b;
    while (root->data < a && root->data < b) {
		root = root->right;
	}
	while (root->data > a && root->data > b) {
		root = root->left;
	}
	if (!Bai29(root, a, path_a) || !Bai29(root, b, path_b)) return;

	for (int i = path_a.size() - 1; i > 0; i--) {
		cout << path_a[i] << " ";
	}
	for (int i = 0; i < path_b.size(); i++) {
		cout << path_b[i] << " ";
	}
}

// Duyệt theo NLR
void Bai31(node* root, vector<int> &path) {
	if (root == NULL) return;
	path.push_back(root->data);
	if (root->left == NULL && root->right == NULL) {
		for (int x : path) {
			cout << x << " ";
		}
		cout << endl;
	}
	else {
		Bai31(root->left, path);
		Bai31(root->right, path);
	}
	path.pop_back(); // Back Tracking
}

int height(node* root) {
	if (root == NULL) return -1;
	return 1 + max(height(root->left), height(root->right));
}

bool check1(node* root, int level, int h) {
	if (root == NULL) return true;
	if (root->left == NULL && root->right == NULL && level < h) return false;
	return check1(root->left, level + 1, h) && check1(root->right, level + 1, h);
}

bool check2(node* root) {
	if (root == NULL) return true;
	if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
	{
		return false;
	}
	return check2(root->left) && check2(root->right);
}

bool Bai32(node* root) {
	queue<node*> q;
	if (root == NULL) return true;
	q.push(root);
	int level = 0;
	while (!q.empty()) {
		int size = q.size(); 
		if (size != pow(2, level)) return false;
		for (int i = 0; i < size; i++) {
			node* top = q.front(); q.pop();
			if (top->left) q.push(top->left);
			if (top->right) q.push(top->right);
		}
		level++;
	}
	return true;
}

vector<int> Merge(node* root1, node* root2) {
	vector<int> res;
	stack<node*> s1, s2;
	while (root1 || root2 || !s1.empty() || !s2.empty()) {
		while (root1) {
			s1.push(root1);
			root1 = root1->left;
		}
		while (root2) {
			s2.push(root2);
			root2 = root2->left;
		}
		if (s2.empty() || !s1.empty() && s1.top()->data <= s2.top()->data) {
			root1 = s1.top();
			s1.pop();
			res.push_back(root1->data);
			root1 = root1->right;
		}
		else {
			root2 = s2.top();
			s2.pop();
			res.push_back(root2->data);
			root2 = root2->right;
		}
	}
	return res;
}

int kthLargestRecur(node* root, int& cnt, int k) {
	if (root == NULL) return -1;
	int right = kthLargestRecur(root->right, cnt, k);
	if (right != -1) {
		return right;
	}

	cnt++;

	if (cnt == k) {
		return root->data;
	}

	int left = kthLargestRecur(root->left, cnt, k);
	return left;
}

void INorder(node* root, vector<int>& seq, int& index) {
	if (root == NULL) return;
	INorder(root->left, seq, index);
    
	if (index < seq.size() && root->data == seq[index]) {
		index++;
	}
	INorder(root->right, seq, index);
}

bool Bai35(node* root, vector<int>& seq) {
	if (root == NULL) return false;
	int index = 0;
	INorder(root, seq, index);
	return index == seq.size();
}

bool Find(node* root, int key, node* current) {
	if (current == NULL) return false;
	while (root != NULL) {
		if (root->data == key && root != current) {
			return true;
		}
		else if (root->data < key) {
			root = root->right;
		}
		else {
			root = root->left;
		}
	}
	return false;
}

int Bai36(node* root, node* current, int target) {
	if (current == NULL) return 0;
	int ans = 0;

	int key = target - current->data;
	if (Find(root, key, current)) {
		ans++;
	}
	ans += Bai36(root, current->left, target);
	ans += Bai36(root, current->right, target);
	return ans;
}

int countNodes(node* root) {
	if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(node* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) {
		return 1;
	}
	return countLeaves(root->left) + countLeaves(root->right);
}

void countInrange(node* root, int a, int b, int& count) {
	if (root == NULL) return;
	if (root->data >= a && root->data <= b) {
		count++;
	}
	countInrange(root->left, a, b, count);
	countInrange(root->right, a, b, count);
}

void Bai37(node* root, int a, int b) {
	cout << countNodes(root) << endl;
	cout << countLeaves(root) << endl;
	int res = 0;
	countInrange(root, a, b, res);
	cout << res << endl;
}

int Bai38(node* root, int value) {
	int closet = root->data;
	if (root == NULL) return 0;
	while (root) {
		if (abs(root->data - value) < abs(closet - value)) {
			closet = root->data;
		}
		if (root->data < value) {
			root = root->right;
		}
		else if (root->data > value) {
			root = root->left;
		}
		else break;
	}
	return closet;
}

bool Bai41(node* root) {
	queue<node*> q;
	if (root == NULL) return true;
	q.push(root);
	bool checknodenull = false;
	while (!q.empty()) {
		node* top = q.front(); q.pop();
		if (top->left != NULL) {
			if (checknodenull) return false;
			q.push(top->left);
		}
		else {
			checknodenull = true;
		}
		if (top->right != NULL) {
			if (checknodenull) return false;
			q.push(top->right);
		}
		else {
			checknodenull = true;
		}
	}
	return true;
}

void printLongestPath(node* root, vector<int>& path, int level, int h)
{
	if (root == NULL) return;
	path.push_back(root->data);

	if (root->left == NULL && root->right == NULL && level == h) {
		for (int x : path) {
			cout << x << " ";
		}
		cout << endl;
	}
	printLongestPath(root->left, path, level + 1, h);
	printLongestPath(root->right, path, level + 1, h);
	path.pop_back();
}

bool isEquivalent(node* root1, node* root2) 
{
	if (root1 == NULL && root2 == NULL) return true;
	if (root1 == NULL || root2 == NULL) return false;
	if (root1->data != root2->data) return false;
	return (isEquivalent(root1->left, root2->left)) && (isEquivalent(root1->right, root2->right));
}

int findGoal(node* root, int k) {
	int floor = -1, ceil = -1;
	while (root) {
		if (root->data == k) return root->data;
		if (root->data < k) {
			floor = root->data;
			root = root->right;
		}
		else {
			ceil = root->data;
			root = root->left;
		}
	}
	if (floor == -1) return ceil;
	if (ceil == -1) return floor;
	return (ceil - k <= k - floor) ? ceil : floor;
}

int findClosest(node* root, int k) {
	int closest = root->data;
	node* cur = root;

	while (cur) {
		if (abs(cur->data - k) < abs(closest - k)) {
			closest = cur->data;
		}
		// Có thể dùng đệ quy ở này duyệt theo NLR

		if (k < cur->data) {
			cur = cur->left;
		}
		else if (k > cur->data) {
			cur = cur->right;
		}
		else {
			return cur->data; // k == cur->data
		}
	}

	return closest;
}

int countNode(node* root) {
	if (root == NULL) return 0;
	return 1 + countNode(root->left) + countNode(root->right);
}

void traversal(node* root, int& k, int& ans) 
{
	if (root == NULL) return;
	traversal(root->left, k, ans);
	k--;
	if (k == 0) {
		ans = root->data;
		return;
	}
	traversal(root->right, k, ans);
}

int findmedium(node* root) 
{
	if (root == NULL) return -1;
	int n = countNode(root);
	int k = (n + 1) / 2;
	int ans = -1;
	traversal(root, k, ans);
	return ans;
}

//int findKth(node* root, int k) {
//	if (root == NULL) return -1;
//
//	int leftCount = 0;
//	if (root->left != NULL) {
//		leftCount = root->left->items;
//	}
//	if (k == leftCount + 1) return root->data;
//	else if (k <= leftCount) return findKth(root->left, k);
//	else return findKth(root->right, k - (leftCount + 1));
//}
//
//int Findmedium(node* root) {
//	if (root == NULL) return -1;
//	int n = root->items + 1;
//	int k = (n + 1) / 2;
//	return findKth(root, k);
//}

int Height(node* root) {
	if (root == NULL) return -1;
	else return 1 + max(Height(root->left), Height(root->right));
}

void TraverSal(node* root, int level, int height, int &ans) {
	if (root == NULL) return;
	if (level == height && ans == -1) {
		ans = root->data;
		return;
	}
	TraverSal(root->right, level + 1, height, ans);
	TraverSal(root->left, level + 1, height, ans);
}

int Bai46(node* root) {
	if (root == NULL) return -1;
	int h = Height(root);
	int ans = -1;
	TraverSal(root, 0, h, ans);
	return ans;
}

bool isPrime(int n) {
	if (n < 2) return false;
	else {
		for (int i = 2; i <= sqrt(n); i++) {
			if (n % i == 0) return false;
		}
	}
	return true;
}

int countNT(node* root) {
	if (root == NULL) return 0;

	int count = 0;

	if (isPrime(root->data)) count++;
	count += countNT(root->left);
	count += countNT(root->right);

	return count;
}

void bai47(node* root, int& ans) {
	if (root == NULL) return;
	int leftCount = countNT(root->left);
	int rightCount = countNT(root->right);
	if (leftCount < rightCount) {
		ans++;
	}
	bai47(root->left, ans);
	bai47(root->right, ans);
}

int Bai47(node* root) {
	if (root == NULL) return -1;
	int ans = 0;
	bai47(root, ans);
	return ans;
}

int countSubTree(node* root) {
	if (root == NULL) return 0;
	else return 1 + countSubTree(root->left) + countSubTree(root->right);
}

void bai48(node* root) {
	if (root == NULL) return;
    // in ra theo level kem theo so luong node con cua moi node
	queue<node*>q;
	q.push(root);
	while (!q.empty()) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			node* top = q.front(); q.pop();
			cout << top->data << " (" << countSubTree(top) - 1 << ") ";
			if (top->left) q.push(top->left);
			if (top->right) q.push(top->right);
		}
		cout << endl;
	}
}

void bai49(node* root, int& ans) {
	if (root == NULL) return;
	// Xu ly tai node root sau do toi L roi toi R theo truong hop duyet NLR
	int leftCount = countSubTree(root->left);
	int rightCount = countSubTree(root->right);
	if (leftCount < rightCount) {
		ans++;
	}
	bai49(root->left, ans);
	bai49(root->right, ans);
}

int Bai49(node* root) {
	if (root == NULL) return -1;
	int ans = 0;
	bai49(root, ans);
	return ans;
}

void menu(node*& root, vector<int>& arr, vector<int> &a) 
{ 
	while (true) {
		system("cls");
		cout << "Level order: " << endl;
		levelOrder(root);
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
		cout << "15. Find the second largest." << endl;
		cout << "16. Sum of k smallest elements in BST." << endl;
		cout << "17. Print BST keys in given Range." << endl;
		cout << "18. Balance a Binary Search Tree." << endl;
		cout << "19. LCA in BST - Lowest Common Ancestor in Binary Search Tree." << endl;
		cout << "20. Shortest Distance between Two Nodes in BST." << endl;
		cout << "21. k-th Smallest in BST (Order Statistics in BST)." << endl;
		cout << "22. Remove all leaf nodes from the binary search tree." << endl;
		cout << "23. Two Sum in BST - Pair with given sum." << endl;
		cout << "24. Maximum element between two nodes of BST." << endl;
		cout << "25. Find a pair with given sum in a Balanced BST." << endl;
		cout << "26. Path from this node to the another node in the BST." << endl;
		cout << "27. Count number leaf of the BST." << endl;
		cout << "28. Print all the height of the node in BST." << endl;
		cout << "29. In đường đi từ node gốc tới node khác trong cây." << endl;
		cout << "30. In đường đi từ 2 node bất kỳ trong cây." << endl;
		cout << "31. In ra đường đi từ node gốc tới các node còn lại." << endl;
		cout << "32. Cay nhi phan hoan hao." << endl;
		cout << "33. Merge two BST into the BSTs." << endl;
		cout << "34. K'th Largest Element in BST when modification to BST is not allowed." << endl;
		cout << "35. Check if given sorted sub-sequence exists in binary search tree." << endl;
		cout << "36. Count pairs from two BSTs whose sum is equal to a given value x." << endl;
		cout << "37. BST Element Counting." << endl;
		cout << "38. Find Closest Value in BST." << endl;
		cout << "39. BST to Balanced BST." << endl;
		cout << "40. Construct BST from Sorted Array." << endl;
		cout << "41. Cay nhi phan hoan chinh." << endl;
		cout << "42. Print Longest Path." << endl;
		cout << "43. isEquivalent between two binary search tree." << endl;
		cout << "44. Tim phan tu x sao cho |k - x| la nho nhat." << endl;
		cout << "45. Tim trung vi cua cay theo lower bound." << endl;
		cout << "45.1. Tim trung vi khi no co them truong items." << endl;
		cout << "46. In ra phan tu cuoi cung phai nhat." << endl;
		cout << "47. In ra so node co so luong node con trai nhieu hon so node con phai ve SL so NT." << endl;
		cout << "48. In ra so node con cua 1 node bat ky trong cay." << endl;
		cout << "49. In ra so luong node co cay con trai nhieu hon cay con phai." << endl;
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
			cout << "\nLevelOrder: \n";
			levelOrder(root);
			cout << endl;
			system("pause");
		}
		else if (choice == 15) {
			int ans = findSecondLargest(root);
			cout << ans << endl;
			system("pause");
		}
		else if (choice == 16) {
			cout << "Nhap k = "; int k; cin >> k;
			int sum = Bai16(root, k);
			cout << "Ans = " << sum << endl;
			system("pause");
		}
		else if (choice == 17) {
			int n1, n2;
			cout << "Nhap n1 va n2 = ";
			cin >> n1 >> n2;
			Bai17(root, n1, n2);
			system("pause");
		}
		else if (choice == 18) {
			node* temp = Bai18(root);
			levelOrder(temp);
			system("pause");
		}
		else if (choice == 19) {
			cout << "Nhap n1 va n2 = ";
			int n1, n2; cin >> n1 >> n2;
			node* temp = Bai19(root, n1, n2);
			cout << temp->data << " ";
			system("pause");
		}
		else if (choice == 20) {
			int a, b;
			cout << "Nhap a va b = ";
			cin >> a >> b;
			int ans = Bai20(root, a, b);
			cout << "Ans = " << ans << endl;
			system("pause");
		}
		else if (choice == 21) {
			cout << "Nhap k = ";
			int k; cin >> k;
			cout << Bai21(root, k) << endl;
			system("pause");
		}
		else if (choice == 22) {
			node* temp = deleteAllLeaf(root);
			levelOrder(temp);
			system("pause");
		}
		else if (choice == 23) {
			cout << "Nhap target = ";
			int target; cin >> target;
			if (Bai23(root, target)) {
				cout << "Exist pair with sum equal target" << endl;
			}
			else cout << "No exist" << endl;
			system("pause");
		}
		else if (choice == 24) {
			int a, b;
			cout << "Nhap a va b = ";
			cin >> a >> b;
			cout << Bai24(root, a, b) << endl;
			system("pause");
		}
		else if (choice == 25) {
			cout << "Nhap target = ";
			int target; cin >> target;
			if (Bai25(root, root, target)) {
				cout << "Exist pair" << endl;
			}
			else cout << "No exist" << endl;
			system("pause");
		}
		else if (choice == 27) {
			int ans = 0;
			Bai27(root, ans);
			cout << ans << endl;
			system("pause");
		}
		else if (choice == 28) {
			cout << "In ra theo bac: " << endl;
			Bai28(root);
			system("pause");
		}
		else if (choice == 29) {
			vector<int> path;
			int x; cout << "Nhap x = ";
			cin >> x;
			if (Bai29(root, x, path)) {
				for (int x : path) {
					cout << x << " ";
				}
			}
			else {
				cout << "Khong ton tai duong di" << endl;
			}
			system("pause");
		}
		else if (choice == 30) {
			cout << "Nhap a va b = ";
			int a, b; cin >> a >> b;
			Bai30(root, a, b);
			system("pause");
		}
		else if (choice == 31) {
			vector<int> path;
			Bai31(root, path);
			system("pause");
		}
		else if (choice == 32) {
			int h = height(root);
			if (Bai32(root)) cout << "Cay hoan hao" << endl;
			else cout << "Cay khong hoan hao" << endl;
			system("pause");
		}
		else if (choice == 33) {
			node* root2 = new node(2);
			root2->left = new node(0);
			root2->right = new node(9);
			root2->right->right = new node(16);
			vector<int> ans = Merge(root, root2);
			for (int x : ans) {
				cout << x << " ";
			}
			system("pause");
		}
		else if (choice == 34) {
			cout << "Nhap k = ";
			int k; cin >> k;
			int cnt = 0;
			int ans = kthLargestRecur(root, cnt, k);
			cout << ans << endl;
			system("pause");
		}
		else if (choice == 35) {
			cout << "Nhap so luong phan tu trong tap hop = ";
			int n; cin >> n;
			vector<int> res;
			for (int i = 0; i < n; i++) {
				int x; cin >> x;
				res.push_back(x);
			}
			if (Bai35(root, res)) {
				cout << "True" << endl;
			}
			else cout << "False" << endl;
			system("pause");
		}
		else if (choice == 36) {
			int target;
			cout << "Nhap target = ";
			cin >> target;
			cout << "Ans = " << Bai36(root, root, target) / 2 << endl;
			system("pause");
		}
		else if (choice == 37) {
			cout << "Nhap a va b = ";
			int a, b; cin >> a >> b;
			Bai37(root, a, b);
			system("pause");
		}
		else if (choice == 38) {
			cout << "Nhap gia tri can tim closet = ";
			int x; cin >> x;
			cout << "Ans = " << Bai38(root, x) << endl;
			system("pause");
		}
		else if (choice == 41) {
			if (Bai41(root)) {
				cout << "Cay hoan chinh" << endl;
			}
			else cout << "Cay nhi phan khong phan chinh" << endl;
			system("pause");
		}
		else if (choice == 42) {
			int h = height(root);
			vector<int> path;
			printLongestPath(root, path, 0, h);
			system("pause");
		}
		else if (choice == 43) {
			node* root2 = NULL;
			for (int x : a) {
				insert1(root2, x);
			}
			if (isEquivalent(root, root2)) {
				cout << "Hai cay nhi phan tim kiem tuong duong nhau" << endl;
			}
			else cout << "Khong tuong duong nhau" << endl;
			system("pause");
		}
		else if (choice == 44) {
			cout << "Nhap k = "; int k; cin >> k;
			cout << findGoal(root, k);
			system("pause");
		}
		else if (choice == 45) {
			int ans = findmedium(root);
			cout << "Ans = " << ans << endl;
			system("pause");
		}
		else if (choice == 46) {
			int ans = Bai46(root);
			cout << ans << endl;
			system("pause");
		}
		else if (choice == 47) {
			int ans = Bai47(root);
			cout << "Ans = " << ans << endl;
			system("pause");
		}
		else if (choice == 48) {
			bai48(root);
			system("pause");
		}
		else if (choice == 49) {
			int ans = Bai49(root);
			cout << "Ans = " << ans << endl;
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
	vector<int> arr1 = { 5, 6, 3, 1, 4, 8, 7, 11, 12, 15, 16, 14 };
	vector<int> arr2 = { 5, 6, 3, 1, 4, 8, 7, 11, 12, 15, 16, 14 };
	menu(root, arr1, arr2);
	system("pause");
	return 0;
}