#include <iostream>
#include <cstdio>

using namespace std;


class Node {
	Node *left, *right, *parent;
	int color; //0: red, 1: black
public:
	virtual int compareTo(Node*) = 0;
	virtual void update() = 0;
};

class RBTree {
	Node *root;
public:
	RBTree() {
		root = NULL;
	}
	void insert(Node *p) {
		if (!root) {
			root = p;
			root->color = 1;
			return;
		}
		Node *tmp = root;
		p->color = 0; //default red
		while (true) {
			if (p->compareTo(tmp) <= 0) {
				if (!tmp->left) {
					tmp->left = p;
					p->parent = tmp;
					break;
				} else {
					tmp = tmp->left;
				}
			} else {
				if (!tmp->right) {
					tmp->right = p;
					p->parent = tmp;
					break;
				} else {
					tmp = tmp->right;
				}
			}
		}
		_rb_fix_up(p);
	}
private:
	void _rb_fix_up(Node *z) {
		
	}
};

int main() {

}
