/**
All code here adapted (modified as little as possible) from 
www.luckyspin.org
Adaptation by Gary Lewandowski, 14 October 2007.

Original header comments follow.
**/

/*
 * This is a very simple example of how to use libcurl from within 
 * a C++  program. The basic idea is that you want to retrieve the 
 * contents of a web page as a string. Obviously, you can replace 
 * the buffer object with anything you want and adjust elsewhere 
 * accordingly.
 * 
 * Hope you find it useful..
 * 
 * Todd Papaioannou 
 */
 
 /**
 *Joseph Thompson
 *ive altered simplecurltest to suit my needs
**/


#include "JesusGolf.h"

using namespace std;

int main(int argc, char *argv[])
{
	int x;
	JesusGolf theGame = JesusGolf(argv[1]);
	cout<<" breadth first search or depth first search? enter a positive int for BFS, a zero or negative for DFS"<<endl;
	cin>>x;
	if(x>0){
		theGame.BFS();
	}
	else if(x<=0){
		theGame.DFS();
	}
	
	return 0;
}
