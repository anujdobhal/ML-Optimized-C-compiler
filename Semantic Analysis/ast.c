#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===================== AST NODE ===================== */

typedef struct ASTNode {
    char type[20];      // ADD, SUB, MUL, DIV, ID, NUM, ASSIGN
    char value[100];    // variable name or number
    struct ASTNode *left, *right;
} ASTNode;


/* ===================== CREATE NODE ===================== */

ASTNode* createNode(char* type, char* value, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));

    strcpy(node->type, type);

    if (value != NULL)
        strcpy(node->value, value);
    else
        strcpy(node->value, "");

    node->left = left;
    node->right = right;

    return node;
}


/* ===================== TEMP VARIABLE ===================== */

int tempCount = 0;

char* newTemp() {
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempCount++);
    return temp;
}


/* ===================== OPERATOR MAP ===================== */

char* getOp(char* type) {
    if (strcmp(type, "ADD") == 0) return "+";
    if (strcmp(type, "SUB") == 0) return "-";
    if (strcmp(type, "MUL") == 0) return "*";
    if (strcmp(type, "DIV") == 0) return "/";

    return "";
}


/* ===================== TAC GENERATOR ===================== */

char* generateTAC(ASTNode* node) {
    if (node == NULL) return "";

    // Leaf nodes
    if (strcmp(node->type, "NUM") == 0 || strcmp(node->type, "ID") == 0) {
        return node->value;
    }

    // Assignment
    if (strcmp(node->type, "ASSIGN") == 0) {
        char* right = generateTAC(node->right);
        printf("%s = %s\n", node->value, right);
        return node->value;
    }

    // Binary operations
    char* left = generateTAC(node->left);
    char* right = generateTAC(node->right);

    char* temp = newTemp();

    printf("%s = %s %s %s\n", temp, left, getOp(node->type), right);

    return temp;
}


/* ===================== DEBUG (OPTIONAL) ===================== */

void printAST(ASTNode* node, int level) {
    if (node == NULL) return;

    for (int i = 0; i < level; i++) printf("  ");

    printf("%s (%s)\n", node->type, node->value);

    printAST(node->left, level + 1);
    printAST(node->right, level + 1);
}
