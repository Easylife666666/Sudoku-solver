#include <stdio.h>
#include <string.h>
int a[9][9]={
{5,4,0,8,0,1,9,0,6},
{0,2,3,0,0,0,0,7,8},
{8,0,0,0,0,0,0,3,0},
{2,0,0,0,4,0,0,0,1},
{0,0,0,7,5,9,0,0,0},
{9,0,0,0,2,0,0,0,3},
{0,6,0,0,0,0,0,0,2},
{4,9,0,0,0,0,8,6,0},
{3,0,1,2,0,7,0,4,9}
},b[9][9];
int Stack[9][9][9]={};

int Check(int* SubStack,int* rpt,int r){
	int cnt=0;
	for(int i=0;i<r;i++){
		if(SubStack[rpt[i]])
			cnt++;
	}
	return (cnt==r||!cnt)?1:0;
}
void Keep(int* SubStack,int* rpt,int r){
	int cnt=0;
	for(int i=0;i<r;i++){
		if(SubStack[rpt[i]])
			cnt++;
	}
	if(cnt==r){
		for(int i=0;i<9;i++){
			int flag=1;
			for(int j=0;j<r;j++){
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
	int flag=0;
	//R
	for(int i=0;i<9;i++){
		if(a[i][Ij]==Ik)
			flag=1;
	}
	//C
	for(int j=0;j<9;j++){
		if(a[Ii][j]==Ik)
			flag=1;
	}
	//S
	for(int i=Ii/3*3;i<(Ii/3+1)*3;i++){
		for(int j=Ij/3*3;j<(Ij/3+1)*3;j++){
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
	int Changed=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(a[i][j])
				//printf("%11d",a[i][j]);
				continue;
			else{
				char b[10]={};
				b[9]='\0';
				for(int k=1;k<10;k++){
					if(!exists(i,j,k)){
						b[k-1]=k+'0';
						Stack[i][j][k-1]=k;
					}
					else
						b[k-1]=' ';
				}
				//printf("[%s]",b);
			}
		}
		//printf("\n");
	}

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

	//printf("1:\n");
	for(int i=0;i<9;i++){
		int ar[9]={};
		for(int j=0;j<9;j++){
			for(int k=0;k<9;k++){
				if(Stack[i][j][k])
					ar[k]++;
			}
		}
		for(int r=2;r<10;r++){
			int cnt=0,rpt[10]={};
			for(int k=0;k<9;k++){
				if(ar[k]==r)
					rpt[cnt++]=k;
			}
			if(cnt==r){
				//printf("CheckpointR:%d\n",i);
				int flag=0;
				for(int j=0;j<9;j++){
					flag=flag||(!(Check(Stack[i][j],rpt,r)));
				}
				if(flag)
					continue;
				for(int j=0;j<9;j++){
					Keep(Stack[i][j],rpt,r);
				}
			}
		}
	}
	//printf("2:\n");
	for(int j=0;j<9;j++){
		int ac[9]={};
		for(int i=0;i<9;i++){
			for(int k=0;k<9;k++){
				if(Stack[i][j][k])
					ac[k]++;
			}
		}
		for(int r=2;r<10;r++){
			int cnt=0,rpt[10]={};
			for(int k=0;k<9;k++){
				if(ac[k]==r)
					rpt[cnt++]=k;
			}
			if(cnt==r){
				//printf("CheckpointC:%d\n",j);
				int flag=0;
				for(int i=0;i<9;i++){
					flag=flag||(!(Check(Stack[i][j],rpt,r)));
				}
				if(flag)
					continue;
				for(int i=0;i<9;i++){
					Keep(Stack[i][j],rpt,r);
				}
			}
		}
	}
	//printf("3:\n");
	for(int I=0;I<3;I++){
		for(int J=0;J<3;J++){
			int ap[9]={};
			for(int i=I*3;i<(I+1)*3;i++){
				for(int j=J*3;j<(J+1)*3;j++){
					for(int k=0;k<9;k++){
						if(Stack[i][j][k])
							ap[k]++;
					}
				}
			}
			for(int r=2;r<10;r++){
				int cnt=0,rpt[10]={};
				for(int k=0;k<9;k++){
					if(ap[k]==r)
						rpt[cnt++]=k;
				}
				if(cnt==r){
					//printf("CheckpointA:%d,%d\n",I,J);
					int flag=0;
					for(int i=I*3;i<(I+1)*3;i++){
						for(int j=J*3;j<(J+1)*3;j++){
							flag=flag||(!(Check(Stack[i][j],rpt,r)));
						}
					}
					if(flag)
						continue;
					for(int i=I*3;i<(I+1)*3;i++){
						for(int j=J*3;j<(J+1)*3;j++){
							Keep(Stack[i][j],rpt,r);
						}
					}
				}
			}
		}
	}

	//printf("AfterChange:\n");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(a[i][j])
				printf("%11d",a[i][j]);
			else{
				char b[10]={};
				b[9]='\0';
				for(int k=0;k<9;k++){
					if(Stack[i][j][k])
						b[k]=k+'1';
					else
						b[k]=' ';
				}
				printf("[%s]",b);
			}
		}
		printf("\n");
	}

	for(int i=0;i<9;i++){
		int ar[9]={};
		for(int j=0;j<9;j++){
			for(int k=0;k<9;k++){
				if(Stack[i][j][k])
					ar[k]++;
			}
		}
		for(int k=0;k<9;k++){
			if(ar[k]==1){
				//printf("R%d:%d\n",i,k+1);
				for(int j=0;j<9;j++){
					if(Stack[i][j][k])
						Changed+=fill(i,j,Stack[i][j][k]);
				}
			}
		}
	}
	for(int j=0;j<9;j++){
		int ac[9]={};
		for(int i=0;i<9;i++){
			for(int k=0;k<9;k++){
				if(Stack[i][j][k])
					ac[k]++;
			}
		}
		for(int k=0;k<9;k++){
			if(ac[k]==1){
				//printf("C%d:%d\n",j,k+1);
				for(int i=0;i<9;i++){
					if(Stack[i][j][k])
						Changed+=fill(i,j,Stack[i][j][k]);
				}
			}
		}
	}
	for(int I=0;I<3;I++){
		for(int J=0;J<3;J++){
			int ap[9]={};
			for(int i=I*3;i<(I+1)*3;i++){
				for(int j=J*3;j<(J+1)*3;j++){
					for(int k=0;k<9;k++){
						if(Stack[i][j][k])
							ap[k]++;
					}
				}
			}
			for(int k=0;k<9;k++){
				if(ap[k]==1){
					//printf("%d,%d:%d\n",I,J,k+1);
					for(int i=I*3;i<(I+1)*3;i++){
						for(int j=J*3;j<(J+1)*3;j++){
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
int main(){
	int flag=1,stepcnt=0;
	memcpy(b,a,sizeof(int)*81);
	while(flag){
		flag=main1();
		memcpy(a,b,sizeof(int)*81);
		memset(Stack,0,sizeof(int)*9*9*9);
		printf("Step%dEnd\n",stepcnt++);
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(!a[i][j]){
				printf("NOT Solved.\n");
				return 1;
			}
		}
	}
	printf("Solved!\n");
	return 0;
}
