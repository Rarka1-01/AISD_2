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
		*root = NULL;
	}

	MyTree(T a)
	{
		*root = new node<T>(a, 0);
		this->cr = 1;
	}

	MyTree(MyTree& r)
	{
		this->cr = 0;
		*root = copy(*root, *r.root);
	}

	~MyTree()
	{
		this->cr = 0;
		this->clear();
	}

	int size()
	{
		this->cr = 0;
		return sz(*root) - 1;
	}

	void clear()
	{
		this->cr = 1;
		this->updateForIterator();
		
		for (int i = 0; i < this->itn; i++)
			delete arr[i];

		delete arr;

		*root = NULL;
	}

	bool isEmpty()
	{
		this->cr++;
		return (*root) == NULL;
	}

	bool changeElement(T nEl, int key)
	{
		this->cr = 1;

		if (root == NULL)
			return false;
		else
		{
			node<T>* tmp = *root;
			int st = 0;

			while (tmp != NULL && tmp->key != key)
			{
				if (key > tmp->key)
				{
					tmp = tmp->right;
					this->cr++;
				}
				else if (key < tmp->key)
				{
					tmp = tmp->left;
					this->cr++;
				}
				else
					break;
			}

			if (tmp == NULL)
				return false;
			else
			{
				tmp->val = nEl;
				return true;
			}
		}
		
		
	}

	T* value(int key)
	{
		this->cr = 1;

		if (root == NULL)
			return NULL;
		else
		{
			node<T>* tmp = *root;
			int st = 0;

			while (tmp != NULL && tmp->key != key)
			{
				if (key > tmp->key)
				{
					tmp = tmp->right;
					this->cr++;
				}
				else if (key < tmp->key)
				{
					tmp = tmp->left;
					this->cr++;
				}
				else
					break;
			}

			if (tmp == NULL)
				return NULL;
			else
				return &(tmp->val);

		}
		
	}

	bool insert(T nEl, int key)
	{
		this->cr = 0;

		if (*root == NULL)
		{
			*root = new node<T>(nEl, key);
			this->cr++;
		}
		else
		{
			node<T>* tmp = *root, * pre = *root;
			int st = 0;

			while (tmp != NULL)
			{
				pre = tmp;
				if (key > tmp->key)
				{
					tmp = tmp->right;
					st = 1;
					this->cr++;
				}
				else if (key < tmp->key)
				{
					tmp = tmp->left;
					st = -1;
					this->cr++;
				}
				else
					return false;
			}

			if (st == 1)
				pre->right = new node<T>(nEl, key);
			else
				pre->left = new node<T>(nEl, key);

			this->cr++;
		}
		return true;
	}

	bool remove(int key)
	{
		this->cr = 0;

		node<T>* curNode = *this->root;
		node<T>* pred;

		while (curNode != NULL && curNode->key != key) {
			pred = curNode;
			if (key < curNode->key) {
				curNode = curNode->left;
			}
			else {
				curNode = curNode->right;
			}
			this->cr++;
		}
		if (curNode == NULL) {
			return false;
		}


		node<T>* x;
			
		if (curNode->left == NULL && curNode->right == NULL) {
			x = NULL;

		}
		else {
			bool flag = true;
			if (curNode->left == NULL) {
				x = curNode->right;
				this->cr++;
				flag = false;
			}
			else {
				if (curNode->right == NULL) {
					x = curNode->left;
					this->cr++;
					flag = false;
				}
			}
			if (flag) {
				pred = curNode;
				node<T>* y = curNode->right;
				while (y->left != NULL) {
					pred = y;
					y = y->left;
					this->cr++;
				}
				curNode->key = y->key;
				curNode->val = y->val;
				this->cr++;
				x = y->right;
				curNode = y;
			}
		}

		if (pred != NULL) {
			if (curNode->key < pred->key) {
				pred->left = x;
			}
			else {
				pred->right = x;
			}
		}
		return true;
	}
	
	void printKey()
	{
		this->cr = 0;
		if (this->isEmpty())
			cout << "Tree is empty!" << endl;
		else
			prK(*root);
	}

	void print()
	{
		this->cr = 0;
		if (this->isEmpty())
			cout << "Tree is empty!" << endl;
		else
			pr(*root);
		cout << endl;
	}

	int extraQ(int key)
	{
		int count = 0;

		updateForIterator();

		for (auto i = this->begin(); i != this->end(); ++i)
			if ((*i)->key > key)
				count++;

		return count;
	}

	//----------------------------------------------
	void updateForIterator()
	{
		this->arr = (node<T>**)malloc(this->size() * sizeof(node<T>*));
		this->itn = 0;
		treeToArray(*this->root);
	}
	
	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using defferance_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = node<T>**;
		using reference = node<T>*;

		Iterator(pointer ptr) :m_ptr(ptr) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		Iterator& operator++() { m_ptr++; return *this; }
		Iterator& operator--() { m_ptr--; return *this; }

		friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };


	private:
		pointer m_ptr;
	};

	struct RIterator
	{
		using iterator_category = std::forward_iterator_tag;
		using defferance_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = node<T>**;
		using reference = node<T>*;

		RIterator(pointer ptr) :m_ptr(ptr) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		RIterator& operator--() { m_ptr++; return *this; }
		RIterator& operator++() { m_ptr--; return *this; }

		friend bool operator==(const RIterator& a, const RIterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!=(const RIterator& a, const RIterator& b) { return a.m_ptr != b.m_ptr; };


	private:
		pointer m_ptr;
	};

	Iterator begin()
	{
		return Iterator(&(this->arr[0]));
	}

	Iterator end()
	{
		int s = size();
		return Iterator(&(this->arr[s]));
	}

	RIterator rbegin()
	{
		int s = size();
		return RIterator(&(this->arr[s - 1]));
	}

	RIterator rend()
	{
		return RIterator(&(this->arr[-1]));
	}
	//----------------------------------------------

	int GetCountView()
	{
		return this->cr;
	}

private:
	node<T>** root = new node<T>*;
	node<T>** arr;
	int itn = 0;
	int cr;

	void treeToArray(node<T>* tmp)
	{
		if (tmp != NULL)
		{
			treeToArray(tmp->left);
			this->arr[itn] = tmp;
			itn++;
			treeToArray(tmp->right);
		}
	}

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
		else
		{
			for (int i = 0; i < n; i++)
				cout << " ";
			cout << "N" << endl;
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

};