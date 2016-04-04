/**
	my main function was getting crowded 
	the purpose of this class is to play jesus golf given a starting url
	uses breadth-first search
	11/4/2015
	Joseph THompson
**/



#include <string>
#include <iostream>
#include <vector>
#include "SimpleCurl.h"
#include "URLgraph.h"
#include "JesusGolf.h"

using namespace std;

JesusGolf::JesusGolf(string start){
	startURL = start;
}
void JesusGolf::BFS()
{
	bool found = false;
	int pages = 0;// this will hold how many pages have been checked for the target word.
	int k;
	int i = 1;
	int x;//will compare this to level to check if the program has reached max levels
	int levels = 0;//this will represent the current level
	URLgraph graph;//will hold all urls and a vector of their neighbors
	string currentURL = startURL;//the url for which i find a vector of urls found in its html file
	string target;//the word we are searching for in the html file
	vector<string> currentLevel = vector<string>(1,startURL);//holds the urls on the current level of the graph, starts with the command line url
	string path = startURL;//this will hold the path to the current 
	cout<<"how many layers deep shall we venture?give an integer please->";
	cin>>x;
	x++;
	if(x<=0){
		cout<<"that was an invalid integer, i will use 5 instead"<<endl;
		x=5;
	}
	cout<<"what word shall we search for?->";
	cin>>target;
	while(!found&&levels<x){//the x determines how many levels deep it goes
		SimpleCurl httpGrabber(currentURL);
		if (httpGrabber.getURL(currentURL) == -1){
			cout<<"invalid URL"<<endl;
        	return;//cout << httpGrabber.getRetrievedDocument() << endl;
        }
		if(httpGrabber.findTarget(httpGrabber.getRetrievedDocument(), target)){
			cout<<"found target "<<target<<" in "<<currentURL<<endl;
			cout<<"checked these pages:"<<endl;
			graph.printAll();
			cout<<"checked "<<pages<<" pages"<<endl;
			found = true;
			return;
		}
		pages++;
		vector<string> output = httpGrabber.find_urls(httpGrabber.getRetrievedDocument());
		cout<<"the urls connected to "<<currentURL<<" are:"<<endl;
		graph.setNeighbors(currentURL,output);
		for(int j = 0;j<output.size();j++){
			cout<<output[j]<<endl;
			
	    }
		/**
		the following code implements a breadth first search, it only stops working(as far as i know)
		if it runs into an unsupported start of a URL such as app or if it cant resolve hostname
		**/
		
		if(i+1>currentLevel.size()||k==currentLevel.size()){
			i=0;
			vector<string> tempo;
			int a = 0;
		for(int q = 0;q<currentLevel.size();q++){
				SimpleCurl levelSetter(currentLevel[q]);
					
			vector<string> nextLevel = levelSetter.find_urls(levelSetter.getRetrievedDocument());
				a=0;
				while(a<nextLevel.size()){
					tempo.push_back(nextLevel[a]);
					a++;
				}
			}
			if(tempo.empty()){
				cout<<"no more urls to search"<<endl;
				cout<<"target not found"<<endl;
				cout<<"here is a list of all URLs searched:"<<endl;
				graph.printAll();
			}
			k = 0;//reset k if we have a new currentLevel
			levels++;
			cout<<"OXOXOXOXO  now searching level "<<levels<<"    OXOXOXOXO"<<endl;
			currentLevel = tempo;
		}
		/**
		the following code picks the next URL
		it checks if the URL is already a key in the graph,and if the URL contains other URLS
		if a URL is a dead end, it simply skips over it, it is still included in the graph though.
		**/

		string temp = currentURL;
		
		while(currentURL==temp){
			cout<<k<<endl;
			if(k>=currentLevel.size()){
				i=0;
				vector<string> tempo;
				int a = 0;
			
				for(int q = 0;q<currentLevel.size();q++){
					SimpleCurl levelSetter(currentLevel[q]);
					vector<string> nextLevel = levelSetter.find_urls(levelSetter.getRetrievedDocument());
					a=0;
					while(a<nextLevel.size()){
						tempo.push_back(nextLevel[a]);
						a++;
					}
				}
				k = 0;//reset k if we have a new currentLevel
				levels++;
				cout<<"OXOXOXOXO  now searching level "<<levels<<"    OXOXOXOXO"<<endl;
				currentLevel = tempo;
			}
			
			SimpleCurl httpChecker(currentLevel[k]);
			vector<string> checker = httpChecker.find_urls(httpChecker.getRetrievedDocument());
			if(checker.size()<1){
				i++;
			}
			if((checker.size()>=1) && !graph.contains(currentLevel[k])){
				currentURL = currentLevel[k];
			}
			k++;
		}
		i++;
   }
  cout<<"the target was not found, here is a list of the urls visited"<<endl;
  cout<<"the following should be all of the urls i used as currentURL."<<endl;
  cout<<"pages searched: "<<pages<<endl;
  graph.printAll();
}
void JesusGolf::DFS(){
	bool found = false;
	string currentURL = startURL;
	int depth;
	int x = 0;
	URLgraph graph;
	string target;
	cout<<"what word shall we search for?->";
	cin>>target;
	cout<<"how deep shall we search?->";
	cin>>depth;
	while(!found&&depth>x){
		SimpleCurl httpGrabber(currentURL);
		if (httpGrabber.getURL(currentURL) == -1){
			cout<<"invalid URL"<<endl;
        	return;//cout << httpGrabber.getRetrievedDocument() << endl;
        }
        if(httpGrabber.findTarget(httpGrabber.getRetrievedDocument(), target)){
			cout<<"found target "<<target<<" in "<<currentURL<<endl;
			cout<<"the urls visited are"<<endl;
			graph.printAll();
			found = true;
			return;
		}
		vector<string> output = httpGrabber.find_urls(httpGrabber.getRetrievedDocument());
		cout<<"the urls connected to "<<currentURL<<" are:"<<endl;
		graph.setNeighbors(currentURL,output);
		for(int j = 0;j<output.size();j++){
			cout<<output[j]<<endl;
			
	    }
	    int k = 0;
	    string temp = currentURL;
	    while(currentURL==temp){
	    	SimpleCurl httpChecker(output[k]);
	    	vector<string> checker = httpChecker.find_urls(httpChecker.getRetrievedDocument());
	    	if(checker.size()<1){
	    		k++;
	    	}
	    	if((checker.size()>=1) && !graph.contains(output[k])){
				currentURL = output[k];
				x++;
		    }
			if(k>checker.size()){
				cout<<"ran out of urls, ill star over with startURL"<<endl;
				if(currentURL != startURL){
					currentURL = startURL;
				}
				else{
					cout<<"ran out of URLs altogether"<<endl;
					graph.printAll();
					return;
				}
			}
	    }
	}
}