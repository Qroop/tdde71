#include <iostream>
#include "Expression.h"

using namespace std;
int main()
{
	string line;
	while ( getline(cin, line) ) {
		Expression e{line};

	 	cout << e.to_string() << " "
		<< e.evaluate() << endl;
	}
	return 0;
}
