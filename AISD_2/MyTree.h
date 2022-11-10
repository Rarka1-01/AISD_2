#pragma once
#include <iostream>
#include <stack>

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

	int size();

	void clear();

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
		}
	}

	void printKey()
	{
		prK(root);
	}

	void print()
	{
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

	void pr(node<T>* tmp)
	{
		if (tmp == NULL)
			return;
		else
			cout << tmp->val << " ";

		pr(tmp->left);
		pr(tmp->right);
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