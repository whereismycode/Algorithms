/*
 * ============================================================================
 * This is a driver program to run and profile the Graph Coloring
 * implementation.
 * Copyright (C) 2013 Shashank
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

#include <iostream>
using namespace std;
#include <ctime>
#include "Graph.h"

/*
 *=============================================================================
 * graph_builder creates a graph according to the input file representing a
 * graph
 *=============================================================================
 */
class graph_builder{
	char *path;
	Graphs::Graph<size_t> *g;
public:
	graph_builder(char *str):g(NULL){
		path = new char[strlen(str)];
		strcpy(path, str);
		build_graph();
	}
	Graphs::Graph<size_t> *get_built_graph(){
		return g;
	}
	~graph_builder(){
		delete path;
		delete g;
	}
private:
#define DELIM " "
	int getIntFromString(char *str){
		int value;
		std::istringstream convert(str);
		convert >> value;
		return value;
	}
	void build_graph(){
		ifstream input;
		input.open(path);
		if(!input.good() || input.eof())
			return;

		// Find number of entries
		int n;
		{
			char buf[80];
			input.getline(buf, 80);
			char* token = NULL;
			token = strtok(buf, DELIM);
			if(!token)
				return ;
			n = getIntFromString(token);
		}

		g = new Graphs::Graph<size_t>(n);
		const int max_chars_in_a_line = n*10;
		char buf[max_chars_in_a_line];
		char* token = NULL;;
		int vertexNum;
		while(!input.eof()){
			input.getline(buf, max_chars_in_a_line);
			token = strtok(buf, DELIM);
			if(!token)
				break;
			vertexNum = getIntFromString(token);
			for(int i = 0; ; i++){
				token = strtok(0, DELIM);
				if(!token)
					break;
				int conn = getIntFromString(token);
				g->addEdge(vertexNum, conn);
			}
		}
		input.close();
		return;
	}
};
/*
 *=============================================================================
 * Timer class
 *=============================================================================
 */
class Timer {
	clock_t time;
public:
	Timer():time(0){}
	void start(){
		time = clock();
	}
	void end(){
		time = clock()-time;		
	}
	long getDurationInMilli(){
		return time*((float)1000/CLOCKS_PER_SEC);
	}
};
void printResult(char *str, int cn, long duration){
	cout << str << ": Chromatic number of the input graph = " << cn;
	cout <<  " (" << duration <<" milli seconds)"<<endl;
}
/*
 *=============================================================================
 * main driver program
 *=============================================================================
 */
int main(int argc, char **argv) {
	if(argc < 2){
		cout<< "****Missing input graph file****"<<endl;
		cout<< "Usage - ./gc.out <path to input graph file>"<<endl;
		return 0;
	}

	graph_builder gb(argv[1]);
	Graphs::Graph<size_t> *g = gb.get_built_graph();
	if(g == NULL){
		return 0;
	}

	Timer t;
	t.start();
	int cn = g->getChromaticNumber(false);
	t.end();
	printResult("RLF", cn, t.getDurationInMilli());
	
	t.start();
	cn = g->getChromaticNumber(true);
	t.end();
	printResult("RRLF", cn, t.getDurationInMilli());
	
	return 0;
}
