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
       return 0; }
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
void agaciyazdirma(struct TreeNode* kok, char matris[10][20], int row, int col, int bosluk) {
    if (kok == NULL)
        return;
    char numara[6];
    sprintf(numara, "%d", kok->data);

    matris[row][col] = numara[0];
    if (kok->data >= 10) {
    matris[row][col + 1] = numara[1];
    if (kok->data >= 100) {
    matris[row][col + 2] = numara[2];
    if (kok->data >= 1000) {
    matris[row][col + 3] = numara[3];
    if (kok->data >= 10000)
    matris[row][col + 4] = numara[4];
            }
        }
    }
    if (kok->left != NULL) {
        matris[row + 1][col - bosluk / 2] = '/';
    agaciyazdirma(kok->left, matris, row + 2, col - bosluk, bosluk / 2);
    }
    if (kok->right != NULL) {
        matris[row + 1][col + bosluk / 2] = '\\';
      agaciyazdirma(kok->right, matris, row + 2, col + bosluk, bosluk / 2);
    }
}
int main() {
    int n;
    printf("Bir n sayisi giriniz : ");
    scanf("%d", &n);
    struct TreeNode* root = agacolustur(0, n - 1);
    char matris[10][20] = {0};
    agaciyazdirma(root, matris, 0, 20 / 2, 20 / 4);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if (matris[i][j] == '\0')
                printf(" ");
            else
                printf("%c", matris[i][j]);
        }
        printf("\n");
    }
    free(root);
    return 0; }