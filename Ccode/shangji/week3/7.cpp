#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

typedef struct BinTreeNode{
    int data;
    struct BinTreeNode *lchild;
    struct BinTreeNode *rchild;
}BinTreeNode, *BTree;

void CreateBTree(BTree &root){
    int n;
    scanf("%d", &n);
    if(!n){
        root = NULL;
    }
    else{
        root = (BTree) malloc (sizeof(BinTreeNode));
        root->data = n;
        printf("输入%d的左子树(0为空): ", n);
        CreateBTree(root->lchild);
        printf("输入%d的右子树(0为空): ", n);
        CreateBTree(root->rchild);
    }
}

void InOrder(BTree r){
    if(r == NULL) return;
    else{
        if(r->lchild) InOrder(r->lchild);
        printf("%d ", r->data);
        if(r->rchild) InOrder(r->rchild);
    }
}

int a[2];
int len = 0;
bool IsBSTree(BTree r){
    bool ok = true;
    if(r != NULL){
        if(r->lchild)   ok = IsBSTree(r->lchild);
        if(len = 0){
            a[len++] = r->data;
        } else if(len == 1){
            if(a[len] > r->data){
                return false;
            } else{
                a[0] = r->data;
            }
        }
        if(r->rchild)  ok = IsBSTree(r->rchild);
    }
    return ok;
}

int main(){
    BTree root;
    printf("请输入树根(0为空):");
    CreateBTree(root);
    if(root == NULL){
        printf("二叉树为空");
    }
    puts("二叉树中序遍历:");
    InOrder(root);
    puts("");
    len = 0;
    if(IsBSTree(root) == true){
        printf("该二叉树为二叉排序树");
    }else{
        printf("该二叉树不是二叉排序树");
    }
    return 0;
}