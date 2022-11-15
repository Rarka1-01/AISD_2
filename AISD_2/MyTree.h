#pragma once
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
struct node {
	T val;
	int key;
	node* right;
	node* left;

public:
	node(T a, int k)
	{
		val = a;
		key = k;
		right = NULL;
		left = NULL;
	}
};

template <typename T>
class MyTree 
{
public:
	
	MyTree()
	{
		this->cr = 1;
		root = NULL;
	}
	
	MyTree(T a)
	{
		root = new node<T>(a, 0);
		this->cr = 1;
	}

	MyTree(MyTree& r)
	{
		this->cr = 0;
		root = copy(root, r.root);
	}

	~MyTree()
	{
		this->clear();
	}

	int size()
	{
		this->cr = 0;
		return sz(root) - 1;
	}

	void clear()
	{
		clr(root);
		root = NULL;
	}

	bool isEmpty()
	{
		this->cr++;
		return root == NULL;
	}

	bool changeElement(T nEl, int key)
	{
		if (!seekKey(key))
			return false;
		else
		{
			stack<int> k = getStackKeys(key);
			node<T>* tmp = root;

			while (!k.empty() && k.top() != 0)
			{
				if (k.top() % 2 == 0)
					tmp = tmp->right;
				else
					tmp = tmp->left;

				k.pop();
			}

			tmp->val = nEl;
			return true;
		}
	}

	T* value(int key)
	{
		if (seekKey(key))
		{
			stack<int> k = getStackKeys(key);
			node<T>* tmp = root;

			while (!k.empty() && k.top() != 0)
			{
				if (k.top() % 2 == 0)
					tmp = tmp->right;
				else
					tmp = tmp->left;

				k.pop();
			}
			
			return &(tmp->val);
		}
		else
			return NULL;
	}

	bool insert(T nEl, int key)
	{
		if (root == NULL && key == 0)
		{
			root = new node<T>(nEl, key);
			return true;
		}
		else if (root == NULL)
			return false;

		if (!(seekKey(key) == 0 && seekKey((key - 2 + (key % 2)) / 2) == 1))
			return false;
		else
		{
			stack<int> k;
			int tK = key;

			while (tK != 0)
			{
				tK = (tK - 2 + (tK % 2)) / 2;
				k.push(tK);
			}

			k.pop();

			node<T>* tmp = root;

			while (!k.empty())
			{
				if (k.top() % 2 == 0)
					tmp = tmp->right;
				else
					tmp = tmp->left;

				k.pop();
			}

			if (key % 2 == 0)
				tmp->right = new node<T>(nEl, key);
			else
				tmp->left = new node<T>(nEl, key);

			return true;
		}
	}

	int* remove(int key)
	{
		int* keys = new int[2];
		if (seekKey(key) == 0)
			return NULL;
		else
		{
			keys[0] = key;
			
			if (key != 0)
			{
				stack<int> k = getStackKeys(key);
				int a = 0; // -1 = left, 1 = right
				node<T>* tmp = root;
				node<T>* kid;

				while (k.top() != key)
				{
					if (k.top() % 2 == 0)
						tmp = tmp->right;
					else
						tmp = tmp->left;

					k.pop();
				}

				if (key % 2 == 0)
				{
					kid = tmp->right;
					a = 1;
				}
				else
				{
					kid = tmp->left;
					a = -1;
				}

				if (kid->right == NULL && kid->left == NULL)
				{
					delete kid;
					switch (a)
					{
					case 1: tmp->right = NULL; break;
					case -1: tmp->left = NULL;  break;
					}

					keys[1] = -1;
				}
				else if (kid->right == NULL && kid->left != NULL)
				{
					keys[1] = kid->left->key;

					switch (a)
					{
					case 1: tmp->right = kid->left; tmp->right->key = keys[0]; break;
					case -1: tmp->left = kid->left; tmp->left->key = keys[0]; break;
					}

					delete kid;
				}
				else if (kid->right != NULL && kid->left == NULL)
				{
					keys[1] = kid->right->key;

					switch (a)
					{
					case 1: tmp->right = kid->right; tmp->right->key = keys[0]; break;
					case -1: tmp->left = kid->right; tmp->left->key = keys[0]; break;
					}

					delete kid;
				}
				else
				{
					node<T>* nt = kid->left;
					node<T>* preNT = NULL;

					while (!(nt->right == NULL && nt->left == NULL))
					{
						preNT = nt;
						if (nt->left != NULL)
							nt = nt->left;
						else
							nt = nt->right;
					}

					if(preNT != NULL)
						if (preNT->left == nt)
							preNT->left = NULL;
						else
							preNT->right = NULL;

					nt->right = kid->right;

					if (kid->left != nt)
						nt->left = kid->left;

					keys[1] = nt->key;

					delete kid;

					switch (a)
					{
					case 1: tmp->right = nt; tmp->right->key = keys[0]; break;
					case -1: tmp->left = nt; tmp->left->key = keys[0]; break;
					}

				}

				
			}
			else
			{
				if (root->left == NULL && root->right == NULL)
				{
					delete root;
					root = NULL;
					keys[1] = -1;
				}
				else if (root->left == NULL && root->right != NULL)
				{
					node<T>* tmp = root->right;
					delete root;
					keys[1] = tmp->key;
					root = tmp;
					root->key = keys[0];
					keys[1] = tmp->key;
				}
				else if (root->left != NULL && root->right == NULL)
				{
					node<T>* tmp = root->left;
					delete root;
					keys[1] = tmp->key;
					root = tmp;
					root->key = keys[0];
				}
				else
				{
					node<T>* nt = root->left;
					node<T>* preNT = NULL;

					while (!(nt->left == NULL && nt->right == NULL))
					{
						preNT = nt;

						if (nt->left != NULL)
							nt = nt->left;
						else
							nt = nt->right;
					}

					if(preNT != NULL)
						if (preNT->left == nt)
							preNT->left = NULL;
						else
							preNT->right = NULL;

					nt->right = root->right;

					if(root->left != nt)
						nt->left = root->left;

					delete root;

					keys[1] = nt->key;

					root = nt;
					root->key = keys[0];
					
				}
			}

			return keys;
		}
	}

	void printKey()
	{
		this->cr = 0;
		if (this->isEmpty())
			cout << "Tree is empty!" << endl;
		else
			prK(root);
	}

	void print()
	{
		this->cr = 0;
		if (this->isEmpty())
			cout << "Tree is empty!" << endl;
		else
			pr(root);
		cout << endl;
	}

	int extraQ(int key);

	//ÈÒÅÐÎÒÎÐÛ!

	int GetCountView()
	{
		return this->cr;
	}

private:
	node<T>* root;
	int cr;

	node<T>* copy(node<T>* r1, node<T>* r2)
	{
		if (r2 != NULL)
		{
			this->cr++;
			r1 = new node<T>(r2->val, r2->key);

			r1->left = copy(r1->left, r2->left);
			r1->right = copy(r1->right, r2->right);

			return r1;
		}
		else
			return NULL;
	}

	void clr(node<T>* tmp)
	{
		if (tmp != NULL)
		{
			this->cr++;
			if (tmp->left != NULL)
				clr(tmp->left);

			if (tmp->right != NULL)
				clr(tmp->right);

			delete tmp;
		}
	
	}

	int sz(node<T>* tmp)
	{
		if (tmp == NULL)
			return 1;
		else
		{
			this->cr++;
			return sz(tmp->left) + sz(tmp->right);
		}
	}

	void pr(node<T>* tmp, int n = 0)
	{
		if (tmp != NULL)
		{
			this->cr++;
			pr(tmp->right, n + 5);

			for (int i = 0; i < n; i++)
				cout << " ";
			cout << tmp->val << endl;
			pr(tmp->left, n + 5);
		}
	}

	void prK(node<T>* tmp)
	{
		if (tmp == NULL)
			return;
		else
		{
			this->cr++;
			cout << tmp->key << " ";

			if (tmp->left != NULL)
			{
				cout << tmp->left->key << " ";
				this->cr++;
			}
			else
				cout << "N ";

			if (tmp->right != NULL)
			{
				cout << tmp->right->key << " ";
				this->cr++;
			}
			else
				cout << "N ";

			cout << endl;
		}

		prK(tmp->left);
		prK(tmp->right);
	}

	bool seekKey(int key)
	{
		stack<int> k;
		int tK = key;
		bool f = true;
		node<T>* tmp = root;
		this->cr++;

		do
		{
			k.push(tK);

			tK = (tK - 2 + (tK % 2)) / 2;

		} while (tK > 0);

		while (!k.empty() && f)
		{
			this->cr++;
			if (tmp == NULL)
			{
				f = false;
				break;
			}

			if(k.top() != 0)
				if (k.top() % 2 == 0)
					tmp = tmp->right;
				else
					tmp = tmp->left;

			k.pop();
		}

		if (tmp == NULL || key < 0)
			f = false;
		
		if (root == NULL)
			f = false;

		return f;
	}

	stack<int> getStackKeys(int key)
	{
		stack<int> k;
		int tK = key;

		do
		{
			k.push(tK);

			tK = (tK - 2 + (tK % 2)) / 2;

		} while (tK > 0);

		return k;
	}
};