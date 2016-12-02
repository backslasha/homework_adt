/**
F9在你需要停下的地方设置断点
F5进入调试
F10单步运行
F11进入函数
**/
#include "poly.h"
#include<stdio.h>
#include<stdlib.h>

float pow(float x,int i){
	float count = x;
	int j;
	if(i==0)return 1;
	if(i>0){
		for(j=2;j<=i;j++){
			count = count * x;
		}
		return count;
	}
	else {
		i=-i;
		for(j=2;j<=i;j++){
			count = count * x;
		}
		count=1/count;
		return count;
	}
}


//重置一元稀疏多项式P
Status InitPoly(Poly* Ptr)
{
//	Term *termPtr,*temp;
	if(Ptr==NULL)return ERROR;

/*	if(Ptr->firstTerm!=NULL)//未初始化！=NULL
	{
		termPtr = Ptr->firstTerm;
		while(termPtr!=NULL)
		{
			temp=termPtr;
			termPtr = termPtr->next;
			free(temp);
		}
	}*/
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

	//确保term的next的地址不会被保留，否则会发生意外的bug
	{	if(termPtr->next!=NULL)
		termPtr->next=NULL;
	}

	 //如果系数为0，不添加
    if(term.coef==0)
    {																//	printf("系数为0不添加!:%d\n",PolyLength(*Ptr));
		return OK;
    }

	//如果是空的多项式，添加为firstTerm；或者如果是指数最小，插入成为firstTerm
    if(NULL==Ptr->firstTerm||term.expn < Ptr->firstTerm->expn)
    {																	
		termPtr->next = Ptr->firstTerm;
        Ptr->firstTerm = termPtr;				
																	//	printf("插入成为首项!:%d\n",PolyLength(*Ptr));
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
        {																
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
																		//	printf("合并一项:%d\n",PolyLength(*Ptr));
			return OK;
        }
		 //如果找到指数比它大的的项时
        else if(term.expn<p->expn)
        {
																		
			if(pre==NULL)Ptr->firstTerm=p->next;
			else
            pre->next=termPtr;
            termPtr->next=p;
																		//	printf("插入中间一项!:%d\n",PolyLength(*Ptr));

        }
		 //如果是到了最后，则插在最后
       else if(p->next==NULL)
        {
																		
            p->next=termPtr;
																	//		printf("插入末尾一项!:%d\n",PolyLength(*Ptr));
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

//打印输出Poly的裸数据
Status PrintPoly(Poly poly)
{
    Term term;
    int i=1;
	if(poly.firstTerm==NULL)
	{
		printf("0");
		return OK;
	}else
		term=*poly.firstTerm;

    while(i++)
    {   
		//输入系数
		if(term.coef==1)
		{
			printf("");
		}
		else if(term.coef==-1)
		{
			printf("-");
		}
		else 
		{
			printf("%.1f",term.coef);
		}

		//输入x
		if(term.expn==0)
		{
			printf("");
		}
		else 
		{
			printf("x");
        }
		
		//输入指数
		if(term.expn==0||term.expn==1)
		{
			printf("");
        }
		else 
		{
			printf("^%d",term.expn);
        }

		//输入加号
		if(term.next==NULL||(term.next!=NULL&&term.next->coef<0))//如果没有下一项或者下一项带-号，则不输出+号
		{
			printf("");
		}
		else
		{
			printf("+");
		}
		if(term.next==NULL)break;//没有下一项时跳出循环
		term=*term.next;		
    }
    //printf(".");
    return OK;
}

//返回Poly项数
int PolyLength(Poly P)
{
    Term *termPtr;int i=0;
	if(P.firstTerm==NULL)return 0;
	else 
	{
		termPtr=P.firstTerm;
		while(termPtr!=NULL)
		{
			i++;
			termPtr=termPtr->next;
		}
	}
	return i;
}

//Poly的加法*resultPtr=Pa+Pb
void AddPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{
	Term *PaPtr,*PbPtr;

	//保证传进来的poly已经初始化
	{	resultPtr->length=0;
		resultPtr->firstTerm=NULL;
	}

	PaPtr = Pa.firstTerm;
	PbPtr = Pb.firstTerm;
	
	while(PaPtr!=NULL)
	{
		InsertTerm(resultPtr,*PaPtr);
		PaPtr = PaPtr->next;
	}
	while(PbPtr!=NULL) 
	{
		InsertTerm(resultPtr,*PbPtr);
		PbPtr = PbPtr->next;
	}
}

//Poly的减法*resultPtr=Pa-Pb
void SubPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{

	Term *PbPtr;
	PbPtr=Pb.firstTerm;
	while(PbPtr!=NULL)
	{
		PbPtr->coef=-PbPtr->coef;
		PbPtr=PbPtr->next;
	}
	AddPoly(Pa,Pb,resultPtr);
	PbPtr=Pb.firstTerm;
	while(PbPtr!=NULL)
	{
		PbPtr->coef=-PbPtr->coef;
		PbPtr=PbPtr->next;
	}
}

//Poly的乘法*resultPtr=Pa*Pb
void MulPoly(Poly Pa,Poly Pb,Poly* resultPtr)
{
	Term *PaPtr,*PbPtr,temp;

	//保证传进来的poly已经初始化
	{	resultPtr->length=0;
		resultPtr->firstTerm=NULL;
	}

	PaPtr = Pa.firstTerm;
	PbPtr = Pb.firstTerm;

	if(PaPtr==NULL||PbPtr==NULL)
	{
		return;
	}

	temp.next=NULL;
	while(PaPtr!=NULL)
	{
		if(PbPtr==NULL)
		{
			PaPtr=PaPtr->next;
			PbPtr=Pb.firstTerm;
			continue;
		}else
		{
			temp.coef=PaPtr->coef*PbPtr->coef;
			temp.expn=PaPtr->expn+PbPtr->expn;
			InsertTerm(resultPtr,temp);
			PbPtr=PbPtr->next;
		}
	}

}


//求Poly在x下的值
float ValueForX(Poly P,float x)
{
	Term *termPtr;
	float value = 0;
	if(P.firstTerm==NULL||P.length==0)
	{
		return 0;
	}
	else
	{	
		termPtr=P.firstTerm;
		while(termPtr!=NULL)
		{
			value+=termPtr->coef*pow(x,termPtr->expn);
			termPtr=termPtr->next;
		}
	}
	return value;
}

//求Poly的导函数
Poly getDerivedPoly(Poly origin)
{
	Poly derived;
	Term term,*termPtr;

	derived.firstTerm=NULL;
	derived.length=0;

	if(origin.firstTerm==NULL||origin.length==0)
		return derived;
	else 
	{
		term.next=NULL;
		termPtr=origin.firstTerm;
		while(termPtr!=NULL)
		{
			term.coef=termPtr->coef*termPtr->expn;
			term.expn=termPtr->expn-1;
			InsertTerm(&derived,term);
			termPtr=termPtr->next;
		}
	}
	return derived;
}


