#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 97;
typedef int elemType;
typedef struct DuLNode
{
    elemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode, *DuLinklist;

DuLinklist create()
{
    DuLNode *head, *tail, *p;
    head=(DuLinklist)malloc(sizeof(DuLNode));
    //tail=(DuLinklist)malloc(sizeof(DuLNode));
    head->prior = NULL;
    head->next = NULL;
    tail = head;
    elemType c;
    bool flag = false;
    while(1)
    {
        p=(DuLinklist)malloc(sizeof(DuLNode));
        scanf("%d",&c);
        if(c==0)
        {
            if(!flag) head = NULL;
            break ;
        }
        flag = true;
        p->data=c;
        p->next = NULL;
        p->prior = tail;
        tail->next = p;
        tail = p;
        //printf("Creat Check\n");
    }
    return head;
}

DuLinklist srandCreate(DuLinklist head, int max_item)
{
    if(max_item <=0) return (head = NULL);
    DuLinklist ptmp1 = NULL, ptmp2 = NULL;
    head = (DuLNode *)malloc(sizeof(DuLNode));
    if(head == NULL)
    {
        printf("No memory!!!\n");
    }
    ptmp1 = head;
    srand(time(NULL));
    for(int i = 0; i < max_item; ++i)
    {
        ptmp2 = (DuLNode *)malloc(sizeof(DuLNode));
        if(ptmp2 == NULL)
        {
            printf("No memory!!!\n");
        }
        ptmp2->data = rand() % MAXN;
        ptmp2->next = NULL;
        ptmp1->next = ptmp2;
        ptmp2->prior = ptmp1;
        ptmp1 = ptmp2;
    }
    return head;
}

void destory(DuLNode *head)
{
    DuLNode *tmp = NULL;
    while(head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print(DuLinklist head)
{
    if(head == NULL)
    {
        puts("NULL");
        return ;
    }
    DuLNode *p;
    for(p=head->next; p!=NULL;p=p->next)
        printf("%d ",p->data);
    cout <<endl;
}

DuLinklist Partition(DuLinklist head, DuLinklist low, DuLinklist high)
{
    elemType pdata = low->data;
    while(low != high)
    {
        //from right to left
        while(low != high && high->data >= pdata)
            high = high->prior;
        swap(low->data, high->data);
        //from left to right 
        while(low != high && low->data <= pdata)
            low = low->next;
        swap(low->data, high->data);
    }
    return low;
}

void QSort(DuLinklist head,DuLinklist low,DuLinklist high)
{
    DuLNode *ptmp = NULL;
    ptmp = Partition(head, low, high);
    if(low != ptmp) QSort(head, low, ptmp->prior);
    if(high != ptmp) QSort(head,ptmp->next, high);
}

DuLinklist QuickSort(DuLinklist head)
{
    if(head == NULL || head->next == NULL) return head;
    DuLNode *temp = head->next;
    while(temp->next != NULL) temp = temp->next;
    DuLNode *high = temp;
    QSort(head,head->next,high);
    return head;
}

void BubbleSort(DuLNode *&head)
{
    if(head == NULL || head->next == NULL) return ;
    DuLinklist p = NULL, q = NULL, r = NULL;
    bool ok = false;
    p = head->next;
    while(p != r && !ok)
    {
        ok = true;
        q = p->next;
        while(q != r){
            if(p->data > q ->data ){
                p->prior->next = q;
                if(q->next != NULL) q->next->prior = p;
                p->next = q->next;
                q->prior = p->prior;
                q->next = p;
                p->prior = q;
                q = q->next;
                ok = false;
            } else {
                p = q;
                q = q->next;
            }
        }
        if(ok) break;
        print(head);
        p = head->next;
    }
    return ;
}

int main()
{
    int item;
    cout << "number of element: ";
    while(cin >> item)
    {
        DuLinklist head;
        // head=create();
        head = srandCreate(head, item);
        printf("Before sorted: ");
        print(head);
        //head = QuickSort(head);
        BubbleSort(head);
        printf("After sorted: ");
        print(head);
        destory(head);
        cout << "number of element: ";
    }
    return 0;
}
