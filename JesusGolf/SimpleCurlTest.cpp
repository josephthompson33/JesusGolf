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

#include <string>
#include <iostream>
#include <vector>
#include "SimpleCurl.h"
 #include "URLgraph.h"

using namespace std;

int main(int argc, char *argv[])
{
	/** one way to use SimpleCurl: via a constuctor. Give a string and it
	  tries to retrieve the document.
	  **/
	SimpleCurl httpGrabber(argv[1]);
	string doc = httpGrabber.getRetrievedDocument();
	cout << doc << endl;

    /** Here is a second way -- the more likely way you'll use it.
        After creating an httpGrabber, invoke the getURL method.
        It returns -1 on failure.
        **/
	if (httpGrabber.getURL(argv[1]) !=-1){
        	cout << httpGrabber.getRetrievedDocument() << endl;
        }
	else{
		cout << "Could not retrieve document" << endl;
	}
	vector<string> output = httpGrabber.find_urls(httpGrabber.getRetrievedDocument());
	for(int i = 0;i<output.size();i++){
		cout<<output[i]<<endl;
	}

}
