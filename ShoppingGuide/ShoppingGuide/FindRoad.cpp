#include "stdafx.h"
#include "FindRoad.h"


CFindRoad::CFindRoad()
{
	m_shortest = -1;
	m_path = NULL;
	numVertex = 0;
	matrix = NULL;
	mark = NULL;
}


CFindRoad::~CFindRoad()
{
	
}


void CFindRoad::find_the_path(const int start, const int dest)
{
	int *D = (int*)malloc(sizeof(int)*numVertex);;   //存储设置的源城市到任意城市的估计最小长度
	int i, v, w;

	for (i = 0; i<numVertex; i++)
	{
		D[i] = 100000;//初始化为无限大，用来存放最短路径
		m_path[i] = -1;//存放经过的点集合
	}
	D[start] = 0;

	for (i = 0; i<verNum(); i++)
	{
		v = minVertex(D);
		if (D[v] == 100000)
			return;
		setMark(v, 1);//已遍历过
		for (w = firstNghbr(v); w<verNum(); w = nextNghbr(v, w))//从第V的下一个W开始，小于总数，V---W的权值
		{
			if (D[w]>(D[v] + weight(v, w)))
			{
				D[w] = D[v] +weight(v, w);//重新设置长度
				m_path[w] = v;//从W开始，下一个是点是V（m_path[w]）(各点到其他点的最短经过点集合)
			}
		}
	}

	m_shortest = D[dest];

	free(D);
	D = NULL;

	IntToVector(dest, start); //start开始->m_path[start]->.....最短路径经过的点，不包括起始点
}

int CFindRoad::minVertex(int* D)
{
	int i, v;

	for (i = 0; i<verNum(); i++)
	{
		if (getMark(i) == 0)
		{
			v = i;
			break;
		}
	}
	for (i++; i<verNum(); i++)
	if ((getMark(i) == 0) && (D[i] < D[v]))//遍历所有D[]
		v = i;
	return v;
}

int CFindRoad::verNum()
{
	return numVertex;
}

int CFindRoad::edgNum()
{
	return numEdge;
}

int CFindRoad::firstNghbr(int v)//第V个元素
{
	int i;
	for (i = 0; i<numVertex; i++)
	if (matrix[v][i] != 0)//未遍历
		return i;
	return i;           //若无第一个邻接结点返回节点数
}
int CFindRoad::nextNghbr(int v1, int v2)//V1节点的第V2个邻接点后
{
	int i;
	for (i = v2 + 1; i<numVertex; i++)
	if (matrix[v1][i] != 0)
		return i;
	return i;
}

void CFindRoad::setEdge(int v1, int v2, int wgt)//第V个元素
{
	if (matrix[v1][v2] == 0)
		numEdge++;
	matrix[v1][v2] = wgt;
}
void CFindRoad::delEdge(int v1, int v2)//第V个元素
{
	if (matrix[v1][v2] != 0)
		numEdge--;
	matrix[v1][v2] = 0;
}
int CFindRoad::weight(int v1, int v2)//第V个元素
{
	return matrix[v1][v2];
}
int CFindRoad::getMark(int v)//第V个元素
{
	return mark[v];
}
void CFindRoad::setMark(int v,int val)
{
	mark[v] = val;
}

// 创建图
void CFindRoad::CreateMap(int num)
{
	if (num <= 0)
	{
		return;
	}
	
		int i,j;
		numVertex = num;//节点个数
		numEdge = 0;
		m_road.clear();//清空经过节点
		m_path = (int *)malloc(sizeof(int)*numVertex);
		mark = new int[numVertex];
		for(i=0; i<numVertex; i++)
			mark[i] = 0;   //初始化各点访问情况为0,即未访问


		matrix = (int**) new int*[numVertex];//二位数组 邻接矩阵
		for(i=0; i<numVertex; i++)
			matrix[i] = new int[numVertex];//申请空间


		for(i=0; i<numVertex; i++)
			for(j=0; j<numVertex; j++)
				matrix[i][j] = 0;      //权为0表示两点间没有边连接//初始化邻接矩阵此时没有存入
}


void CFindRoad::IntToVector(int dest, int start)
{
	int k;
	k = m_path[dest];
	if (k == start)
		return;
	IntToVector(k, start);
	m_road.push_back(k);
}


// 清空图
void CFindRoad::Clear()
{
	m_road.clear();
	if (m_path != NULL)
	{
		free(m_path);
		m_path = NULL;
	}
	if (mark != NULL)
	{
		delete[] mark;
		mark = NULL;
	}

	if (matrix != NULL)
	{
		for (int i = 0; i < numVertex; i++)
		{
			delete[] matrix[i];
			matrix[i] = NULL;
		}
		delete[] matrix;
		matrix = NULL;
	}
	
		


}


// 重置所有属性

