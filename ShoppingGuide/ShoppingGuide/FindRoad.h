#pragma once
#include <vector>
using namespace std;
class CFindRoad
{
public:
	CFindRoad();
	~CFindRoad();
public:


	void find_the_path(const int start, const int dest);
	
	void setEdge(int v1, int v2, int wgt);
private:
	int minVertex(int* D);

	int verNum();
	int edgNum();//
	int firstNghbr(int v);//��V��Ԫ��
	int nextNghbr(int v1, int v2);//V1�ڵ�ĵ�V2���ڽӵ��
	
	void delEdge(int v1, int v2);
	int weight(int v1, int v2);
	int getMark(int v);
	void setMark(int v, int val);



	int numVertex, numEdge;//�ڵ����    ��Ȩ·����
	int **matrix;//�ڽӾ���///////�洢�ڵ���Ϣ
	int *mark;//��־λ

	

public:
	// ����ͼ
	void CreateMap(int num);
	int m_shortest;
	vector<int> m_road;
	int *m_path;
private:
	void IntToVector(int dest, int start);
public:
	// ���ͼ
	void Clear();
	// ������������

};

