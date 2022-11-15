#include "MyTree.h"
// <Required>

int main()
{
	MyTree<int> m;
	int n = 16;
	for (int i = 0; i < n; i++)
		//m.insert(-(rand() % 10), i);
		m.insert(i, i);

	return 0;
}