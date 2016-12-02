#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;
typedef struct Term
{
    float coef;//系数
    int expn;//指数
    struct Term *next;//下一项

} Term; //项

typedef struct Poly
{
    Term *firstTerm;//存储空间首地址
    int length;//项数

} Poly; //一元稀疏多项式头结点

Status InitPoly(Poly *Ptr);                   //初始化一个一元稀疏多项式的头结点
Status InsertTerm(Poly *Ptr,Term term);       //寻找合适的位置插入一个项，指数相同则合并，为0则不插入
Status Destory(Poly *Ptr);                    //销毁Poly
Status PrintPoly(Poly P);                       //打印输出Poly
int PolyLength(Poly P);                         //返回Poly项数
void AddPoly(Poly Pa,Poly Pb,Poly *resultPtr);	//Poly的加法*resultPtr=Pa+Pb
void SubPoly(Poly Pa,Poly Pb,Poly *resultPtr);	//Poly的减法*resultPtr=Pa-Pb
void MulPoly(Poly Pa,Poly Pb,Poly *resultPtr);	//Poly的乘法*resultPtr=Pa*Pb
float ValueForX(Poly P,float x);				//求Poly在x下的值
Poly getDerivedPoly(Poly origin);				//求Poly的导函数



