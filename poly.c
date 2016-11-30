/**
F9在你需要停下的地方设置断点
F5进入调试
F10单步运行
F11进入函数
**/
#include "poly.h"
#include<stdio.h>
#include<stdlib.h>
//由数组e的前n项构建的一元稀疏多项式P
Status InitPoly(Poly* Ptr)
{
    //Ptr = (Poly*)malloc(sizeof(Poly));
    if(Ptr==NULL)return OVERFLOW;
    Ptr->firstTerm=NULL;
    Ptr->length=0;
    return OK;
}
//寻找合适的位置插入一个项，指数小的放前面，指数相同则合并，为0则不插入
Status InsertTerm(Poly *Ptr,Term term)
{	Term *termPtr;
    if(Ptr==NULL)return ERROR;


	termPtr = (Term*)malloc(sizeof(Term));
	(*termPtr)=term;

	 //如果系数为0，不添加
    if(term.expn==0)
    {
		return OK;
    }

	//如果是空的多项式，添加为firstTerm；或者如果是指数最小，插入成为firstTerm
    if(NULL==Ptr->firstTerm||term.expn < Ptr->firstTerm->expn)
    {	
		termPtr->next = Ptr->firstTerm;
        Ptr->firstTerm = termPtr;			

    }
    else
    {
        //寻找合适的位置
        Term *p ,*pre;
		p = Ptr->firstTerm;
		pre = NULL;

        while (  NULL!=p->next && term.expn > p->expn)//p指向  最后一项时/找到指数<=它的项时，停止循环
        {
            pre = p;
            p = p->next;
        }
       //如果找到指数相等的则合并
         if(term.expn==p->expn)
        {printf("合并");
            //指数相加
            p->coef+=term.coef;

            //如果系数为0，删除并释放该节点
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
		 //如果找到指数比它大的的项时
        else if(term.expn<p->expn)
        {
printf("插入中间!");
			if(pre==NULL)Ptr->firstTerm=p->next;
			else
            pre->next=termPtr;
            termPtr->next=p->next;
			

        }
		 //如果是到了最后，则插在最后
       else if(p->next==NULL)
        {
		   printf("插入末尾!");
            p->next=termPtr;

	   }else{
			printf("插入项数出错!!");
			return ERROR;
	   }
    }
	
    Ptr->length++;
    return OK;
}
//销毁Poly
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

//打印输出Poly
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
        printf("%.0fx^%d",term.coef,term.expn);//输出一项
        if(i==poly.length-1||(term.next!=NULL&&term.next->coef<0)){//如果没有下一项或者下一项带-号，则不输出+号

		}else{
			printf("+");
		}
		if(term.next==NULL)break;//没有下一项时跳出循环
		term=*term.next;		
    }
    printf(".\n\n");
    return OK;
}

//返回Poly项数
int PolyLength(Poly P)
{
    return P.length;

}

//Poly的加法*resultPtr=Pa+Pb
void AddPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{

}

//Poly的减法*resultPtr=Pa-Pb
void SubPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{

}

//Poly的乘法*resultPtr=Pa*Pb
void MulPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{

}

//Poly的除法*resultPtr=Pa/Pb
void DivPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{

}


