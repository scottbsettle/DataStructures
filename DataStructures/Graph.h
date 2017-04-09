#pragma once
#include "DynArray.h"
#include "SLList.h"
#include "DLList.h"
template<typename Type>
class Graph
{
private:
	
public:
	struct Edge
	{
		unsigned int toVertex;
	};

	struct Vertex
	{
		// the data that this vertex is storing
		Type element;
		// the list of edges that connect this vertex to another vertex
		SLList<Edge> edges;
		void addEdge(const unsigned int& toVertex);

	};
private:
	DynArray<Vertex> m_graph;
public:
	unsigned int addVertex(const Type& value);
	Vertex& operator[](const unsigned int& index);
	unsigned int size() const;
	void clear();
	void printBreadthFirst(const unsigned int& startVertex);


};
///////////////////////////////////////////////////////////////////////////
// Function : addEdge
// Parameters : toVertex - the index of the vertex we are adjacent to
///////////////////////////////////////////////////////////////////////////
template<typename Type>
void Graph<Type>::Vertex::addEdge(const unsigned int & toVertex)
{
	Edge _tmp;
	_tmp.toVertex = toVertex;
	edges.addHead(_tmp);
}
/////////////////////////////////////////////////////////////////////////////
// Function : addVertex
// Parameters : value - the data to store in this vertex
// Return : unsigned int - the index this vertex was added at
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
unsigned int Graph<Type>::addVertex(const Type & value)
{
	Vertex _tmp;
	_tmp.element = value;
	m_graph.append(_tmp);
	return m_graph.size() - 1;
}
/////////////////////////////////////////////////////////////////////////////
// Function : operator[]
// Parameters : index - the index in the graph to access
// Return : Vertex& - the vertex stored at the specified index
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
typename Graph<Type>::Vertex & Graph<Type>::operator[](const unsigned int & index)
{
	return m_graph[index];
}
/////////////////////////////////////////////////////////////////////////////
// Function : size
// Return : unsiged int - the number of vertices in the graph
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
unsigned int Graph<Type>::size() const
{
	return m_graph.size();
}
/////////////////////////////////////////////////////////////////////////////
// Function : clear
// Notes : clears the graph and readies it for re-use
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void Graph<Type>::clear()
{
	m_graph.clear();
}
/////////////////////////////////////////////////////////////////////////////
// Function : printBreadthFirst
// Parameters : startVertex - the vertex to start the traversal at
// Notes : prints contents of the graph in depth order 
//			(from closest to farthest)
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void Graph<Type>::printBreadthFirst(const unsigned int & startVertex)
{
	DLList<unsigned int> _tmp;
	DLLIter<unsigned int> _itter(_tmp);
	int* depth = new int[m_graph.GetSize()];
	int x = 0;
	_tmp.addHead(startVertex);
	depth[_tmp.Head()] = 0;

	while (_tmp.size() > 0)
	{
		if (depth[_tmp.Head()] != -1)
		{
			SLLIter<Edge> itter(m_graph[_tmp.Head()].edges);
			itter.begin();
			while (!itter.end())
			{
				if (depth[itter.current().toVertex] != -1)
					depth[itter.current().toVertex] = depth[_tmp.Head() ] + 1;

				_tmp.addTail(itter.current().toVertex);
				++itter;
			}

			cout << m_graph[_tmp.Head()].element << " " << depth[_tmp.Head()] << "\n";
			depth[_tmp.Head()] = -1;
		}
		_itter.beginHead();
		_tmp.remove(_itter);
	}
	delete[] depth;
}
