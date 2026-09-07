#ifndef NODE_H
#define NODE_H

struct Node {
	int data;
	struct Node* right;
	struct Node* left;
};

struct Node* createNode(int data);

#endif
