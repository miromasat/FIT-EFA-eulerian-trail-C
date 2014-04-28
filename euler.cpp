#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <list>
#include <stdint.h>

using namespace std;

class CGraph
{
public:
	CGraph() { m_sizeNodes = 0; m_sizeEdges = 0; }
	~CGraph() { 
		delete [] m_connections;
		delete [] m_edges;
	};

	int validateGrades();
	bool validateBFS();
	bool validateEdge(int a, int b);
	void deleteEdge(int a, int b);
	int validateNode(int a);
	list<int> findTrail();

	
	list<int> m_trail;
	list<int> m_stack;
	vector<int>* m_edges;
	bool* m_connections;
	int m_sizeNodes;
	int m_sizeEdges;
};

bool CGraph::validateEdge(int a, int b)
{
	bool res = false;

	for (unsigned int i = 0; i < m_edges[a].size(); ++i)
	{
		if (m_edges[a][i] == b)
			return true;
	}
		
	
	return res;
}

void CGraph::deleteEdge(int a, int b)
{

	for (unsigned int i = 0; i < m_edges[a].size(); ++i)
	{
		if (m_edges[a][i] == b)
		{
			m_edges[a].erase(m_edges[a].begin() + i);
			break;
		}
	}

	for (unsigned int i = 0; i < m_edges[b].size(); ++i)
	{
		if (m_edges[b][i] == a)
		{
			m_edges[b].erase(m_edges[b].begin() + i);
			break;
		}
	}

}

int CGraph::validateNode(int a)
{
	if ( m_edges[a].size() > 0 )
			return m_edges[a].front();

	return -1;	
}

bool CGraph::validateBFS()
{
	queue<int> Q;
	Q.push(0);
	 
	m_connections[0] = true;
	int nodeCount = 1;
	 
	int n;
	 
	while(Q.size()){
	 n = Q.front();
	 Q.pop();
	 
	 for (unsigned int i = 0; i < m_edges[n].size(); ++i)
	 {
	     if( !m_connections[m_edges[n][i]] ){
	         m_connections[m_edges[n][i]] = true;
	         Q.push(m_edges[n][i]);
	         nodeCount++;
	     }
	 }
	}
	 
	if(nodeCount != m_sizeNodes){
	 return false;
	}

	return true;
}

int CGraph::validateGrades()
{
	int odds = 0;
	int odd = 0;
	for (int i = 0; i < m_sizeNodes; ++i)
		if (m_edges[i].size() % 2 != 0)
		{
			odds++;
			odd = i;
		}
		
	if (odds == 0)
		return 0;

	if (odds == 2)
		return odd;

	return -1;

}

list<int> CGraph::findTrail()
{
	int node, v, start = -1;

	start = validateGrades();
	if (start == -1)
		return m_trail;	

	for (int i = 0; i < m_sizeNodes; ++i)
		m_connections[i] = false;

	if(!validateBFS())
		return m_trail;
	
	
	m_stack.push_back(start);
	while (!m_stack.empty())
	{
		node = m_stack.front();
		v = validateNode(node);

		if ( v != -1)
		{
			m_stack.push_front(v);
			deleteEdge(node, v);
		}else{
			m_trail.push_front(node);
			m_stack.erase (m_stack.begin());
		}
	}

	return m_trail;
}

bool solveGraph( const char * inFile, const char * outFile )
 {
    int u, v;
    CGraph g;
    list<int> trail;

	ifstream read(inFile);
	ofstream write(outFile);

	read >> g.m_sizeNodes;
	read >> g.m_sizeEdges;

	g.m_connections = new bool[g.m_sizeNodes];
	g.m_edges = new vector<int>[g.m_sizeNodes];

	for (int i = 0; i < g.m_sizeEdges; ++i)
	{
		read >> u;
		read >> v;
		g.m_edges[u].push_back( v );
		g.m_edges[v].push_back( u );

	}
			

	trail = g.findTrail();	

	if (!trail.empty())
		for (std::list<int>::iterator it = trail.begin(); it != trail.end(); it++)
    	 	write << *it << endl;

	read.close();
	write.close();

	return true;
 }

int main ( int argc, char * argv [] )
 {
   solveGraph("in.txt", "out.txt");

   return 0;
   
 }
