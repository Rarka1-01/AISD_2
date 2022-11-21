#include "MyTree.h"
#include <fstream>
// <Required>

int main()
{	
	MyTree<int> m;
	int n = 16;

	for (int i = 0; i < n; i++)
		m.insert(i, i);

	m.updateForIterator();
	m.print();

	for (auto i = m.rbegin(); i != m.rend(); ++i)
		cout << (*i)->val << " ";

	return 0;
}