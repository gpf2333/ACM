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
typedef char ElemType; //结点的值设置为字符
typedef struct CSNode
{
	ElemType data;
	struct CSNode *firstChild;  //第一个孩子
	struct CSNode *nextsbling;   //该孩子的第一个兄弟
}CSNode, *CSTree;

typedef CSTree QElemType;
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;  //队头指针
	QueuePtr rear;  //队尾指针
}LinkQueue;

Status InitQueue(LinkQueue &Q)//构造一个空队列
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));//队头结点
	if(!Q.front)
		exit(OVERFLOW);
	Q.front ->next = NULL;
	return OK;
}

Status QueueEmpty(const LinkQueue &Q)//若队列为空，则返回TRUE，否则返回FALSE
{
	if(Q.rear == Q.front)
		return TRUE;
	return FALSE;
}

Status EnQueue(LinkQueue &Q, QElemType e) //插入元素e为Q的新队尾元素
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

Status DeQueue(LinkQueue &Q,  QElemType &e) //若队列不空，则删除Q的队头元素，用e返回其值，并返回OK;
{
	if(Q.front == Q.rear)
	{
		return ERROR; //队空
	}
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return OK;
}

Status CreateTree(CSTree &T)  //创建一棵树
{

	LinkQueue Q;
	InitQueue(Q);//构造一个空队列
	char buffChild[20] ={       };  //用于存放孩子们的缓存
	memset(buffChild,0,20); //初始化缓存数组，置为NULL
	printf("请输入树的根结点（字符,以#代表空）:\n");
	scanf("%c",&buffChild[0]);
	if(buffChild[0] != '#')
	{

		T = (CSTree)malloc(sizeof(CSNode));//为根结点开辟一个空间
		if(!T)
			exit(OVERFLOW);  //开辟失败，终止程序
		T->data = buffChild[0];
		T->nextsbling = NULL;  //根结点无兄弟
		EnQueue(Q,T);  //根结点入队
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e); //结点出队
			//CSTree p = e; //用以指向队头结点
			printf("请按长幼顺序输入结点%c的孩子(输入的字符串以#结束):\n",e->data);
			scanf("%s",buffChild);
			if(buffChild[0] != '#')//有孩子
			{
					CSTree q;
					q = (CSTree)malloc(sizeof(CSNode));  //开辟孩子结点空间
				if(!q)
					exit(OVERFLOW);
					q->data = buffChild[0];  //
					e->firstChild = q;  //指向第一个孩子
					EnQueue(Q,q);  //第一个孩子入队
					CSTree p = q;  //指向刚入队的孩子
				for(size_t i = 1; i < strlen(buffChild)-1; ++i) //孩子存在兄弟
				{
					q = (CSTree)malloc(sizeof(CSNode));  //开辟孩子结点空间
					if(!q)
						exit(OVERFLOW);
					q->data = buffChild[i];
					p->nextsbling = q;
					EnQueue(Q,q);
					p = q;                     //指向刚入队的孩子
				}
				p->nextsbling = NULL;
			}
			else//无孩子
			{
				e->firstChild = NULL;
			}
		}
	}
	else
	{
		T = NULL;//空树
	}
	return OK;
}

void DestroyTree(CSTree &T)
{
	if(T)
	{
		if(T->firstChild)	//左子树存在，即销毁以长子为结点的子树
			DestroyTree(T->firstChild);
		if(T->nextsbling)	//右子树存在，即销毁以兄弟为结点的子树
			DestroyTree(T->nextsbling);
		free(T);
		T = NULL;
	}
}

void ClearTree(CSTree &T)
{

	DestroyTree(T);	//树T存在，将树T清为空树,
}

Status TreeEmpty(const CSTree &T)
{
	if(T)	//树T存在，空树返回TRUE，否则返回FALSE
		return TRUE;
	else
		return FALSE;
}

int TreeDepth(const CSTree &T)
{
	//树T存在，返回树的深度
	if(!T)//树空
	{
		return 0;
	}
	if(!T->firstChild)//无长子
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
	    return max+1;//当前层的下一层
}

ElemType Root(const CSTree &T)
// CSNode *Root(const CSTree &T)
{
	//树T存在，返回树的根
	if(T)
	  //return T;
		return T->data;
	return 0;
}

CSNode *FindNode(const CSTree &T,ElemType cur_e)
{
	//树T存在，返回值为cur_e的结点的指针
	LinkQueue Q;
	InitQueue(Q);  //构造一个空队列
	if(T)
	{
		EnQueue(Q,T);//树根入队
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e);
			if(e->data == cur_e)
				return e;
			if(e->firstChild) //当前结点有长子，则该长子入队
			{
				EnQueue(Q,e->firstChild);
			}
			if(e->nextsbling)//当前结点有兄弟,则该兄弟入队
			{
				EnQueue(Q,e->nextsbling);
			}
		}
	}
	return NULL;
}

CSNode *Parent(CSTree &T,ElemType cur_e)
{
	//初始条件：树T存在，cur_e是T中某个结点
	//操作结果：若cur_e是T的非根结点，则返回它的双亲，否则返回空
	LinkQueue Q;
	InitQueue(Q);
	if(T)
	{
		if(T->data == cur_e)
			return NULL;//根结点无双亲,结束，返回NULL
		EnQueue(Q,T);//根结点入队
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e);
			QElemType p = e;//提示刚出队的元素；
			if(e->firstChild)//该结点有孩子
			{
				if(e->firstChild->data == cur_e)//或该孩子是所求的结点，则返回双亲
				{
					return p;
				}
				EnQueue(Q,e->firstChild);
				QElemType brotherPtr = e->firstChild->nextsbling;//指向孩子的兄弟结点
				while(brotherPtr) //该孩子有兄弟
				{
					if(brotherPtr->data == cur_e)//兄弟是所求的结点，则返回双亲
					{
						return p;
					}
					EnQueue(Q,brotherPtr);//兄弟入队
					brotherPtr = brotherPtr->nextsbling;
				}
			}
		}
	}
	return NULL;
}

ElemType LeftChild(CSTree &T, ElemType cur_e)
{
	//初始条件：树T存在，cur_e是T中某个结点
	//操作结果：若cur_e是T的非叶子结点，则返回它的最左孩子，否则返回空
	CSNode *node;
	node = FindNode(T,cur_e);
	if(node)
	{
		if(node->firstChild)//非叶子结点
		{
			return node->firstChild->data; //返回结点的值
		}
	}
	return '\0';
}

ElemType RightSibling(CSTree &T, ElemType cur_e)
{
	//初始条件：树T存在，cur_e是T中的某个结点。
	//操作结果：若cur_e有右兄弟，则返回它的右兄弟，否则返回空
	CSNode *node;
	node = FindNode(T,cur_e);
	if(node)
	{
		if(node->nextsbling)//有右兄弟
		{
			return node->nextsbling->data;//返回右兄弟的值
		}
	}
	return '\0';
}

Status LevelOrderTraverse(const CSTree &T)
{
	//层序遍历树
	LinkQueue Q;
	InitQueue(Q);
	if(T)
	{
		printf("%c ",T->data);     //访问结点
		EnQueue(Q,T);             //根结点排队
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
	if(p == NULL)   return 1; //长子不存在返回1
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
	InitQueue(Q);//构造一个空队列
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
	if(!T)  return 0; //树根为空
	CSTree p = T->firstChild;
	if(!p)  return 1; //
	//有长子
	for( ; p!=NULL; p=p->nextsbling) //寻找兄弟中度最大的
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
	printf("LevelOrder tree：");
	LevelOrderTraverse(T);
	puts("");
	printf("deepth(dfs) ： %d\n",dfs_GetDepth(T));
	printf("deepth(bfs)：%d\n",bfs_GetDepth(T));
	printf("(degree of tree)： %d\n",Get_Degree(T));
	return 0;
}



