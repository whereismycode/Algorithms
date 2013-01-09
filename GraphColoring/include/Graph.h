/*
 * ============================================================================
 * This file contains implementation of Graph data structure and graph coloring
 * algorithm.
 * Copyright (C) 2013 Shashank (shash2k5@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * ============================================================================
 */
#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include <list>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <set>
#include <cstdlib>

// Namespace Graphs
namespace Graphs {
/*
 * ============================================================================
 * Class Graph declaration
 * ============================================================================
 */
template<class T>
class Graph {
	vector<list<size_t> *> adj_list;
	vector<T> vertexList;
public:
	Graph(int n);
	~Graph();
	bool isEmpty();
	void addEdge(T key1, T key2);
	void printAllTest(ostream& os);
	int getChromaticNumber(bool isRandomizedRLF);
private:
	int getVertexWithMaxDegree(set<int> s, bool visited[], int degree[], bool isRandomizedRLF);
};
/*
 *============================================================================
 * Constructor
 *============================================================================
 */
template<class T>
Graph<T>::Graph(int numOfVertices){
	// For convenience let the first list be null, so that
	// key == index or position
	adj_list.push_back(NULL);

	for(int i = 1; i <= numOfVertices; i++) {
		adj_list.push_back(new list<size_t>());
	}
}
/*
 *============================================================================
 * Destructor
 *============================================================================
 */
template<class T>
Graph<T>::~Graph(){
	// For convenience let the first list be null, so that
	// key == index or position
	adj_list.push_back(NULL);

	for(int i = 1; i < adj_list.size(); i++) {
		delete adj_list[i];
	}
}

/*
 *============================================================================
 * Function Name : isEmpty()
 * returns if the graph is empty
 *============================================================================
 */
template<class T>
bool Graph<T>::isEmpty(){
	return adj_list.size()-1;
}
/*
 *============================================================================
 * Function Name : getVertexWithMaxDegree()
 *
 *============================================================================
 */
template<class T>
int Graph<T>::getVertexWithMaxDegree(set<int> s, bool visited[], int degreeList[],
											     bool isRandomizedRLF){
	set<int>::iterator it = s.begin();
	int maxSoFar = -1;
	int vmx=0;
	if(isRandomizedRLF){
		int rvmx;
		do{
			rvmx = rand() % adj_list.size();
		}while(visited[rvmx] == true);
		return rvmx;
	}
	for(; it != s.end(); it++){
		int degree = degreeList[*it];
		if(degree > maxSoFar){
			maxSoFar = degree;
			vmx = *it;
		}
	}
	return vmx;
}
/*
 *============================================================================
 * Function Name : getChromaticNumber()
 *
 *============================================================================
 */
template<class T>
int Graph<T>::getChromaticNumber(bool isRandomizedRLF){
	set<int> vertexSet;
	set<int> colorSet;
	srand ( time(NULL) );

	int n = adj_list.size();
	int dl1[n];
	int dl2[n];
	for(int i = 1; i < n; i++){
		vertexSet.insert(i);
		dl1[i] = adj_list[i]->size();;
	}

	int colorCount = 1;
	bool visited[n];
	while(!vertexSet.empty()){
		set<int> lvs(vertexSet);
		for(int i = 0; i < n; i++){
			dl2[i] = -1;
			visited[i] = true;
		}
		set<int>::iterator si = vertexSet.begin();
		for(;si != vertexSet.end(); si++){
			dl2[*si] = dl1[*si];
			visited[*si] = false;
		}
		while(!lvs.empty()){
			int vertexNum = getVertexWithMaxDegree(lvs, visited, dl2, isRandomizedRLF);
			lvs.erase(vertexNum);
			dl2[vertexNum] = -1;
			dl1[vertexNum] = -1;
			visited[vertexNum] = true;
			list<size_t> *l = adj_list[vertexNum];
			class list<T>::iterator it = l->begin();
			for(;it != l->end(); it++){
				lvs.erase(*it);
				dl2[*it]--;
				dl1[*it]--;
				visited[*it] = true;
			}
			vertexSet.erase(vertexNum);
		}
		colorSet.insert(colorCount);
		colorCount++;
	}
	return colorSet.size();
}
/*
 *============================================================================
 * Function Name : addEdge()
 *
 *============================================================================
 */
template<class T>
void Graph<T>::addEdge(T key1, T key2){
	if(key1 > adj_list.size() || key2 > adj_list.size()){
		return;
	}

	adj_list[key1]->push_back(key2);
	return;
}
/*
 *============================================================================
 * Function Name : printAllTest()
 *
 *============================================================================
 */
template<class T>
void Graph<T>::printAllTest(ostream& out){
	int n = adj_list.size();

	for(int i = 1; i < n; i++){
		list<T> *l = adj_list[i];
		if(!l->size())
			continue;
		class list<T>::iterator it = l->begin();
		out << i << " ";
		for(;it != l->end();it++)
			out << *it <<" ";
		out << endl;
	}
}
//=============================== End of class ================================
};

#endif /* GRAPH_H_ */
