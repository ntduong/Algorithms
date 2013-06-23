#include<cstdio>
#include<iostream>
using namespace std;
const int MINV = -100;
const int MAXV = 100;

struct node{
	int data;
	node* left;
	node* right;
};

node* getNewNode(int data){
	node* newNode = new node;
	newNode->data = data;
	newNode->left = 0;
	newNode->right = 0;
	return newNode;
}

node* insert(node* root, int data){
	if(root == 0) return getNewNode(data);
	else{
		if(data <= root->data) root->left = insert(root->left, data);
		else root->right = insert(root->right, data);
		return root;
	}
}

bool lookup(node* root, int target){
	if(root == 0) return false;
	else{
		if(target == root->data) return true;
		else{
			if(target < root->data) return lookup(root->left, target);
			else return lookup(root->right, target);
		}
	}
}

int treeSize(node *root){
	if(root == 0) return 0;
	reurn treeSize(root->left) + 1 + treeSize(root->right);
}

int maxDepth(node *root){
	if(root == 0) return 0;
	int leftDepth = maxDepth(root->left);
	int rightDepth = maxDepth(root->right);
	return max(leftDepth,rightDepth)+1;
}

int minValue(node* root){
	node* cur = root;
	while(cur->left != 0){
		cur = cur->left;
	}

	return cur->data;
}

void printTree(node* root){
	if(root == 0) return;
	printTree(root->left);
	cout << root->data << " ";
	printTree(root->right);
}

bool isBSTHelper(node* root, int minV, int maxV){
	if(root == 0) return true;
	if(root->data < minV || root->data > maxV) return false;
	return isBSTHelper(root->left, minV, root->data) && isBSTHelper(root->right, root->data+1, maxV);
}

bool isBST(node* root){
	return isBSTHelper(root, MINV, MAXV);
}

//how many structurally unique BST are there that store keys: 1, 2,...numKeys
int countTree(int numKeys){
	if(numKeys <= 1) return 1;
	else{
		int sum = 0;
		int left, right, root;
		for(root = 1; root <= numKeys; root++){
			left = countTree(root-1);
			right = countTree(numKeys-root);
			sum += left*right;
		}
		return sum;
	}
}

bool sameTree(node* a, node* b){
	if(a == 0 && b == 0) return true;
	else if(a != 0 && b != 0){
		return a->data == b->data && sameTree(a->left, b->left) && sameTree(a->right, b->right);
	}
	else return false;
}

void mirror(node * root){
	if(root == 0) return;
	node* tmp;
	mirror(root->left);
	mirrot(root->right);

	//swap left - right child
	tmp = root->left;
	root->left = root->right;
	root->right = tmp;
}


int main(){


	return 0;
}
