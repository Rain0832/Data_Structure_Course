# 第六章 树与二叉树

> **姓名：****
>
> **学号：****
>
> **Github仓库： https://github.com/Rain0832/Data_Structure_Course.git**

> **上机时间：第 13 周星期六（11 月 30 日）**
>
> **上机地点：基础实验大楼506**

### 题目描述

##### 必做 哈夫曼编码

- 利用哈夫曼编码进行通信可以大大提高信道利用率，缩短信息传输时间， 降低传输成本，但是，这要求在发送端通过一个编码系统对待传数据预先编码， 在接收端将传来的数据进行译码（复原）。
- 对于双工信道（即可以双向传输信息的通道）每端都需要一个完整的编/译码系统。
- 试为这样的信息收发站写一哈 夫曼编/译码系统。
-  基本要求： 
- （1）初始化：从终端输入字符集的大小 $n$，以及 $n$ 个字符和 $n$ 个权值建立哈夫 曼树。
- （2）输出：哈夫曼树，及各字符对应的编码。 
- （3）编码：利用建好的哈夫曼树，对输入的待发送电文进行编码。输入原文、输出编码串。 
- （4）译码：利用建好的哈夫曼树，对输入的已接收电文进行译码。输入编码串、输出原文。

> 基本思想： 
>
> （1）对输入的一段欲编码的字符串进行统计各个字符出现的次数，并将它们转化为权值${w_1,w_2,......，w_N}$，构成n棵二叉树的集合$F={T_1,T_2,......，T_n}$ 把它们保存到结构体数组$HT[n]$中,其中${Ti}$是按它们的ASCⅡ码值先后排序。其中，每棵二叉树$Ti$中只有一个带权为$W_i$的根结点的权值为其左、右子树上根结 点的权值之和。 
>
> （2）在$HT[1..i]$中选取两棵根结点的权值最小且没有被选过的树作为左右 子树构造一棵新的二叉树，且置新的二叉树的根结点的权值为左、右子树 上根结点的权值之和。 
>
> （3）哈夫曼树已经建立后，从叶子到根逆向求每一个字符的哈夫曼编码。

##### 选做：二叉树遍历

- 实现二叉树中序遍历的递归算法。

### 1. 必做 哈夫曼编码 函数源码

##### 1.1 哈夫曼树定义

```cpp
// 定义哈夫曼树节点
typedef struct HuffmanNode {
    char ch;                  // 字符
    int weight;               // 权值
    struct HuffmanNode *left; // 左子树
    struct HuffmanNode *right;// 右子树
    int used;                 // 是否被合并
} HuffmanNode;

// 哈夫曼编码表
typedef struct {
    char ch;                  // 字符
    char code[256];           // 编码
} HuffmanCode;

// 全局编码表
HuffmanCode huffmanCodes[256];
int codeIndex = 0;

// 创建哈夫曼节点
HuffmanNode* createNode(char ch, int weight) {
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    node->ch = ch;
    node->weight = weight;
    node->left = node->right = NULL;
    node->used = 0;
    return node;
}
```

##### 1.2 哈夫曼树生成

```cpp
// 排序函数，用于 qsort
int compare(const void *a, const void *b) {
    return (*(HuffmanNode **)a)->weight - (*(HuffmanNode **)b)->weight;
}

// 生成哈夫曼树
// 输入：字符数组、权值数组、字符数
HuffmanNode* buildHuffmanTree(char chars[], int weights[], int n) {
    HuffmanNode **forest = (HuffmanNode **)malloc(n * sizeof(HuffmanNode *));
    for (int i = 0; i < n; i++) {
        forest[i] = createNode(chars[i], weights[i]);
    }

    while (n > 1) {
        qsort(forest, n, sizeof(HuffmanNode *), compare);

        HuffmanNode *left = forest[0];
        HuffmanNode *right = forest[1];
        HuffmanNode *newNode = createNode('\0', left->weight + right->weight);
        newNode->left = left;
        newNode->right = right;

        forest[0] = newNode;
        forest[1] = forest[n - 1];
        n--;
    }

    HuffmanNode *root = forest[0];
    free(forest);
    return root;
}
```

##### 1.3 哈夫曼编码表

```cpp
// 生成哈夫曼编码表（递归）
// 输入：哈夫曼树根节点、当前编码、当前编码长度
void generateCodes(HuffmanNode *root, char *code, int length) {
    if (!root) return;

    if (root->left == NULL && root->right == NULL) {
        code[length] = '\0';
        huffmanCodes[codeIndex].ch = root->ch;
        strcpy(huffmanCodes[codeIndex].code, code);
        codeIndex++;
        return;
    }

    code[length] = '0';
    generateCodes(root->left, code, length + 1);

    code[length] = '1';
    generateCodes(root->right, code, length + 1);
}
```

##### 1.4 哈夫曼编码函数

```cpp
// 编码函数
// 输入：待编码的字符串
// 输出：编码后的 01 密文
void encode(char *input) {
    printf("Encoded: ");
    for (int i = 0; i < strlen(input); i++) {
        char *code = getCode(input[i]);
        if (code) {
            printf("%s", code);
        }
    }
    printf("\n");
}

// 查找字符的编码
// 返回编码长度，如果找不到，返回 -1
char* getCode(char ch) {
    for (int i = 0; i < codeIndex; i++) {
        if (huffmanCodes[i].ch == ch) {
            return huffmanCodes[i].code;
        }
    }
    return NULL;
}

```

##### 1.5 哈夫曼解码函数

```cpp
// 解码函数
// 输入：哈夫曼树根节点、编码后的 01 密文
// 输出：解码后的明文
void decode(HuffmanNode *root, char *encoded) {
    printf("Decoded: ");
    HuffmanNode *current = root;
    for (int i = 0; i < strlen(encoded); i++) {
        current = (encoded[i] == '0') ? current->left : current->right;
        if (current->left == NULL && current->right == NULL) {
            printf("%c", current->ch);
            current = root;
        }
    }
    printf("\n");
}
```

##### 1.6 哈夫曼字符权重生成

```cpp
// 统计字符频率
void countFrequencies(char *input, char *chars, int *weights, int *n) {
    int freq[256] = {0};
    for (int i = 0; input[i] != '\0'; i++) {
        freq[(unsigned char)input[i]]++;
    }

    *n = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            chars[*n] = (char)i;
            weights[*n] = freq[i];
            (*n)++;
        }
    }
}
```

##### 1.7 主函数

```cpp
// 主函数
int main() {
    // 输入字符串
    char input[256];
    printf("Enter a string: ");
    scanf("%s", input);

    // 字符频率作为权值
    char chars[256];
    int weights[256];
    int n;
    countFrequencies(input, chars, weights, &n);

    // 根据字符构建哈夫曼表
    printf("Characters and weights:\n");
    for (int i = 0; i < n; i++) {
        printf("%c: %d\n", chars[i], weights[i]);
    }

    HuffmanNode *root = buildHuffmanTree(chars, weights, n);

    char code[256] = {0};
    generateCodes(root, code, 0);

    printf("Huffman Codes:\n");
    for (int i = 0; i < codeIndex; i++) {
        printf("%c: %s\n", huffmanCodes[i].ch, huffmanCodes[i].code);
    }

    // 编码：输出编码后的 01 密文
    encode(input);

    // 解码：输入编码后的 01 密文，输出解码后的明文
    char encoded[256];
    printf("Enter encoded string to decode: ");
    scanf("%s", encoded);
    decode(root, encoded);

    return 0;
}
```

### 2. 选做 二叉树遍历 函数源码

##### 2.1 二叉树定义

```cpp
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
```

##### 2.2 中序遍历递归函数

```cpp
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
```

##### 2.3 主函数

```cpp
int main() {
    // 例子：二叉树
    //             1
    //            / \
    //           2   3
    //          / \ / \
    //         4  5 6  7
    
    // 输出: 4 2 5 1 6 3 7

    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    
    printf("Inorder traversal: ");
    inorderTraversal(root);  
    printf("\n");
    
    return 0;
}
```

### 3. 调试程序后得到的结果

##### 3.1 必做

- 输入原始字符串，可以统计得到出现过的字符对应的权重（出现频率）

![image-20241204221202441](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241204221202441.png)

- 根据对应权重，进行哈夫曼编码（权重大的编码短）

![image-20241204221210178](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241204221210178.png)

- 对输入的字符串进行编码为 0 1 密文

![image-20241204221217689](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241204221217689.png)

- 若输入密文可以解码得到明文

![image-20241204221224729](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241204221224729.png)

##### 选作

- 对于二叉树

	​            1

	​           / \

	​         2    3

	​        / \   / \

	​      4  5   6  7

- 输出中序遍历顺序

![image-20241204221632355](C:\Users\27100\AppData\Roaming\Typora\typora-user-images\image-20241204221632355.png)

验证为正确

### 4. 实验结论和结果分析

- **哈夫曼编码系统**：成功构造哈夫曼树，生成字符编码并实现基本的编码解码功能，可以优化解码逻辑和编码表查找效率。

- **二叉树中序遍历**：递归实现正确，输出符合预期，适用于小规模二叉树，但需要主函数中主动键入二叉树，可以考虑在终端输入。

- **结论**：系统验证了哈夫曼编码与中序遍历的理论正确性，但需改进性能和健壮性，提升对大规模数据的处理能力。
