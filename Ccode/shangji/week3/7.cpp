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
        printf("����%d��������(0Ϊ��): ", n);
        CreateBTree(root->lchild);
        printf("����%d��������(0Ϊ��): ", n);
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
    printf("����������(0Ϊ��):");
    CreateBTree(root);
    if(root == NULL){
        printf("������Ϊ��");
    }
    puts("�������������:");
    InOrder(root);
    puts("");
    len = 0;
    if(IsBSTree(root) == true){
        printf("�ö�����Ϊ����������");
    }else{
        printf("�ö��������Ƕ���������");
    }
    return 0;
}