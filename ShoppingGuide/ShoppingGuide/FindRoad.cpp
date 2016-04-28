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
	int *D = (int*)malloc(sizeof(int)*numVertex);;   //�洢���õ�Դ���е�������еĹ�����С����
	int i, v, w;

	for (i = 0; i<numVertex; i++)
	{
		D[i] = 100000;//��ʼ��Ϊ���޴�����������·��
		m_path[i] = -1;//��ž����ĵ㼯��
	}
	D[start] = 0;

	for (i = 0; i<verNum(); i++)
	{
		v = minVertex(D);
		if (D[v] == 100000)
			return;
		setMark(v, 1);//�ѱ�����
		for (w = firstNghbr(v); w<verNum(); w = nextNghbr(v, w))//�ӵ�V����һ��W��ʼ��С��������V---W��Ȩֵ
		{
			if (D[w]>(D[v] + weight(v, w)))
			{
				D[w] = D[v] +weight(v, w);//�������ó���
				m_path[w] = v;//��W��ʼ����һ���ǵ���V��m_path[w]��(���㵽���������̾����㼯��)
			}
		}
	}

	m_shortest = D[dest];

	free(D);
	D = NULL;

	IntToVector(dest, start); //start��ʼ->m_path[start]->.....���·�������ĵ㣬��������ʼ��
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
	if ((getMark(i) == 0) && (D[i] < D[v]))//��������D[]
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

int CFindRoad::firstNghbr(int v)//��V��Ԫ��
{
	int i;
	for (i = 0; i<numVertex; i++)
	if (matrix[v][i] != 0)//δ����
		return i;
	return i;           //���޵�һ���ڽӽ�㷵�ؽڵ���
}
int CFindRoad::nextNghbr(int v1, int v2)//V1�ڵ�ĵ�V2���ڽӵ��
{
	int i;
	for (i = v2 + 1; i<numVertex; i++)
	if (matrix[v1][i] != 0)
		return i;
	return i;
}

void CFindRoad::setEdge(int v1, int v2, int wgt)//��V��Ԫ��
{
	if (matrix[v1][v2] == 0)
		numEdge++;
	matrix[v1][v2] = wgt;
}
void CFindRoad::delEdge(int v1, int v2)//��V��Ԫ��
{
	if (matrix[v1][v2] != 0)
		numEdge--;
	matrix[v1][v2] = 0;
}
int CFindRoad::weight(int v1, int v2)//��V��Ԫ��
{
	return matrix[v1][v2];
}
int CFindRoad::getMark(int v)//��V��Ԫ��
{
	return mark[v];
}
void CFindRoad::setMark(int v,int val)
{
	mark[v] = val;
}

// ����ͼ
void CFindRoad::CreateMap(int num)
{
	if (num <= 0)
	{
		return;
	}
	
		int i,j;
		numVertex = num;//�ڵ����
		numEdge = 0;
		m_road.clear();//��վ����ڵ�
		m_path = (int *)malloc(sizeof(int)*numVertex);
		mark = new int[numVertex];
		for(i=0; i<numVertex; i++)
			mark[i] = 0;   //��ʼ������������Ϊ0,��δ����


		matrix = (int**) new int*[numVertex];//��λ���� �ڽӾ���
		for(i=0; i<numVertex; i++)
			matrix[i] = new int[numVertex];//����ռ�


		for(i=0; i<numVertex; i++)
			for(j=0; j<numVertex; j++)
				matrix[i][j] = 0;      //ȨΪ0��ʾ�����û�б�����//��ʼ���ڽӾ����ʱû�д���
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


// ���ͼ
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


// ������������

