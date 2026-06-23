#include <stdio.h>
int a[9][9]={
{4,2,7,6,9,5,3,1,8},
{8,6,3,7,2,1,4,5,9},
{9,5,1,8,3,4,6,7,2},
{1,3,5,2,4,7,8,9,6},
{6,8,2,3,1,9,5,4,7},
{7,4,9,5,6,8,1,2,3},
{3,1,4,9,7,6,2,8,5},
{2,7,8,4,5,3,9,6,1},
{5,9,6,1,8,2,7,3,4}
};
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
int main(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(a[i][j])
				printf("%11d",a[i][j]);
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
				printf("[%s]",b);
			}
		}
		printf("\n");
	}

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			int cnt=0;
			for(int k=0;k<9;k++){
				if(Stack[i][j][k])
					cnt++;
			}
			if(cnt==1)
				printf("Place%d:%dSpecial\n",i,j);
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

	printf("AfterChange:\n");
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
			if(ar[k]==1)
				printf("R%d:%d\n",i,k+1);
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
			if(ac[k]==1)
				printf("C%d:%d\n",j,k+1);
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
				if(ap[k]==1)
					printf("%d,%d:%d\n",I,J,k+1);
			}
		}
	}
	return 0;
}

