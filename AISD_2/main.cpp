#include "MyTree.h"
// <Required>

int main()
{
	MyTree<int> m;
	
	for (int i = 0; i < 16; i++)
		m.insert(-(rand() % 10), i);

	m.print();
	cout << endl;
	m.remove(0);
	cout << endl;
	m.print();

	return 0;
}