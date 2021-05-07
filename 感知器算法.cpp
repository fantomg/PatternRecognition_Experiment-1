#include<iostream>
#include<math.h>
#include<stdlib.h>
using namespace std;
#define COUNT 20  //样本训练次数
#define DIMEN  5  // 输入样本维度
int score[COUNT][DIMEN];
float score1,score2,score3,score4,score5,aver;
double x[COUNT][DIMEN]; 	// 输入样本训练数据
int y[COUNT];              // 训练输出
int d[COUNT];              // 理想输出
double W[COUNT];           // 权值矩阵
double thres;               // 阈值
double eps = 0.0001;       // 进行收敛判断的条件
double s, dp, ep;   // dp为理想输出与实际输出的差，ep为均方误差
double deta = 0.2;          // 学习因子
double r[1] = {3.0};            // 随机数种子
int i, j, k;

void train() {//训练方法
	FILE *fpRead=fopen("scores.txt","r");//训练集数据读取
	if(fpRead==NULL) exit(0);
	fscanf(fpRead,"%*[^\n]");  //跳过第一行
	for(i=0; i<20; i++) {
		fscanf(fpRead,"%f\t%f\t%f\t%f\t%f",&score1,&score2,&score3,&score4,&score5);
		x[i][1]=score1/100;
		x[i][2]=score2/100;
		x[i][3]=score3/100;
		x[i][4]=score4/100;
		x[i][5]=score5/100;
		printf("%f\t%f\t%f\t%f\t%f\n",x[i][1],x[i][2],x[i][3],x[i][4],x[i][5]);
		aver = (x[i][1]+x[i][2]+x[i][3]+x[i][4]+x[i][5])/5;
		if((float)aver >= 0.6)
			d[i] = 1;
		else
			d[i] = 0;
		printf("%d\n",d[i]);
	}
	for(j = 0; j < DIMEN; j++)         //对权值、阈值进行初始化，随机产生[-1,1]间的数
		W[j] = (2.0 * rand() / RAND_MAX - 1) ;
	thres = (2.0 * rand() / RAND_MAX - 1) ;
//	thres = 0.5;
	k = 0;                        //迭代次数
	while(1) {
		ep = 0;
		for(i = 0; i < COUNT; i++) {
			s = 0;
			for(j = 0; j < DIMEN; j++)
				s += W[j] * x[i][j];
			s = s - thres;
			if(s >= 0.6)
				y[i] = 1;
			else
				y[i] = 0;
			dp = (double)(d[i] - y[i]);
			for(j = 0; j < DIMEN; j++) { //更新权值、阈值
				W[j] = W[j] + deta * dp * x[i][j];
				thres = thres - deta * dp;
			}
			dp =(dp * dp )/ 2.0;
			ep += dp;
		}
		k++;
		if(ep <= eps)     
			break;
	}
	printf("迭代次数=%d\n",k);
	printf("权值：\n");
	for(j = 0; j < DIMEN; j++)
		printf("%f\n",W[j]);
	printf("阈值：\n");
	printf("%f\n",thres);
	printf("成绩优秀的学生编号：");
	for(j = 0; j < COUNT; j++)
		if ((double)y[j] == 1)
			printf("%d ",j+1);
	printf("\n成绩合格的学生编号：");
	for(j = 0; j < COUNT; j++)
		if ((double)y[j] == 0)
			printf("%d ",j+1);
//		printf("%d\n",y[j]) ;
}

void test () {//测试方法
	double xt[20][5];          //测试数据
	int dt[20];                //理想数据输出
	int yt[20];               //测试输出
	int count = 0;          //测试正确的数目
	double Rate;             //正确分类率
	FILE *fpRead1=fopen("scores-test.txt","r");//测试集数据读取
	if(fpRead1==NULL) exit(0);
	fscanf(fpRead1,"%*[^\n]");  //跳过第一行
	for(i=0; i<20; i++) {
		fscanf(fpRead1,"%f\t%f\t%f\t%f\t%f",&score1,&score2,&score3,&score4,&score5);
		xt[i][1]=score1/100;
		xt[i][2]=score2/100;
		xt[i][3]=score3/100;
		xt[i][4]=score4/100;
		xt[i][5]=score5/100;
		aver = (xt[i][1]+xt[i][2]+xt[i][3]+xt[i][4]+xt[i][5])/5;
		if((float)aver >= 0.6)
			dt[i] = 1;
		else
			dt[i] = 0;
//		printf("%d\n",d[i]);
		s = 0;
		for(j = 0; j < DIMEN; j++)                          //计算测试输出
			s += W[j] * xt[i][j];
		s = s - thres;
		if(s >= 0.6)
			y[i] = 1;
		else
			y[i] = 0;

		if(dt[i] == y[i])
			count++;
	}
	printf("\n测试数据结果：\n");
	printf("正确分类个数=%d\n",count);
	Rate = (double)(count / (double)COUNT);
	printf("分类正确率：\n");
	printf("%f",Rate*100);
	printf("\n测试组成绩优秀的学生编号：");
	for(j = 0; j < COUNT; j++)
		if ((double)y[j] == 1)
			printf("%d ",j+1);
	printf("\n测试组成绩合格的学生编号：");
	for(j = 0; j < COUNT; j++)
		if ((double)y[j] == 0)
			printf("%d ",j+1);
};

int main() {
	train();	
	test();
	cout<<endl;
}


