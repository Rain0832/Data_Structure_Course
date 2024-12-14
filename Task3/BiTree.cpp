#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    int data;               // 数据域
    struct TreeNode* left;  // 左子树
    struct TreeNode* right; // 右子树
} TreeNode;

// 创建一个新节点
TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 中序遍历递归函数
void inorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return; // 基本情况：空节点不做任何操作
    }
    
    // 递归遍历左子树
    inorderTraversal(root->left);
    
    // 访问当前节点
    printf("%d ", root->data);
    
    // 递归遍历右子树
    inorderTraversal(root->right);
}

int main() {
    // 例子：二叉树
    //             1
    //            / \
    //           2   3
    //          / \ / \
    //         4  5 6  7

    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    
    // 输出中序遍历结果
    printf("中序遍历: ");
    inorderTraversal(root);  // 输出: 4 2 5 1 6 3 7
    printf("\n");
    
    return 0;
}
