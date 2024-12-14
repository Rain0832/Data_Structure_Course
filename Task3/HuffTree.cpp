#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
