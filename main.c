#include <stdio.h>
#include "randomArrayCreator.h"
#include "arraySorter.h"
#include "node.h"

// build tree
struct Node* buildTree(int* arr, int start, int end) {
	if (start > end) return NULL; // base case

	// find middle
	int middle = (start + end) / 2;

	// root
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

	printTree(root);

	return 0;
}
