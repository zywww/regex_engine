#include <cstdlib>
#include <iostream>
#include "Parser.h"

using std::endl;
using std::cout;
using std::cin;

int main()
{
	Parser p("(b*(a|3)*|c)*ss"); 
	p.Parse();

	system("pause");
	return 0;
}