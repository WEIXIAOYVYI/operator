#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

int i=0,top=0;
char opg[5000]={'#'},endlist[10]={'+','*','i','(',')','#'};
FILE * in;
char c,topend='#';
char cmp[10][10]={{1,3,3,3,1,1},{1,1,3,3,1,1},{1,1,-1,-1,1,1},{3,3,3,3,2,-1},{1,1,-1,-1,1,1},{3,3,3,3,-1,-1}};
int check(char a){
	int len=strlen(endlist);
	for(i=0;i<len;i++){
		if(a==endlist[i])
			return i;
	}
	return -1;
}
void push(char a){
	//topend=a;
	opg[++top]=a;
}
void findtop(){
	for(i=top;i>=0;i--){
		if(opg[i]!='N'){
			topend=opg[i];
			break;
		}
	}
}
char pop(){
	if(top>=1)
		return opg[top--];
	return -1;
}
int merge(){
	char a=pop(),b=-1,c=-1;
	if(a==-1)
		return 0;
	if(a=='i'){
		//printf("2\n");
		findtop();
		//printf("3\n");
		push('N');
		return 1;
	}
	else if(a==')'){
		b=pop();c=pop();
		if(b=='N'&&c=='('){
			findtop();
			push('N');
			return 1;
		}
		else return 0;
	}
	else if(a=='N'){
		b=pop();c=pop();
		if(b=='+'&&c=='N'){
			findtop();
			push('N');
			return 1;
		}
		else if(b=='*'&&c=='N'){
			findtop();
			push('N');
			return 1;
		}
		else if(b==-1&&c==-1){
			return 2;
		}
		else return 0;
	}
	else return 0; 
}
int main(int argc,char *argv[]){
	in=fopen(argv[1],"r");	
	c=fgetc(in);
	while(c!=EOF){
		if(c=='\n'){
			c='#';	
		}
			
		int tmp1=-1,tp=-1,tmp2=-1;
		if((tmp1=check(topend))==-1||(tmp2=check(c))==-1||((top!=1||opg[top]!='N')&&cmp[tmp1][tmp2]==-1)){
			printf("E\n");
			break;
		}	
		tp=cmp[tmp1][tmp2];
		if(tp==1){
			//规约
			int n=merge();	//printf("n=%d\n",n);
			if(n==0){
				printf("RE\n");
				break;
			}			
			else if(n==1)
				printf("R\n");
			else if(n==2)
				break;//printf("hh%c\n",c);
		}
		else if(tp==2||tp==3){
			//移进 
			topend=c;
			push(c);
			printf("I%c\n",c);c=fgetc(in);
		}
		else{
			break;
		} 
	}

	return 0;
}
