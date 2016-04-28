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
	int firstNghbr(int v);//第V个元素
	int nextNghbr(int v1, int v2);//V1节点的第V2个邻接点后
	
	void delEdge(int v1, int v2);
	int weight(int v1, int v2);
	int getMark(int v);
	void setMark(int v, int val);



	int numVertex, numEdge;//节点个数    有权路径数
	int **matrix;//邻接矩阵///////存储节点信息
	int *mark;//标志位

	

public:
	// 创建图
	void CreateMap(int num);
	int m_shortest;
	vector<int> m_road;
	int *m_path;
private:
	void IntToVector(int dest, int start);
public:
	// 清空图
	void Clear();
	// 重置所有属性

};

