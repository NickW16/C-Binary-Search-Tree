#include <stdio.h>
#include <stdlib.h>

#include "randomArrayCreator.h"
#include "arraySorter.h"
#include "node.h"

// build tree
struct Node* buildTree(int* arr, int start, int end) {
	if (start > end) return NULL;

	int middle = (start + end) / 2;

	struct Node* root = createNode(arr[middle]);

	root->left = buildTree(arr, start, middle - 1);
	root->right = buildTree(arr, middle + 1, end);

	return root;
}

void inOrder(struct Node* root) {
	if (root != NULL) {
		inOrder(root->left);
		printf("%d ", root->data);
		inOrder(root->right);
	}
}

// operations:
struct Node* insert(struct Node* root, int value) {
	if (root == NULL) {
		return createNode(value);
	}

	if (root->data == value) {
		return root;
	}

	if (value < root->data) {
		root->left = insert(root->left, value);
	} else if (value > root->data) {
		root->right = insert(root->right, value);
	}

	return root;
}

struct Node* getSuccessor(struct Node* curr) {
	curr = curr->right;
	while (curr != NULL && curr->left != NULL) {
		curr = curr->left;
	}
	return curr;
}

struct Node* deleteItem(struct Node* root, int value) {
	if (root == NULL) {
		printf("Attempted to delete node %d but it was not found!\n", value);
		return root;
	}

	// search for key
	if (root->data > value) {
		root->left = deleteItem(root->left, value);
	} else if (root->data < value) {
		root->right = deleteItem(root->right, value);
	} else {

		//cases when root has no children or only one child
		if (root->left == NULL && root->right == NULL) {
			printf("%d deleted successfully\n", value);
			free(root);
			return NULL;
		}

		if (root->left == NULL) {
			struct Node* temp = root->right;
			printf("%d deleted successfully\n", value);
			free(root);
			return temp; // only right child
		}
		if (root->right == NULL) {
			struct Node* temp = root->left;
			printf("%d deleted successfully\n", value);
			free(root);
			return temp; // only left child
		}

		// find successor:
		struct Node* successor = getSuccessor(root);
		root->data = successor->data;
		root->right = deleteItem(root->right, successor->data);
	}

	return root;
}

// print a tree
void printSpaces(int count) {
	for (int i = 0; i < count; i++) {
		printf(" ");
	}
}

void printTreeHelper(struct Node* root, int space, int indent) {
	if (root == NULL) return;

	space += indent;

	// right subtree
	printTreeHelper(root->right, space, indent);

	printf("\n");
	printSpaces(space);
	printf("%d\n", root->data);

	// left subtree
	printTreeHelper(root->left, space, indent);
}

void printTree(struct Node* root) {
	printf("\nBalanced BST:\n");
	printTreeHelper(root, 0, 5);
	printf("\n");
}

void freeTree(struct Node* root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

int main() {
	// PRINTING:

	// generate array and fill with rdm numbers
	int array[10];
	randomArrayCreator(array, 10);

	printf("Original array (10): [ ");
	for (int i = 0; i < 10; i++) {
		printf("%d", array[i]);
		if (i < 9) printf(", ");
	}
	printf(" ]\n");

	// sort and remove duplicates:
	int newSize = arraySorter(array, 10);

	// print sorted
	printf("Sorted (%d): [ ", newSize);
	for (int i = 0; i < newSize; i++) {
		printf("%d", array[i]);
		if (i < newSize - 1) printf(", ");
	}
	printf(" ]\n");

	struct Node* root = buildTree(array, 0, newSize - 1);

	printf("In-order: [ ");
	inOrder(root);
	printf("]\n");

	printf("Root: %d\n", root->data);

	// test cases:
	printf("--Test cases:\n");
	printf("inserting number: 50\n");
	root = insert(root, 50);

	printf("Deleting numbers 80, 50 and 37 (if exists)\n");
	root = deleteItem(root, 80);
	root = deleteItem(root, 50);
	root = deleteItem(root, 37);

	printTree(root);

	freeTree(root);
	return 0;
}
