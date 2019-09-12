#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define OVERFLOW -2
using namespace std;
typedef int Status;
typedef char ElemType; //����ֵ����Ϊ�ַ�
typedef struct CSNode
{
	ElemType data;
	struct CSNode *firstChild;  //��һ������
	struct CSNode *nextsbling;   //�ú��ӵĵ�һ���ֵ�
}CSNode, *CSTree;

typedef CSTree QElemType;
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;  //��ͷָ��
	QueuePtr rear;  //��βָ��
}LinkQueue;

Status InitQueue(LinkQueue &Q)//����һ���ն���
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));//��ͷ���
	if(!Q.front)
		exit(OVERFLOW);
	Q.front ->next = NULL;
	return OK;
}

Status QueueEmpty(const LinkQueue &Q)//������Ϊ�գ��򷵻�TRUE�����򷵻�FALSE
{
	if(Q.rear == Q.front)
		return TRUE;
	return FALSE;
}

Status EnQueue(LinkQueue &Q, QElemType e) //����Ԫ��eΪQ���¶�βԪ��
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

Status DeQueue(LinkQueue &Q,  QElemType &e) //�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK;
{
	if(Q.front == Q.rear)
	{
		return ERROR; //�ӿ�
	}
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return OK;
}

Status CreateTree(CSTree &T)  //����һ����
{

	LinkQueue Q;
	InitQueue(Q);//����һ���ն���
	char buffChild[20] ={       };  //���ڴ�ź����ǵĻ���
	memset(buffChild,0,20); //��ʼ���������飬��ΪNULL
	printf("���������ĸ���㣨�ַ�,��#����գ�:\n");
	scanf("%c",&buffChild[0]);
	if(buffChild[0] != '#')
	{

		T = (CSTree)malloc(sizeof(CSNode));//Ϊ����㿪��һ���ռ�
		if(!T)
			exit(OVERFLOW);  //����ʧ�ܣ���ֹ����
		T->data = buffChild[0];
		T->nextsbling = NULL;  //��������ֵ�
		EnQueue(Q,T);  //��������
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e); //������
			//CSTree p = e; //����ָ���ͷ���
			printf("�밴����˳��������%c�ĺ���(������ַ�����#����):\n",e->data);
			scanf("%s",buffChild);
			if(buffChild[0] != '#')//�к���
			{
					CSTree q;
					q = (CSTree)malloc(sizeof(CSNode));  //���ٺ��ӽ��ռ�
				if(!q)
					exit(OVERFLOW);
					q->data = buffChild[0];  //
					e->firstChild = q;  //ָ���һ������
					EnQueue(Q,q);  //��һ���������
					CSTree p = q;  //ָ�����ӵĺ���
				for(size_t i = 1; i < strlen(buffChild)-1; ++i) //���Ӵ����ֵ�
				{
					q = (CSTree)malloc(sizeof(CSNode));  //���ٺ��ӽ��ռ�
					if(!q)
						exit(OVERFLOW);
					q->data = buffChild[i];
					p->nextsbling = q;
					EnQueue(Q,q);
					p = q;                     //ָ�����ӵĺ���
				}
				p->nextsbling = NULL;
			}
			else//�޺���
			{
				e->firstChild = NULL;
			}
		}
	}
	else
	{
		T = NULL;//����
	}
	return OK;
}

void DestroyTree(CSTree &T)
{
	if(T)
	{
		if(T->firstChild)	//���������ڣ��������Գ���Ϊ��������
			DestroyTree(T->firstChild);
		if(T->nextsbling)	//���������ڣ����������ֵ�Ϊ��������
			DestroyTree(T->nextsbling);
		free(T);
		T = NULL;
	}
}

void ClearTree(CSTree &T)
{

	DestroyTree(T);	//��T���ڣ�����T��Ϊ����,
}

Status TreeEmpty(const CSTree &T)
{
	if(T)	//��T���ڣ���������TRUE�����򷵻�FALSE
		return TRUE;
	else
		return FALSE;
}

int TreeDepth(const CSTree &T)
{
	//��T���ڣ������������
	if(!T)//����
	{
		return 0;
	}
	if(!T->firstChild)//�޳���
	{
		return 1;
	}
	CSTree p;
	int depth,max = 0;
	for(p = T->firstChild; p; )
	{
	 	depth = TreeDepth(p);
		if(depth > max)
			max = depth;
		    p = p->nextsbling;
	}
	    return max+1;//��ǰ�����һ��
}

ElemType Root(const CSTree &T)
// CSNode *Root(const CSTree &T)
{
	//��T���ڣ��������ĸ�
	if(T)
	  //return T;
		return T->data;
	return 0;
}

CSNode *FindNode(const CSTree &T,ElemType cur_e)
{
	//��T���ڣ�����ֵΪcur_e�Ľ���ָ��
	LinkQueue Q;
	InitQueue(Q);  //����һ���ն���
	if(T)
	{
		EnQueue(Q,T);//�������
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e);
			if(e->data == cur_e)
				return e;
			if(e->firstChild) //��ǰ����г��ӣ���ó������
			{
				EnQueue(Q,e->firstChild);
			}
			if(e->nextsbling)//��ǰ������ֵ�,����ֵ����
			{
				EnQueue(Q,e->nextsbling);
			}
		}
	}
	return NULL;
}

CSNode *Parent(CSTree &T,ElemType cur_e)
{
	//��ʼ��������T���ڣ�cur_e��T��ĳ�����
	//�����������cur_e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻ؿ�
	LinkQueue Q;
	InitQueue(Q);
	if(T)
	{
		if(T->data == cur_e)
			return NULL;//�������˫��,����������NULL
		EnQueue(Q,T);//��������
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e);
			QElemType p = e;//��ʾ�ճ��ӵ�Ԫ�أ�
			if(e->firstChild)//�ý���к���
			{
				if(e->firstChild->data == cur_e)//��ú���������Ľ�㣬�򷵻�˫��
				{
					return p;
				}
				EnQueue(Q,e->firstChild);
				QElemType brotherPtr = e->firstChild->nextsbling;//ָ���ӵ��ֵܽ��
				while(brotherPtr) //�ú������ֵ�
				{
					if(brotherPtr->data == cur_e)//�ֵ�������Ľ�㣬�򷵻�˫��
					{
						return p;
					}
					EnQueue(Q,brotherPtr);//�ֵ����
					brotherPtr = brotherPtr->nextsbling;
				}
			}
		}
	}
	return NULL;
}

ElemType LeftChild(CSTree &T, ElemType cur_e)
{
	//��ʼ��������T���ڣ�cur_e��T��ĳ�����
	//�����������cur_e��T�ķ�Ҷ�ӽ�㣬�򷵻����������ӣ����򷵻ؿ�
	CSNode *node;
	node = FindNode(T,cur_e);
	if(node)
	{
		if(node->firstChild)//��Ҷ�ӽ��
		{
			return node->firstChild->data; //���ؽ���ֵ
		}
	}
	return '\0';
}

ElemType RightSibling(CSTree &T, ElemType cur_e)
{
	//��ʼ��������T���ڣ�cur_e��T�е�ĳ����㡣
	//�����������cur_e�����ֵܣ��򷵻��������ֵܣ����򷵻ؿ�
	CSNode *node;
	node = FindNode(T,cur_e);
	if(node)
	{
		if(node->nextsbling)//�����ֵ�
		{
			return node->nextsbling->data;//�������ֵܵ�ֵ
		}
	}
	return '\0';
}

Status LevelOrderTraverse(const CSTree &T)
{
	//���������
	LinkQueue Q;
	InitQueue(Q);
	if(T)
	{
		printf("%c ",T->data);     //���ʽ��
		EnQueue(Q,T);             //������Ŷ�
		while(!QueueEmpty(Q))
		{
			QElemType e,p;
			DeQueue(Q,e);
			p = e->firstChild;
			while(p)
			{
				printf("%c ",p->data);
				EnQueue(Q,p);
				p = p->nextsbling;
			}
		}
		return OK;
	}
	return ERROR;
}

int dfs_GetDepth(const CSTree &T)
{
	if(T == NULL)   return 0;
	CSTree p = T->firstChild;
	if(p == NULL)   return 1; //���Ӳ����ڷ���1
	int h, maxx = 0;
	while(p!= NULL)
	{
        h = dfs_GetDepth(p);
        maxx = (maxx > h ) ? maxx : h;
	    p = p->nextsbling;
	}
	return maxx + 1;
}

int bfs_GetDepth(const CSTree &T)
{
    if(!T) return 0;
    LinkQueue Q;
	InitQueue(Q);//����һ���ն���
	EnQueue(Q, T);
	QElemType e;
	int h = 0, w = 1;
	while(!QueueEmpty(Q))
    {
        ++h;
        int tmp = 0;
        for(int i = 0; i < w; ++i)
        {
            DeQueue(Q, e);
            e = e->firstChild;
            while(e != NULL)
            {
                EnQueue(Q, e);
                e = e->nextsbling;
                ++tmp;
            }
        }
        w = tmp;
    }
    return h;
}

int Get_Degree(const CSTree T)
{
	int d = 0, maxx = 0;
	if(!T)  return 0; //����Ϊ��
	CSTree p = T->firstChild;
	if(!p)  return 1; //
	//�г���
	for( ; p!=NULL; p=p->nextsbling) //Ѱ���ֵ��ж�����
	{
	   d++;
	   int d_sub = Get_Degree(p);
	   maxx = (maxx > d_sub) ? maxx : d_sub;
	}
	return  ((maxx > d) ? maxx : d);
}

int main()
{
	CSTree T;
	CreateTree(T);
	printf("LevelOrder tree��");
	LevelOrderTraverse(T);
	puts("");
	printf("deepth(dfs) �� %d\n",dfs_GetDepth(T));
	printf("deepth(bfs)��%d\n",bfs_GetDepth(T));
	printf("(degree of tree)�� %d\n",Get_Degree(T));
	return 0;
}



