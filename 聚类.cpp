#include<iostream>
#include<math.h>
#include<stdlib.h>
using namespace std;
#define N 20
#define M 5
int score[N][M];
float r[N][N];
int df[N];
float score1,score2,score3,score4,score5;



void cluster_r(float(*cluster)(int ,int)) { //成绩转化相似矩阵
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			r[i][j]=cluster(i,j);
}

void cluster_r_tran() { //计算传递闭包
	while(1) {
		float a[N][N];
		for(int i=0; i<N; i++) {
			for(int j=i; j<N; j++) {
				float b=0,c;
				for(int k=0; k<N; k++) {
					c=r[i][k]<r[j][k]?r[i][k]:r[j][k];
					b=c>b?c:b;
				}
				a[i][j]=b;
			}
		}
		bool flag=1;
		for(int i=0; i<N; i++)
			for(int j=i; j<N; j++)
				if(r[i][j]!=a[i][j])
					flag=0;
		if(flag)
			return ;
		else {
			for(int i=0; i<N; i++)
				for(int j=i; j<N; j++)
					r[j][i]=r[i][j]=a[i][j];
		}
	}
}

void cluster_r_r(float fr) {//聚类 
	int a[N][N];
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++) {
			if(r[i][j]>=fr)
				a[i][j]=1;
			else
				a[i][j]=0;
		}
	for(int i=0; i<N; i++)
		df[i]=i;
	for(int i=0; i<N; i++) {
		if(!a[i][i])
			break ;
		for(int j=i+1; j<N; j++)
			if(a[i][j])
				df[j]=df[i];
	}
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++)
			if(df[j]==i)
				cout<<j+1<<" ";
		cout<<endl;
	}
}

float cluster_max() { //计算部分最大值
	float s=0,r=0;
	for(int i=0; i<N; i++) {
		r=0;
		for(int j=0; j<M; j++)
			r+=score[i][j];
		s=s>r?s:r;
	}
	return s;
}

float cluster_r_fabs(int i,int j) { //绝对值减数法
	if(i==j)
		return 1;
	float s=0,c=cluster_max()/5;
	for(int k=0; k<M; k++)
		s+=abs(score[i][k]-score[j][k]);
	return 1-s/c;
}

float cluster_r_mm(int i,int j) { //最大最小法
	if(i==j)
		return 1;
	float a=0,b=0;
	for(int k=0; k<M; k++) {
		a+=score[i][k]>score[j][k]?score[j][k]:score[i][k];//最小
		b+=score[i][k]>score[j][k]?score[i][k]:score[j][k];//最大
	}
	return a/b;
}

void file_read(float score1,float score2,float score3,float score4,float score5) {
	// 读数据
	int i;
	FILE *fpRead=fopen("scores.txt","r");
	if(fpRead==NULL) exit(0);
	fscanf(fpRead,"%*[^\n]");  //跳过第一行
	for(i=0; i<N; i++) {
		fscanf(fpRead,"%f\t%f\t%f\t%f\t%f",&score1,&score2,&score3,&score4,&score5);
		score[i][1]=score1;
		score[i][2]=score2;
		score[i][3]=score3;
		score[i][4]=score4;
		score[i][5]=score5;
		printf("%f\t%f\t%f\t%f\t%f\n",score1,score2,score3,score4,score5);

	}
	cout<<endl;
}


int main() {
	file_read(score1,score2,score3,score4,score5);
	cout<<endl;
	printf("最大最小距离聚类：\n");
	cluster_r(cluster_r_mm);
//	for(int i=0; i<N; i++) {
//		for(int j=0; j<N; j++)
//			printf("%0.2f ",r[i][j]);
//		cout<<endl;
//	}
//	cluster_r_tran();
	for(float z=0.9; z>0.6; z-=0.1) {
		cout<<"r="<<z<<"时的聚类结果为:"<<endl;
		cluster_r_r(z);
		cout<<endl;
	}
	printf("绝对值减数法聚类：\n");
	cluster_r(cluster_r_fabs);
//	for(int i=0; i<N; i++) {
//		for(int j=0; j<N; j++)
//			printf("%0.2f ",r[i][j]);
//		cout<<endl;
//	}
	cout<<endl;

	cluster_r_tran();
//	for(int i=0; i<N; i++) {
//		for(int j=0; j<N; j++)
//			printf("%0.2f ",r[i][j]);
//		cout<<endl;
//	}
//	cout<<endl;

	for(float z=0.8; z>0.6; z-=0.05) {
		cout<<"r="<<z<<"时的聚类结果为:"<<endl;
		cluster_r_r(z);
		cout<<endl;
	}
	cout<<endl;
}
