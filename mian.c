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
        printf("�������%d���ϵ����ָ�����Կո����\n����\"0,0\"�Ž�������\n:",i);
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
