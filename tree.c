#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (node == NULL) {
       return 0;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct TreeNode* agacolustur(int bas, int son) {
    if (bas > son)
        return NULL;
    int orta = bas + (son - bas) / 2;
    struct TreeNode* root = newNode(pow(2, orta));
    root->left = agacolustur(bas, orta - 1);
    root->right = agacolustur(orta + 1, son);
    return root;
}
int count = 100;
void printTree(struct TreeNode* root, int bosluk) {
    if (root == NULL)
        return;
    bosluk += count;
    printTree(root->right, bosluk);
    printf("\n");
    for (int i = count; i < bosluk; i++)
        printf(" ");
    printf("%d\n", root->data);
    printTree(root->left, bosluk);
}
void print(struct TreeNode* root) {
    printTree(root, 0);
}
void freeTree(struct TreeNode* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
int yapraksayisi(struct TreeNode* node) {
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 1;
    else
        return yapraksayisi(node->left) + yapraksayisi(node->right);
}
int main() {
    int n;
    printf("Bir n sayisi giriniz : ");
    scanf("%d", &n);
    struct TreeNode* root = agacolustur(0, n - 1);
    printf("            %d\n", root->data);
    printf("         /       \\\n");
    if (root->left != NULL) {
        printf("      %d", root->left->data);
    } else {
        printf("      NULL");
    }
    if (root->right != NULL) {
        printf("         %d\n", root->right->data);
    } else {
        printf("         NULL\n");
    }
    if (root->left != NULL && root->left->left != NULL) {
        printf("     / \\");
        if (root->right != NULL && root->right->left != NULL) {
            printf("       / \\\n");
            printf("    %d   %d    %d   %d\n", root->left->left->data, root->left->right->data, root->right->left->data, root->right->right->data);
        }
        else {
            printf("       NULL   NULL\n");
            printf("    %d   %d\n", root->left->left->data, root->left->right->data);
        }
    }
    printf("yaprak sayisi: %d\n", yapraksayisi(root));
    freeTree(root);
    return 0;
}