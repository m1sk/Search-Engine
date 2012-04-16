#include "triesite.h"
#include <iostream>

using namespace std;
using namespace Library;

int main()
{
	cout << "Hello, world" << endl;
	triesite site = triesite("C:\\Users\\Micha\\Desktop\\temp",'c');
	site.mount("C:\\Users\\Micha\\Desktop\\temp");
	int x;
	cin >> x;
	return 0;
}