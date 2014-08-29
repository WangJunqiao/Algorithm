#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
	TreeNode *left, *right;
	int val;
};

int find_max(TreeNode *root) {
	if (root == NULL) {
		return 0;
	}
	//使用BFS而不用DFS是为了防止出现Stack-over-flow
	queue<TreeNode*> q;
	q.push(root);
	int max_val = root->val, min_val = root->val;
	while (!q.empty()) {
		TreeNode *tmp = q.front();
		q.pop();
		if (tmp->val > max_val) {
			max_val = tmp->val;
		}
		if (tmp->val < min_val) {
			min_val = tmp->val;
		}
		if (tmp->left) {
			q.push(tmp->left);
		} 
		if (tmp->right) {
			q.push(tmp->right);
		}
	}
	return max_val - min_val;
}

int mi = 10000, ma = 0;

void gen(TreeNode *p, int num) {
	if (num) {
		
	}
}

int main() {


	
}
