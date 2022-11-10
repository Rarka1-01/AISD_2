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
		root = NULL;
	}
	
	MyTree(T a)
	{
		root = new node<T>(a, 0);
	}

	MyTree(MyTree& r)
	{

	}

	int size()
	{
		return sz(root) - 1;
	}

	void clear()
	{
		clr(root);
		root = NULL;
	}

	bool isEmpty();

	bool changeElement(T nEl, int key);

	T* value(int key)
	{
		if (seekKey(key))
		{
			stack<int> k = getStackKeys(key);
			node<T>* tmp = root;

			while (!k.empty())
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

	bool remove(int key)
	{
		if (seekKey(key) == 0)
			return false;
		else
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
			
			if (key != 0)
			{
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
				}
				else if (kid->right == NULL && kid->left != NULL)
				{
					switch (a)
					{
					case 1: tmp->right = kid->left; break;
					case -1: tmp->left = kid->left;  break;
					}

					delete kid;
					updateKeys(root);
				}
				else if (kid->right != NULL && kid->left == NULL)
				{
					switch (a)
					{
					case 1: tmp->right = kid->right; break;
					case -1: tmp->left = kid->right;  break;
					}

					delete kid;
					updateKeys(root);
				}
				else
				{
					node<T>* ins = kid->left;

					switch (a)
					{
					case 1: tmp->right = kid->right; break;
					case -1: tmp->left = kid->right; break;
					}

					delete kid;

					updateKeys(root);

					toStackVal(ins);

					while (!vlsTmp.empty())
					{
						this->insert(vlsTmp.front(), getFirstFreeKey());
						vlsTmp.pop();
					}
				}

			}
			else
			{
				toStackVal(root);
				vlsTmp.pop();

				this->clear();
				int i = 0;
				while (!vlsTmp.empty())
				{
					this->insert(vlsTmp.front(), i);
					i++;
					vlsTmp.pop();
				}
			}
			return true;
		}
	}

	void printKey()
	{
		prK(root);
	}

	void print()
	{
		if (root == NULL)
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
	queue<T> vlsTmp;

	void clr(node<T>* tmp)
	{
		
		if (tmp->left != NULL)
			clr(tmp->left);

		if (tmp->right != NULL)
			clr(tmp->right);

		delete tmp;
	
	}

	int getFirstFreeKey()
	{
		int i = 0;
		while (seekKey(i))
			i++;

		return i;
	}

	void toStackVal(node<T>* tmp)
	{
		if (tmp == NULL)
			return;
		else
			vlsTmp.push(tmp->val);

		toStackVal(tmp->right);
		toStackVal(tmp->left);
	}

	int sz(node<T>* tmp)
	{
		if (tmp == 0)
			return 1;
		else
			return sz(tmp->left) + sz(tmp->right);
	}

	void updateKeys(node<T>* tmp, int pr = 0, int s = 0)
	{
		if (tmp == NULL)
			return;
		else
			tmp->key = pr * 2 + s;

		updateKeys(tmp->left, tmp->key, 1);
		updateKeys(tmp->right, tmp->key, 2);
	}

	void pr(node<T>* tmp, int n = 0)
	{
		if (tmp != NULL)
		{
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
			cout << tmp->key << " ";
			if (tmp->left != NULL)
				cout << tmp->left->key << " ";
			else
				cout << "N ";

			if (tmp->right != NULL)
				cout << tmp->right->key << " ";
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

		do
		{
			k.push(tK);

			tK = (tK - 2 + (tK % 2)) / 2;

		} while (tK > 0);

		while (!k.empty() && f)
		{

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