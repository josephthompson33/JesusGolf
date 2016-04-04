//class urlgraph
// will hold a graph of the urls found while searching for a word or phrase
//Joseph thompson
//November 2 2015
//joseph thompson


#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iterator>
//#include <curl/curl.h>
#include <map>

using namespace std; 
#ifndef URLgraph_h
#define URLgraph_h

class URLgraph{
public: 
	URLgraph();
	vector<string> getNeighbors(string url);
	void setNeighbors(string url, vector<string> neighbors);
	int length();
	void printAll();
	bool contains(string key);
	
	

private:
	map<string, vector<string> > graph;//this will hold all of the urls and their neighbors
};
#endif