/**
F9������Ҫͣ�µĵط����öϵ�
F5�������
F10��������
F11���뺯��
**/
#include "poly.h"
#include<stdio.h>
#include<stdlib.h>
//������e��ǰn�����һԪϡ�����ʽP
Status InitPoly(Poly* Ptr)
{
    //Ptr = (Poly*)malloc(sizeof(Poly));
    if(Ptr==NULL)return OVERFLOW;
    Ptr->firstTerm=NULL;
    Ptr->length=0;
    return OK;
}
//Ѱ�Һ��ʵ�λ�ò���һ���ָ��С�ķ�ǰ�棬ָ����ͬ��ϲ���Ϊ0�򲻲���
Status InsertTerm(Poly *Ptr,Term term)
{	Term *termPtr;
    if(Ptr==NULL)return ERROR;


	termPtr = (Term*)malloc(sizeof(Term));
	(*termPtr)=term;

	 //���ϵ��Ϊ0�������
    if(term.expn==0)
    {
		return OK;
    }

	//����ǿյĶ���ʽ�����ΪfirstTerm�����������ָ����С�������ΪfirstTerm
    if(NULL==Ptr->firstTerm||term.expn < Ptr->firstTerm->expn)
    {	
		termPtr->next = Ptr->firstTerm;
        Ptr->firstTerm = termPtr;			

    }
    else
    {
        //Ѱ�Һ��ʵ�λ��
        Term *p ,*pre;
		p = Ptr->firstTerm;
		pre = NULL;

        while (  NULL!=p->next && term.expn > p->expn)//pָ��  ���һ��ʱ/�ҵ�ָ��<=������ʱ��ֹͣѭ��
        {
            pre = p;
            p = p->next;
        }
       //����ҵ�ָ����ȵ���ϲ�
         if(term.expn==p->expn)
        {printf("�ϲ�");
            //ָ�����
            p->coef+=term.coef;

            //���ϵ��Ϊ0��ɾ�����ͷŸýڵ�
            if(p->coef==0)
            {
				if(pre==NULL)Ptr->firstTerm=p->next;
				else
                pre->next=p->next;
				Ptr->length--;
                free(p);
            }

			return OK;
        }
		 //����ҵ�ָ��������ĵ���ʱ
        else if(term.expn<p->expn)
        {
printf("�����м�!");
			if(pre==NULL)Ptr->firstTerm=p->next;
			else
            pre->next=termPtr;
            termPtr->next=p->next;
			

        }
		 //����ǵ��������������
       else if(p->next==NULL)
        {
		   printf("����ĩβ!");
            p->next=termPtr;

	   }else{
			printf("������������!!");
			return ERROR;
	   }
    }
	
    Ptr->length++;
    return OK;
}
//����Poly
Status Destory(Poly* Ptr)
{
    Term *temp,*p;
    if(Ptr==NULL)return OK;
    else
    {
        p = Ptr->firstTerm;
        free(Ptr);
    }
    while(p!=NULL)
    {
        temp=p;
        p=p->next;
        free(temp);
    }
    free(p);
    return OK;
}

//��ӡ���Poly
Status PrintPoly(Poly poly)
{
    Term term;
    int i=0;
    printf("P(x)=");
	if(poly.firstTerm==NULL)
	{
		printf("0.\n");
		return OK;
	}else
		term=*poly.firstTerm;

    for(; ; i++)
    {       
        printf("%.0fx^%d",term.coef,term.expn);//���һ��
        if(i==poly.length-1||(term.next!=NULL&&term.next->coef<0)){//���û����һ�������һ���-�ţ������+��

		}else{
			printf("+");
		}
		if(term.next==NULL)break;//û����һ��ʱ����ѭ��
		term=*term.next;		
    }
    printf(".\n\n");
    return OK;
}

//����Poly����
int PolyLength(Poly P)
{
    return P.length;

}

//Poly�ļӷ�*resultPtr=Pa+Pb
void AddPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{

}

//Poly�ļ���*resultPtr=Pa-Pb
void SubPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{

}

//Poly�ĳ˷�*resultPtr=Pa*Pb
void MulPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{

}

//Poly�ĳ���*resultPtr=Pa/Pb
void DivPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{

}


