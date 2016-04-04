#include <string>
#include <iostream>
#include <vector>

using namespace std;

#ifndef JesusGolf_h
#define JesusGolf_h

class JesusGolf{
	public:
	void BFS();
	JesusGolf(string start);
	void DFS();
	private:
		string startURL;
};
#endif	