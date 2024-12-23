#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int element;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

AVLNode* create_node(int e) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->element = e;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(AVLNode* node) {
    return node == NULL ? 0 : node->height;
}

int find_max(int a, int b) {
    return a > b ? a : b;
}

//* Hàm xoay đơn trái-trái 
AVLNode* rotateWithLeftChild(AVLNode* k2) {
    AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = find_max(height(k2->left), height(k2->right)) + 1;
    k1->height = find_max(height(k1->left), k2->height) + 1;
    return k1;
}

//* Hàm xoay đơn phải-phải
AVLNode* rotateWithRightChild(AVLNode* k2) {
    AVLNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = find_max(height(k2->left), height(k2->right)) + 1;
    k1->height = find_max(height(k1->right), k2->height) + 1;
    return k1;
}

//* Hàm xoay kép trái-phải
AVLNode* doubleWithLeftChild(AVLNode* k3) {
    k3->left = rotateWithRightChild(k3->left);
    return rotateWithLeftChild(k3);
}

//* Hàm xoay kép phải-trái
AVLNode* doubleWithRightChild(AVLNode* k3) {
    k3->right = rotateWithLeftChild(k3->right);
    return rotateWithRightChild(k3);
}

//* Hàm kiểm tra cân bằng
AVLNode* balance(AVLNode* node) {
    if(node == NULL) return NULL;
    if(height(node->left) - height(node->right) > 1) {
        if(height(node->left->left) >= height(node->left->right)) {
            node = rotateWithLeftChild(node);
        }
        else {
            node = doubleWithLeftChild(node);
        }
    } 
    else if(height(node->right) - height(node->left) > 1) {
        if(height(node->right->right) >= height(node->right->left)) {
            node = rotateWithRightChild(node);
        }
        else {
            node = doubleWithRightChild(node);
        }
    }
    node->height = find_max(height(node->left), height(node->right)) + 1;
    return node;
}

//* Hàm nhập node mới
AVLNode* insert(AVLNode* root, int e) {
    if(root == NULL) {
        return create_node(e);
    }
    if(e <= root->element) {
        root->left = insert(root->left, e);
    }
    else {
        root->right = insert(root->right, e);
    }
    return balance(root);
}

AVLNode* findMin(AVLNode* root) {
    if(root == NULL) return NULL; 
    while(root->left != NULL) {   
        root = root->left;
    }
    return root; 
}

//* Hàm in cây theo thứ tự In-Order
void inOrder(AVLNode* root) {
    if(root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->element);
    inOrder(root->right);
}

//* Hàm in cây theo thứ tự Pre-Order
void preOrder(AVLNode* root) {
    if(root == NULL) return;
    printf("%d ", root->element);
    preOrder(root->left);
    preOrder(root->right);
}

//* Hàm in cây theo thứ tự Post-Order
void postOrder(AVLNode* root) {
    if(root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->element);
}

int main() {
    AVLNode* root = NULL;

    int elements[] = {17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58};
    int n = sizeof(elements) / sizeof(elements[0]);
    for (int i = 0; i < n; i++) {
        root = insert(root, elements[i]);
    }

    printf("Pre-order Traversal:\n");
    preOrder(root);
    printf("\nIn-order Traversal:\n");
    inOrder(root);
    printf("\nPost-order Traversal:\n");
    postOrder(root);

    return 0;
}