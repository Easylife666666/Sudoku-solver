#include <stdio.h>
#include <string.h>
int a[9][9]={
{0,0,9,0,0,3,1,5,0},
{0,5,0,0,0,0,0,3,4},
{0,1,0,4,0,2,0,0,0},
{0,0,1,2,0,0,0,0,7},
{0,0,4,0,1,0,5,0,0},
{9,0,0,0,0,7,6,0,0},
{0,0,0,1,0,4,0,8,0},
{1,8,0,0,0,0,0,6,0},
{0,4,3,6,0,0,7,0,0}
},b[9][9],aBk[9][9];
int Stack[9][9][9]={},StackBk[9][9][9]={};

int Check(int* SubStack,int* rpt,int r){
	int cnt=0,i;
	for(i=0;i<r;i++){
		if(SubStack[rpt[i]])
			cnt++;
	}
	return (cnt==r||!cnt)?1:0;
}
void Keep(int* SubStack,int* rpt,int r){
	int cnt=0,i,j;
	for(i=0;i<r;i++){
		if(SubStack[rpt[i]])
			cnt++;
	}
	if(cnt==r){
		for(i=0;i<9;i++){
			int flag=1;
			for(j=0;j<r;j++){
				if(i==rpt[j])
					flag=0;
			}
			if(flag)
				SubStack[i]=0;
		}
	}
	return;
}
int exists(int Ii,int Ij,int Ik){
	int flag=0,i,j;
	//R
	for(i=0;i<9;i++){
		if(a[i][Ij]==Ik)
			flag=1;
	}
	//C
	for(j=0;j<9;j++){
		if(a[Ii][j]==Ik)
			flag=1;
	}
	//S
	for(i=Ii/3*3;i<(Ii/3+1)*3;i++){
		for(j=Ij/3*3;j<(Ij/3+1)*3;j++){
			if(a[i][j]==Ik)
				flag=1;
		}
	}
	return flag;
}
int fill(int input1,int input2,int input3){
	if(a[input1][input2])
		return 0;
	b[input1][input2]=input3;
	return 1;
}

int main1(){
	int Changed=0,i,j,k,r,I,J;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(a[i][j])
				printf("%11d",a[i][j]);
			else{
				char cb[10]={};
				cb[9]='\0';
				for(k=1;k<10;k++){
					if(!exists(i,j,k)){
						cb[k-1]=k+'0';
						Stack[i][j][k-1]=k;
					}
					else
						cb[k-1]=' ';
				}
				printf("[%s]",cb);
			}
		}
		printf("\n");
	}
	/*
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			int cnt=0;
			for(int k=0;k<9;k++){
				if(Stack[i][j][k])
					cnt++;
			}
			if(cnt==1){
				//printf("Place%d:%dSpecial\n",i,j);
				int where;
				for(int k=0;k<9;k++){
					if(Stack[i][j][k])
						where=Stack[i][j][k];
				}
				Changed+=fill(i,j,where);
			}
		}
	}
	*/

	//printf("1:\n");
	for(i=0;i<9;i++){
		int ar[9]={};
		for(j=0;j<9;j++){
			for(k=0;k<9;k++){
				if(Stack[i][j][k])
					ar[k]++;
			}
		}
		for(r=2;r<10;r++){
			int cnt=0,rpt[10]={};
			for(k=0;k<9;k++){
				if(ar[k]==r)
					rpt[cnt++]=k;
			}
			if(cnt==r){
				//printf("CheckpointR:%d\n",i);
				int flag=0;
				for(j=0;j<9;j++){
					flag=flag||(!(Check(Stack[i][j],rpt,r)));
				}
				if(flag)
					continue;
				for(j=0;j<9;j++){
					Keep(Stack[i][j],rpt,r);
				}
			}
		}
	}
	//printf("2:\n");
	for(j=0;j<9;j++){
		int ac[9]={};
		for(i=0;i<9;i++){
			for(k=0;k<9;k++){
				if(Stack[i][j][k])
					ac[k]++;
			}
		}
		for(r=2;r<10;r++){
			int cnt=0,rpt[10]={};
			for(k=0;k<9;k++){
				if(ac[k]==r)
					rpt[cnt++]=k;
			}
			if(cnt==r){
				//printf("CheckpointC:%d\n",j);
				int flag=0;
				for(i=0;i<9;i++){
					flag=flag||(!(Check(Stack[i][j],rpt,r)));
				}
				if(flag)
					continue;
				for(i=0;i<9;i++){
					Keep(Stack[i][j],rpt,r);
				}
			}
		}
	}
	//printf("3:\n");
	for(I=0;I<3;I++){
		for(J=0;J<3;J++){
			int ap[9]={};
			for(i=I*3;i<(I+1)*3;i++){
				for(j=J*3;j<(J+1)*3;j++){
					for(k=0;k<9;k++){
						if(Stack[i][j][k])
							ap[k]++;
					}
				}
			}
			for(r=2;r<10;r++){
				int cnt=0,rpt[10]={};
				for(k=0;k<9;k++){
					if(ap[k]==r)
						rpt[cnt++]=k;
				}
				if(cnt==r){
					//printf("CheckpointA:%d,%d\n",I,J);
					int flag=0;
					for(i=I*3;i<(I+1)*3;i++){
						for(j=J*3;j<(J+1)*3;j++){
							flag=flag||(!(Check(Stack[i][j],rpt,r)));
						}
					}
					if(flag)
						continue;
					for(i=I*3;i<(I+1)*3;i++){
						for(j=J*3;j<(J+1)*3;j++){
							Keep(Stack[i][j],rpt,r);
						}
					}
				}
			}
		}
	}

	if(Changed)
		return Changed;

	printf("AfterChange:\n");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(a[i][j])
				printf("%11d",a[i][j]);
			else{
				char cb[10]={};
				cb[9]='\0';
				for(k=0;k<9;k++){
					if(Stack[i][j][k])
						cb[k]=k+'1';
					else
						cb[k]=' ';
				}
				printf("[%s]",cb);
			}
		}
		printf("\n");
	}

	for(i=0;i<9;i++){
		int ar[9]={};
		for(j=0;j<9;j++){
			for(k=0;k<9;k++){
				if(Stack[i][j][k])
					ar[k]++;
			}
		}
		for(k=0;k<9;k++){
			if(ar[k]==1){
				//printf("R%d:%d\n",i,k+1);
				for(j=0;j<9;j++){
					if(Stack[i][j][k])
						Changed+=fill(i,j,Stack[i][j][k]);
				}
			}
		}
	}
	if(Changed)
		return Changed;
	for(j=0;j<9;j++){
		int ac[9]={};
		for(i=0;i<9;i++){
			for(k=0;k<9;k++){
				if(Stack[i][j][k])
					ac[k]++;
			}
		}
		for(k=0;k<9;k++){
			if(ac[k]==1){
				//printf("C%d:%d\n",j,k+1);
				for(i=0;i<9;i++){
					if(Stack[i][j][k])
						Changed+=fill(i,j,Stack[i][j][k]);
				}
			}
		}
	}
	if(Changed)
		return Changed;
	for(I=0;I<3;I++){
		for(J=0;J<3;J++){
			int ap[9]={};
			for(i=I*3;i<(I+1)*3;i++){
				for(j=J*3;j<(J+1)*3;j++){
					for(k=0;k<9;k++){
						if(Stack[i][j][k])
							ap[k]++;
					}
				}
			}
			for(k=0;k<9;k++){
				if(ap[k]==1){
					//printf("%d,%d:%d\n",I,J,k+1);
					for(i=I*3;i<(I+1)*3;i++){
						for(j=J*3;j<(J+1)*3;j++){
							if(Stack[i][j][k])
								Changed+=fill(i,j,Stack[i][j][k]);
						}
					}
				}
			}
		}
	}
	return Changed;
}

int IsSolved(int* pointer){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(!pointer[i*9+j]){ //a[i][j]
				return 0;
			}
		}
	}
	return 1;
}
int main(){
	int flag=1,stepcnt=0,i,j,k,GuessFlag,GuessCnt;
	memcpy(b,a,sizeof(int)*81);
	while(flag){
		flag=main1();
		memcpy(a,b,sizeof(int)*81);
		printf("Step%dEnd\n",stepcnt++);
		if(!flag&&!IsSolved(a[0])){
			printf("---GuessPart:---\n");
			GuessFlag=0;
			GuessCnt=0;
			memcpy(aBk,a,sizeof(int)*81);
			memcpy(StackBk,Stack,sizeof(int)*9*9*9);
			memset(Stack,0,sizeof(int)*9*9*9);
			for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					for(k=0;k<9;k++){
						if(StackBk[i][j][k]){
							int SubFlag=1;
							GuessFlag=0;
							GuessCnt=0;
							memcpy(aBk,a,sizeof(int)*81);
							a[i][j]=StackBk[i][j][k];
							printf("Guess:(%d,%d)is%d\n",i,j,StackBk[i][j][k]);
							while(SubFlag){
								SubFlag=main1();
								memcpy(a,b,sizeof(int)*81);
								memset(Stack,0,sizeof(int)*9*9*9);
								printf("GuessStep%dEnd\n",GuessCnt++);
							}
							if(IsSolved(a[0]))
								GuessFlag=1;
							if(GuessFlag)
								break;
							memcpy(a,aBk,sizeof(int)*81);
							memcpy(b,aBk,sizeof(int)*81);
						}
					}
					if(GuessFlag)
						break;
				}
				if(GuessFlag)
					break;
			}
			printf("---GuessPartEnd---\n");
		}
		memset(Stack,0,sizeof(int)*9*9*9);
	}
	if(!IsSolved(a[0])){
		printf("NOT Solved.\n");
		return 1;
	}
	printf("Solved!\n");
	return 0;
}
