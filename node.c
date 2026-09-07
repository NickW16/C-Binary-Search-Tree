#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node* createNode(int data) {
	struct Node* newNode = malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("Memory Allocation Failed!\n");
		return NULL;
	}
	newNode->data = data;
	newNode->right = NULL;
	newNode->left = NULL;

	return newNode;
}
