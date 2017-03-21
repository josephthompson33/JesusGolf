

 
 /**
 *Joseph Thompson
 *This program takes a url and a target word from the user
 *and checks the webpages of the url for the target, if
 * the target is not found, the program then follows either
 *breadth first search or depth first search(designated by the
 *user) to search other webpages that the original url has 
 *links to.
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
