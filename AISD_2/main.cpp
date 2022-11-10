#include "MyTree.h"

int main()
{
	MyTree<int> m;
	
	for (int i = 0; i < 3; i++)
		m.insert(-(rand() % 10), i);

	m.print();
	cout << endl;
	m.printKey();

	return 0;
}