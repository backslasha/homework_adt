#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define TRUE 2
#define FALSE 3

typedef int Status;
typedef char TElemType;
//二叉树的结构
typedef struct BiTNode
{
    int level;
    TElemType data;			//数据域
    struct BiTNode *lchild,*rchild;	//左、右孩子指针
} BiTNode,*BiTree;

//基本接口函数
void InitBiTree(BiTree &T);		//创建一棵空的二叉树
BiTree MakeBiTree(TElemType e,BiTree L,BiTree R);	//创建一个二叉树T，其根节点值为e，L和R为左右子树
void DestoryBiTree(BiTree &T);	//释放一棵二叉树的所有节点指针
Status BiTreeEmpty(BiTree T);	//判断一棵二叉树是否为空二叉树
Status BreakBiTree(BiTree &T,BiTree &L,BiTree &R);	//将一棵二叉树分解为根、左子树和右子树三个部分
Status ReplaceLeft(BiTree &T,BiTree &LT);			//替换左子树，若树为空，返回ERROR，否则用LT替换T的左子树，LT返回T的原左子树
Status ReplaceLeft(BiTree &T,BiTree &LT);			//替换左子树，若树为空，返回ERROR，否则用LT替换T的右子树，LT返回T的原右子树
void PreOrderTraverse(BiTree T);					//递归先序遍历二叉树
int BiTreeDepth(BiTree T);							//求一棵二叉树的深度
void CountLeaf(BiTree T,int &count);							//求一棵二叉树的叶子节点数
BiTree CreateBiTreeByString(char *defBT,int &i,int level);				//给出指定的字符串，基于先序遍历，建立一个二叉树，其中defBT是字符数组，i是下标，初始为0，level是初始层数为1


/***************测试用队列接口*******************/
typedef BiTree ElemType;
typedef struct LQNode
{
    ElemType e;
    struct LQNode *next;
} LQNOde,*QueuePtr;

typedef struct
{
    QueuePtr _front;
    QueuePtr _rear;
} LQueue;

void InitQueue(LQueue &L)
{
    L._front=NULL;
    L._rear=NULL;
}

Status QueueEmpty(LQueue L)
{
    if(L._front==NULL)return TRUE;
    return FALSE;
}

Status EnQueue(LQueue &L,ElemType e)
{
    QueuePtr p = NULL;
    p = (QueuePtr)malloc(sizeof(LQNode));
    if(NULL==p)return ERROR;
    p->e=e;
    p->next=NULL;
    if(NULL==L._front)
        L._front=p;
    else
        L._rear->next=p;

    L._rear=p;
    return TRUE;
}

Status DeQueue(LQueue &L,ElemType &e)
{
    if(NULL==L._front)return ERROR;
    QueuePtr L_copy = L._front;

    e =  L._front->e;
    L._front = L._front->next;

    free(L_copy);
}

//根据二叉树节点的level打印data
void printTNodeByLevel(BiTree T,int &preH)
{
    if(T->level > preH)
    {
        printf("\n");
        preH = T->level;
    }
    printf("\"%c\" ",T->data);
}
//借助队列的层序遍历二叉树
void LevelOrderTraverse(BiTree T)
{
    LQueue Q;
    InitQueue(Q);

    if(NULL==T)return;
    EnQueue(Q,T);

    int d=1;
    while(QueueEmpty(Q)==FALSE)
    {
        DeQueue(Q,T);

        printTNodeByLevel(T,d);

        if(T->lchild!=NULL)EnQueue(Q,T->lchild);
        if(T->rchild!=NULL)EnQueue(Q,T->rchild);
    }
}


//测试
int main()
{
    printf("tab the string : \n");
    char defBT[100];
    {//从键盘接收字符串
        char ch;
        int i=0;
        while(TRUE)
        {
            scanf("%c",&ch);
            defBT[i++] = ch;
            if(ch=='\n')break;
        }
    }


    //创建二叉树
    int index = 0;
    BiTree T = CreateBiTreeByString(defBT,index,1);

    //层数遍历从根节点出发从上到下输出二叉树
    printf("创建二叉树成功！层数结构为 : \n\n");
    LevelOrderTraverse(T);
    printf("\n\n");


    printf("二叉树深度为: %d \n\n",BiTreeDepth(T));

    int count = 0;
    CountLeaf(T,count);
    printf("二叉树叶子总数为 :%d \n\n",count);


    printf("将二叉树分解为三子树:\n\n");
    BiTree root=T,R,L;
    BreakBiTree(root,L,R);

    printf("根树：\n");
    LevelOrderTraverse(root);
    printf("\n\n");

    printf("左树：\n");
    LevelOrderTraverse(L);
    printf("\n\n");

    printf("右树：\n");
    LevelOrderTraverse(R);
    printf("\n\n");

    return 0;
}






//接口函数定义：

void InitBiTree(BiTree &T)
{
    T=NULL;
}
BiTree MakeBiTree(TElemType e,BiTree L,BiTree R,int level)
{
    BiTree T;
    T = (BiTree)malloc(sizeof(BiTNode));
    if(NULL==T)return NULL;
    T->data = e;
    T->level=level;
    T->lchild = L;
    T->rchild = R;
    return T;
}
void DestoryBiTree(BiTree &T)
{
    if(T!=NULL)
    {
        DestoryBiTree(T->lchild);
        DestoryBiTree(T->rchild);
        free(T);
    }
}
Status BiTreeEmpty(BiTree T)
{
    if(NULL==T)return TRUE;
    return FALSE;
}
Status BreakBiTree(BiTree &T,BiTree &L,BiTree &R)
{
    if(NULL==T)return ERROR;
    L=T->lchild;
    R=T->rchild;
    T->lchild=NULL;
    T->rchild=NULL;
    return OK;
}
Status ReplaceLeft(BiTree &T,BiTree &LT)
{
    if(NULL==T)return ERROR;
    BiTree temp = T->lchild;
    T->lchild=LT;
    LT =temp;
    return OK;
}
Status ReplaceRight(BiTree &T,BiTree &RT)
{
    if(NULL==T)return ERROR;
    BiTree temp = T->rchild;
    T->rchild=RT;
    RT =temp;
    return OK;
}
void PreOrderTraverse(BiTree T)
{
    if(NULL==T)
    {
        printf("#\n");
        return;
    }

    PreOrderTraverse(T->lchild);
    printf("%c\n",T->data);
    PreOrderTraverse(T->rchild);
}

int BiTreeDepth(BiTree T)
{
    if(NULL==T)return 0;
    int li,ri;
    li = BiTreeDepth(T->lchild);
    ri = BiTreeDepth(T->rchild);
    return 1+(li>ri?li:ri);
}

void CountLeaf(BiTree T,int &leafcount)
{
    if(NULL!=T)
    {
        if(NULL==T->rchild&&NULL==T->lchild) leafcount++;
        CountLeaf(T->rchild,leafcount);
        CountLeaf(T->lchild,leafcount);
    }
}

BiTree CreateBiTreeByString(char *defBT,int &i,int level)
{
    BiTree T;
    char ch = defBT[i++];
    if('#'==ch) InitBiTree(T);
    else
    {
        T = MakeBiTree(ch,NULL,NULL,level);
        T->lchild = CreateBiTreeByString(defBT,i,level+1);
        T->rchild = CreateBiTreeByString(defBT,i,level+1);
    }
    return T;
}

