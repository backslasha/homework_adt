#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

Poly InputAndGreatePoly(char syn);//从键盘接收系数和指数建立多项式A和B
void showCover();//显示封面菜单

int main()
{	Poly a,b,result,derA,derB;	float x;
	result.firstTerm=b.firstTerm=a.firstTerm=NULL;
	result.length=b.length=a.length=0;


	while(1){
		int i;
		showCover();
		scanf("%d",&i);
		switch(i){
			case 0://从键盘接收数字，建立两个poly
				system("cls");
				printf("请输入多项式 A :\n");
				a=InputAndGreatePoly('A');
				printf("\n请输入多项式 B :\n");
				b=InputAndGreatePoly('B');
				printf("\n任意键继续");
				while('\n'!=getchar());
				getchar();
				break;
			case 1://查看当前保存的两个poly:A和B的表达式，默认为0.
				system("cls");
				printf("多项式A和B:\n");
				printf("\n A(x) = ");
				PrintPoly(a);printf(".");
				printf("\n B(X) = ");
				PrintPoly(b);printf(".");

				derA=getDerivedPoly(a);
				derB=getDerivedPoly(b);
				printf("\n\n导函数:\n");
				printf("\n A`(x) = ");
				PrintPoly(derA);printf(".");
				printf("\n B`(X) = ");
				PrintPoly(derB);printf(".");

				printf("\n\n任意键继续");
				while('\n'!=getchar());
				getchar();
				break;
			case 2://多项式求值
			
				while(1)
				{
					char ch;
					printf("输入x的值(输入#退出):\n");
					scanf("%f",&x);
					printf("A(%.1f) = %.1f;\n",x,ValueForX(a,x));
					printf("B(%.1f) = %.1f;\n",x,ValueForX(b,x));

					while('\n'!=getchar());
					printf("输入任意字符继续,输入#返回主界面\n");	
					ch = getchar();
					if(ch=='#')
						break;
				}
				break;
			case 3://计算A+B的值放入result中,然后打印出表达式
				system("cls");
				InitPoly(&result);
				AddPoly(a,b,&result);
				printf("\n");
				printf("  A + B\n");						//  A + B 
				printf("= (");								//= (ax^b+bx^a) + (cx^d)
				PrintPoly(a);printf(") + (");PrintPoly(b);	//= ax^b+bx^a+cx^d.
				printf(")\n= ");							//
				PrintPoly(result);							//
				printf(".");								//
				printf("\n\n任意键继续");					//
				while('\n'!=getchar());

				getchar();
				break;
			case 4://计算A-B的值放入result中,然后打印出表达式
				system("cls");
				InitPoly(&result);
				SubPoly(a,b,&result);
				printf("\n");
				printf("  A - B\n");						//  A - B 
				printf("= (");								//= (ax^b+bx^a) + (cx^d)
				PrintPoly(a);printf(") - (");PrintPoly(b);	//= ax^b+bx^a+cx^d.
				printf(")\n= ");							//
				PrintPoly(result);							//
				printf(".");								//
				printf("\n\n任意键继续");					//
				while('\n'!=getchar());
				getchar();
				break;
			case 5://计算A*B的值放入result中,然后打印出表达式
				system("cls");
				InitPoly(&result);
				MulPoly(a,b,&result);
				printf("\n");
				printf("  A * B\n");						//  A * B 
				printf("= (");								//= (ax^b+bx^a) * (cx^d)
				PrintPoly(a);printf(") * (");PrintPoly(b);	//= ax^b+bx^a+cx^d.
				printf(")\n= ");							//
				PrintPoly(result);							//
				printf(".");								//
				printf("\n\n任意键继续");					//
				while('\n'!=getchar());
				getchar();
				break;
			case 6:
				exit(1);
			default:
				break;

		}
	
	}


}

Poly InputAndGreatePoly(char syn){
	Poly poly;int i;Term term;char c; 
    InitPoly(&poly);
	term.next=NULL;

	i=1;printf("(请输入项的系数和指数，系数和指数之间以空格隔开，项和项之间以逗号隔开)\n(某一项输入\".\"号结束输入)\n\"%c\":",syn);
    while(i)
    {   
        scanf("%f %d",&term.coef,&term.expn);
		//printf("accpet(%f,%d)\n",term.coef,term.expn);

		c = getchar();
	
		if(ERROR==InsertTerm(&poly,term))
			exit(1);

		if(c=='.'){
			printf("\n");
			break;
		}
    }
	printf("建立多项式  %c : ",syn);
    PrintPoly(poly);
	printf(".\n");
	return poly;
}

void showCover(){
	system("cls");
	printf("* * * * * * *一元稀疏多项式计算器* * * * * *\n");
	printf("*   您想干什么？(回复序号)\n");
	printf("*   0).(重新)输入两个多项式A,B;\n");
	printf("*   1).查看两个多项式A,B及其导函数;\n");
	printf("*   2).计算当x=?时多项式A和B的值\"A\",\"B\";\n");
	printf("*   3).计算A+B;\n");
	printf("*   4).计算A-B;\n");
	printf("*   5).计算A*B;\n");
	printf("*   6).退出.\n");
	printf("* * * * * * *一元稀疏多项式计算器* * * * * *\n");
}

