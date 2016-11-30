#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

int main()
{

    Poly poly;int i;Term term; 
    InitPoly(&poly);
	term.next=NULL;

    for(i=1; i; i++)
    {   
        printf("请输入第%d项的系数和指数，以空格隔开\n输入\"0,0\"号结束输入\n:",i);
        scanf("%f %d",&term.coef,&term.expn);
		printf("accpet(%f,%d)\n",term.coef,term.expn);
        if(term.coef==0&&term.expn==0)
        {
            printf("\n");
            break;
        }
		while(getchar()!='\n');
        if(ERROR==InsertTerm(&poly,term))
			return -1;
    }
    PrintPoly(poly);


}
