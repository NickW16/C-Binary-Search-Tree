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

void postOrder(struct Node* root) {
	if (root != NULL) {
		postOrder(root->left);
		postOrder(root->right);
		printf("%d ", root->data);
	}
}

void preOrder(struct Node* root) {
	if (root != NULL) {
		printf("%d ", root->data);
		preOrder(root->left);
		preOrder(root->right);
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

struct Node* find(struct Node* root, int value) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data == value) {
		printf("Value %d was found in the BST!\n", value);
		return root;
	}

	if (value < root->data) {
		return find(root->left, value);
	} else {
		return find(root->right, value);
	}
}

int height(struct Node* node) {
	if (node == NULL) return -1;
	int left = height(node->left);
	int right = height(node->right);
	return 1 + (left > right ? left : right);
}

int depth(struct Node* root, int value) {
	struct Node* current = root;
	int d = 0;

	while (current != NULL) {
		if (current->data == value) {
			return d;
		}
		d++;

		if (value < current->data) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return -1;
}

int checkBalance(struct Node* node) {
	if (node == NULL) return 0;

	int leftHeight = checkBalance(node->left);
	if (leftHeight == -1) return -1;

	int rightHeight = checkBalance(node->right);
	if (rightHeight == -1) return -1;

	if (((leftHeight - rightHeight) > 1) || (rightHeight - leftHeight) > 1) return -1;

	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int isBalanced(struct Node* root) {
	return checkBalance(root) != -1;
}

// levelOrder with callback function to mimic JS
void levelOrder(struct Node* root, void(*callback)(struct Node*)) {
	if (root == NULL) return;

	// queue size
	struct Node* queue[100];
	int front = 0, back = 0;

	queue[back++] = root;

	while(front < back) {
		struct Node* current = queue[front++];
		callback(current); // callback

		if (current->left != NULL) queue[back++] = current->left;
		if (current->right != NULL) queue[back++] = current->right;
	}
}

void printNode(struct Node* node) {
	printf("%d ", node->data);
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

// rebalance
int collectInOrder(struct Node* root, int* arr, int index) {
	if (root == NULL) return index;

	index = collectInOrder(root->left, arr, index);
	arr[index++] = root->data;
	index = collectInOrder(root->right, arr, index);

	return index;
}

struct Node* rebalance(struct Node* root) {
	int values[100];
	int count = collectInOrder(root, values, 0);

	freeTree(root);

	return buildTree(values, 0, count - 1);
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
	printf("inserting number: 50 and 22\n");
	root = insert(root, 50);
	root = insert(root, 22);

	printf("Deleting numbers 80, 50 and 37 (if exists)\n");
	root = deleteItem(root, 80);
	root = deleteItem(root, 50);
	root = deleteItem(root, 37);

	printf("\n -- Testing find --\n");
	struct Node* result = find(root, 22);
	if (result == NULL) {
		printf("22 not found in tree\n");
	}

	printf("\n -- Testing height -- \n");
	struct Node* node22 = find(root, 22);
	if (node22 != NULL) {
		printf("Height of node 22: %d\n", height(node22));
	}

	printf("\n -- Testing depth -- \n");
	int depthNode22 = depth(root, 22);
	if (depthNode22 != -1) {
		printf("Depth of node 22: %d\n", depthNode22);
	}

	printf("\n-- Testing isBalanced --\n");
	if (isBalanced(root)) {
    printf("Tree is balanced!\n");
	} else {
    printf("Tree is NOT balanced!\n");
	}

	root = rebalance(root);
	printf("After rebalance, isBalanced: %s\n", isBalanced(root) ? "Yes" : "No");

	printf("Level-order: ");
	levelOrder(root, printNode);
	printf("\n");

	printTree(root);

	freeTree(root);
	return 0;
}
