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
		this->cr = 0;
		this->clear();
	}

	int size()
	{
		this->cr = 0;
		return sz(root) - 1;
	}

	void clear()
	{
		this->cr = 1;
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
		this->cr = 0;

		if (!seekKey(key))
			return false;
		else
		{
			stack<int> k = getStackKeys(key);
			this->cr++;
			node<T>* tmp = root;

			while (!k.empty() && k.top() != 0)
			{
				this->cr++;
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
		this->cr = 0;

		if (seekKey(key))
		{
			stack<int> k = getStackKeys(key);
			node<T>* tmp = root;

			while (!k.empty() && k.top() != 0)
			{
				this->cr++;
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
		this->cr = 1;

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
				this->cr++;
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
			this->cr++;
			return true;
		}
	}

	int* remove(int key)
	{
		this->cr = 0;
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
					this->cr++;
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

				this->cr++;

				if (kid->right == NULL && kid->left == NULL)
				{
					delete kid;
					switch (a)
					{
					case 1: tmp->right = NULL; break;
					case -1: tmp->left = NULL;  break;
					}
					this->cr++;
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
					this->cr++;
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
					this->cr++;
					delete kid;
				}
				else
				{
					node<T>* nt = kid->left;
					node<T>* preNT = NULL;

					while (!(nt->right == NULL && nt->left == NULL))
					{
						this->cr++;
						preNT = nt;
						if (nt->left != NULL)
							nt = nt->left;
						else
							nt = nt->right;
					}

					if (preNT != NULL)
					{
						if (preNT->left == nt)
							preNT->left = NULL;
						else
							preNT->right = NULL;
						this->cr++;
					}

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
					this->cr++;
				}

				
			}
			else
			{
				if (root->left == NULL && root->right == NULL)
				{
					delete root;
					root = NULL;
					keys[1] = -1;
					this->cr++;
				}
				else if (root->left == NULL && root->right != NULL)
				{
					node<T>* tmp = root->right;
					delete root;
					keys[1] = tmp->key;
					root = tmp;
					root->key = keys[0];
					keys[1] = tmp->key;
					this->cr += 2;
				}
				else if (root->left != NULL && root->right == NULL)
				{
					node<T>* tmp = root->left;
					delete root;
					keys[1] = tmp->key;
					root = tmp;
					root->key = keys[0];
					this->cr += 2;
				}
				else
				{
					node<T>* nt = root->left;
					node<T>* preNT = NULL;

					while (!(nt->left == NULL && nt->right == NULL))
					{
						this->cr++;
						preNT = nt;

						if (nt->left != NULL)
							nt = nt->left;
						else
							nt = nt->right;
					}

					if (preNT != NULL)
					{
						if (preNT->left == nt)
							preNT->left = NULL;
						else
							preNT->right = NULL;
						this->cr++;
					}

					nt->right = root->right;
					this->cr++;

					if(root->left != nt)
						nt->left = root->left;

					delete root;

					keys[1] = nt->key;

					root = nt;
					root->key = keys[0];
					this->cr++;
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

	int extraQ(int key)
	{
		this->cr = 0;
		int lvl = -1;
		
		do
		{
			lvl++;
		} while (!(pow(2, lvl) - 1 <= key && pow(2,lvl+1) - 2 >= key));
		
		int left = pow(2, lvl) - 1, right = pow(2, lvl + 1) - 2, size_arr = right - left + 1;

		node<T>** tmp = (node<T>**)malloc(sizeof(node<T>*) * size_arr);

		for (int i = left; i <= right; i++)
			tmp[i - left] = seekReturn(i);
		
		int count = 0;

		for (int i = 0; i < size_arr; i++)
			if (tmp[i] != NULL)
				if (tmp[i]->key <= key)
					count += sz(tmp[i]) - 2;
				else
					count += sz(tmp[i]) - 1;

		return count;
	}

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

		this->cr++;
		if (tmp == NULL || key < 0)
			f = false;
		
		this->cr++;
		if (root == NULL)
			f = false;

		return f;
	}

	node<T>* seekReturn(int key)
	{
		stack<int> k = getStackKeys(key);
		
		node<T>* tmp = this->root;

		if (key == 0)
			return tmp;

		this->cr++;

		while (tmp != NULL && !k.empty())
		{
			this->cr++;
			if (k.top() % 2 == 0)
				tmp = tmp->right;
			else
				tmp = tmp->left;

			k.pop();
		}

		return tmp;
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