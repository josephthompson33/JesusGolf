//Joseph Thompson
//this will be a graph holding URL vertices
//the edges will be held in a vector of strings


#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iterator>
//#include <curl/curl.h>
#include <map>
#include "URLgraph.h"

using namespace std;

	URLgraph::URLgraph(){
		map<string, vector<string> > graph;
	}  
	void URLgraph::setNeighbors(string url, vector<string> neighbors){
		graph[url] = neighbors;
	}
	vector<string> URLgraph::getNeighbors(string url){
		return graph[url];
	}
	int URLgraph::length(){
		return graph.size();
	}
	void URLgraph::printAll(){
		typedef map<string, vector<string> >::const_iterator it;
		for(it b = graph.begin();b != graph.end(); b++){
			cout<<b->first<<endl;//prints the URL keys in the map 
		}
	}
	/**
		this method will chek if the map contains a certain url and return true if it does
	**/
	bool URLgraph::contains(string key){
		if(graph.count(key)){
			return true;
		}
		return false;
	}