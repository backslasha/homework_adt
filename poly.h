#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;
typedef struct Term
{
    float coef;//ϵ��
    int expn;//ָ��
    struct Term *next;//��һ��

} Term; //��

typedef struct Poly
{
    Term *firstTerm;//�洢�ռ��׵�ַ
    int length;//����

} Poly; //һԪϡ�����ʽͷ���

Status InitPoly(Poly *Ptr);                   //��ʼ��һ��һԪϡ�����ʽ��ͷ���
Status InsertTerm(Poly *Ptr,Term term);       //Ѱ�Һ��ʵ�λ�ò���һ���ָ����ͬ��ϲ���Ϊ0�򲻲���
Status Destory(Poly *Ptr);                    //����Poly
Status PrintPoly(Poly P);                       //��ӡ���Poly
int PolyLength(Poly P);                         //����Poly����
void AddPoly(Poly Pa,Poly Pb,Poly *resultPtr);//Poly�ļӷ�*resultPtr=Pa+Pb
void SubPoly(Poly Pa,Poly Pb,Poly *resultPtr);//Poly�ļ���*resultPtr=Pa-Pb
void MulPoly(Poly Pa,Poly Pb,Poly *resultPtr);//Poly�ĳ˷�*resultPtr=Pa*Pb
void DivPoly(Poly Pa,Poly Pb,Poly *resultPtr);//Poly�ĳ���*resultPtr=Pa/Pb



