#include "pch.h"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#pragma warning(disable:4996)
using namespace std;

struct number  //每个数的结构体 sa
{
	int sign;//定义一个标记,表示这个数还有几种可能的取值 
	int maybe[9] = { 1,2,3,4,5,6,7,8,9 };//定义num的可能取值 
	int num;//定义num的确定值
}a[9][9];
int m, n;
int line, row;//line行，row列
int gongline, gongrow;
void deletehl(int i, int j);
void del(int i, int j);
void deletegong(int i, int j);
void resetmay()
{
	for(int i=0; i<m; i++)
		for (int j = 0; j < m; j++)
		{
			a[i][j].num = 0;
			a[i][j].sign=m;
			for (int k = 0; k < 9; k++)
			{

				a[i][j].maybe[k] = k + 1;
			}
		}
}
void scanmay()
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < 9; k++)
			{
				cout<<a[i][j].maybe[k]<<" ";
			}
}
void inputsign()//这一段用来对sign赋初值 
{
	for (int i = 0; i < line; i++)
		for (int j = 0; j < row; j++)
		{
			if (a[i][j].num == 0)
			{
				a[i][j].sign = line;
			}
			else
			{
				a[i][j].sign = 0;
			}
		}
}

void onlyone(int i, int j)//这个函数是把唯一解求出来； 
{
	for (int k = 0; k < line; k++) //唯一解在maybe里面 
	{
		if (a[i][j].maybe[k] != 0)
		{
			a[i][j].num = a[i][j].maybe[k];
			a[i][j].maybe[k] = 0;
			a[i][j].sign = 0;
			del(i, j);
			break;
		}
	}
}

void del(int i, int j)
{
	if (m == 3 || m == 5 || m == 7)
	{
		deletehl(i, j);
	}
	else if (m == 4 || m == 6 || m == 8 || m == 9)
	{
		deletehl(i, j);
		deletegong(i, j);
	}
	else
	{
		cout << "m is not right." << endl;
	}
}
void deletehl(int i, int j)
{
	for (int k = 0; k < line; k++)//把同一行的sign减一，把maybe的可能取值变零 
	{
		if (a[i][k].maybe[a[i][j].num - 1] != 0)//如果不等0，说明还没去掉这个可能；
		//等0的话，说明前面已经去掉了，sign不用再减一了； 
		{
			a[i][k].maybe[a[i][j].num - 1] = 0;
			a[i][k].sign--;
			if (a[i][k].sign == 1)
			{
				onlyone(i, k);
			}
		}//把同一行的相同可能值删掉 


		if (a[k][j].maybe[a[i][j].num - 1] != 0)
		{
			a[k][j].maybe[a[i][j].num - 1] = 0;
			a[k][j].sign--;
			if (a[k][j].sign == 1)
			{
				onlyone(k, j);
			}
		}//把同一列的相同可能值删掉 
	}
}

void deletegong(int i, int j)
{
	//宫的首地址计算  //x,y；这个宫的首个数的地址为a[x][y] ;
	int x, y;
	x = (i / gongrow) * gongrow;
	y = (j / gongline) * gongline;
	for (int gi = 0; gi < gongrow; gi++)
		for (int gj = 0; gj < gongline; gj++)//把同一宫的sign减一，把maybe【num】的取值变零 
		{
			if (a[gi + x][gj + y].maybe[a[i][j].num - 1] != 0)
			{
				a[gi + x][gj + y].maybe[a[i][j].num - 1] = 0;
				a[gi + x][gj + y].sign--;
				if (a[gi + x][gj + y].sign == 1)
				{
					onlyone(gi + x, gj + y);
				}
			}
		}
}
void scansign()//用来寻找sign==1的数 
{
	for (int i = 0; i < line; i++)
		for (int j = 0; j < row; j++)
		{
			if (a[i][j].num == 0 && a[i][j].sign == 1)//如果num==0，说明这个空需要填 
			//sign等于1，说明有唯一解； 
			{
				onlyone(i, j);
			}
			else if (a[i][j].num != 0)
			{
				del(i, j);
			}
		}
}

void choosemn()//用来确定line和row和宫的大小 
{
	if (m == 3 || m == 5 || m == 7)
	{
		line = row = m;
	}
	else if (m == 4)
	{
		line = row = m;
		gongline = gongrow = 2;
	}
	else if (m == 6)
	{
		line = row = m;
		gongline = 3;
		gongrow = 2;
	}
	else if (m == 8)
	{
		line = row = m;
		gongline = 2;
		gongrow = 4;
	}
	else if (m == 9)
	{
		line = row = m;
		gongline = 3;
		gongrow = 3;
	}
	else
	{
		cout << "m is not right." << endl;
	}
}

int main(int argc, char** argv)
{
	int i, j;
	ifstream ifp;
	ofstream ofp;
	m = atoi(argv[2]);//宫阶数
	n = atoi(argv[4]);//盘面数
	choosemn();
	ifp.open(argv[6]);
	if (!ifp.is_open())//判断文件是否成功打开
		cout << "文件打开失败" << endl;
	ofp.open(argv[8]);
	if (!ofp.is_open())
		cout << "文件打开失败" << endl;
	while (n > 0)
	{
		resetmay();
		for (i = 0; i < m; i++)//输入数独盘面
		{
			for (j = 0; j < m; j++)
			{
				ifp >> a[i][j].num;
			}
		}
		inputsign();
		scansign();

		for (i = 0; i < m; i++)//输出解出的数独
		{
			for (j = 0; j < m; j++)
			{
				if (j < (m - 1))
					ofp << a[i][j].num << " ";
				else
					ofp << a[i][j].num;
			}
			ofp << endl;
		}
		ofp << endl;
		n--;
	}
	return 0;
}
