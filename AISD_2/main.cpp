#include "MyTree.h"
#include <fstream>
// <Required>

void forIter_1(MyTree<int> m) 
{
	m.updateForIterator();

	auto it = m.begin();
	int ch = -1;
	int count = m.size(), pos = 1;

	do
	{
		system("cls");
		cout << "��������: " << endl;
		cout << "1. ���������� �������� �� ������" << endl;
		cout << "2. ���������� �������� �� �����" << endl;
		cout << "3. ������������� ��������" << endl;
		cout << "4. ���������������� ��������" << endl;
		cout << "5. ������������ ��������" << endl;
		cout << "6. ����� � ������� ����" << endl;

		cin >> ch;

		system("cls");

		switch (ch)
		{
		case 1: {
		
			it = m.begin();
			pos = 1;
		
		}break;
		case 2: {
			it = m.end();
			pos = count + 1;
		}break;
		case 3: {

			++it;
			
			pos++;

		}break;
		case 4: {
			--it;
			pos--;
		}break;
		case 5: {
		
			if (!(pos > 0 && pos <= count))
				cout << "NULL" << endl;
			else
				cout << "����: " << (*it)->key << "\n��������: " << (*it)->val << endl;

			system("pause");
		}break;
		case 6: break;
		default: {
			cout << "������ ������ ��� � ����" << endl; 
			system("pause");
		} break;
		}

	} while (ch != 6);

}

void forIter_2(MyTree<int> m)
{
	m.updateForIterator();

	auto it = m.rbegin();
	int ch = -1;
	int count = m.size(), pos = 1;

	do
	{
		system("cls");
		cout << "��������: " << endl;
		cout << "1. ���������� �������� �� ������" << endl;
		cout << "2. ���������� �������� �� �����" << endl;
		cout << "3. ������������� ��������" << endl;
		cout << "4. ���������������� ��������" << endl;
		cout << "5. ������������ ��������" << endl;
		cout << "6. ����� � ������� ����" << endl;

		cin >> ch;

		system("cls");

		switch (ch)
		{
		case 1: {

			it = m.rbegin();
			pos = 1;

		}break;
		case 2: {
			it = m.rend();
			pos = count + 1;
		}break;
		case 3: {

			++it;

			pos++;

		}break;
		case 4: {
			--it;
			pos--;
		}break;
		case 5: {

			if (!(pos > 0 && pos <= count))
				cout << "NULL" << endl;
			else
				cout << "����: " << (*it)->key << "\n��������: " << (*it)->val << endl;

			system("pause");
		}break;
		case 6: break;
		default: {
			cout << "������ ������ ��� � ����" << endl;
			system("pause");
		} break;
		}

	} while (ch != 6);
}

void forTest()
{
	cout << "�����!" << endl;
	ofstream sl_i("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/sl_i.txt"),
		sl_r("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/sl_r.txt"),
		sl_v("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/sl_v.txt"),
		vr_i("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/vr_i.txt"),
		vr_r("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/vr_r.txt"),
		vr_v("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/vr_v.txt");



	int av_s[3] = { 0, 0 ,0 }, av_v[3] = { 0, 0, 0 };

	for (int i = 1; i < 16; i++)
	{
		cout << "����������� " << i << " ����" << endl;
		for (int j = 0; j < 5; j++)
		{
			MyTree<int> sl;

			for (int k = 0; k < pow(2, i) - 1; k++)
			{
				if (!sl.insert(rand() % 10, rand() % int(pow(2, i) + 10)))
					k--;
			}

			int key = rand() % int(pow(2, i) + 10);
			while (!sl.insert(rand() % 10, key))
				key = rand() % int(pow(2, i) + 10);

			av_s[0] += sl.GetCountView();

			sl.value(key);

			av_s[1] += sl.GetCountView();

			sl.remove(key);

			av_s[2] += sl.GetCountView();
		}

		for (int j = 0; j < 5; j++)
		{
			MyTree<int> sl;
			int k = 0;
			for (k = 0; k < pow(2, i) - 1; k++)
				sl.insert(rand() % 10, k);

			k++;
			sl.insert(rand() % 10, k);

			av_v[0] += sl.GetCountView();

			sl.value(k);

			av_v[1] += sl.GetCountView();

			sl.remove(k);

			av_v[2] += sl.GetCountView();
		}


		for (int j = 0; j < 3; j++)
		{
			av_s[j] /= 5;
			av_v[j] /= 5;
		}

		sl_i << av_s[0] << endl;
		sl_r << av_s[2] << endl;
		sl_v << av_s[1] << endl;

		vr_i << av_v[0] << endl;
		vr_r << av_v[2] << endl;
		vr_v << av_v[1] << endl;

		cout << "�����!" << endl << endl;

	}

}

void menu()
{
	int ch = -1, size = 0, tmpC = 0, tt, tk;
	MyTree<int> m;

	cout << "��������! � ���� ������� ����� ����� ����� ����� �����,\n� ��������� �� ������������� �������� �������� �� 0\n" << endl;



	do
	{
		cout << "������� ������ ������: ";
		cin >> size;

		if (size <= 0)
		{
			cout << "������������ ������, ������� ����� ������ 0" << endl;
			system("pause");
		}
		
		system("cls");

	} while (size <= 0);


	do
	{
		cout << "��� ����� ��������� ������?" << endl;
		cout << "1. ���������� �������" << endl;
		cout << "2. �������" << endl;

		cin >> ch;

		if (ch < 1 || ch > 2)
		{
			cout << "����������� ������ �����" << endl;
			system("pause");
		}

		system("cls");

	} while (ch < 1 || ch > 2);

	if (ch == 1)
	{
		tmpC = 0;
		m.insert(-1, 10);

		for (int i = 1; i < size; i++)
		{
			if (!m.insert(rand() % 10, rand() % (size + 10)))
				i--;
			else
				tmpC += m.GetCountView();
		}
	}
	else
	{
		tmpC = 0;
		cout << "������� �������� " << size << " ���:" << endl;

		for (int i = 0; i < size; i++)
		{
			cin >> tt;
			m.insert(tt, i);
			tmpC += m.GetCountView();
		}
	}

	cout << "�������� ������� ���������!" << endl;
	cout << "����� ����� ���������: " << tmpC << endl;
	system("pause");
	
	do
	{
		system("cls");

		cout << "�������� �����: " << endl;
		cout << "-1. ������������ ��������" << endl;
		cout << "1. �������� ��������" << endl;
		cout << "2. ������� �� �����" << endl;
		cout << "3. �������� �������� �� �����" << endl;
		cout << "4. ��������� ������ �� ���������� ���������" << endl;
		cout << "5. ���������� ��������� � ������" << endl;
		cout << "6. �������� ������� �� �����" << endl;
		cout << "7. ������� ������" << endl;
		cout << "8. ������� �����" << endl;
		cout << "9. ������� ����� ������ ���������" << endl;
		cout << "10. �������� ������" << endl;
		cout << "11. �������� � �����������" << endl;
		cout << "12. �����" << endl;

		cin >> ch;
		system("cls");

		switch (ch)
		{
		case -1: forTest(); break;
		case 1: {

			cout << "������� ����������� �������: ";
			cin >> tt;

			cout << "������� ����: ";
			cin >> tk;

			bool f = m.insert(tt, tk);

			if (f)
				cout << "������� �������� �������!" << endl;
			else
				cout << "������� ��� ����� ������ ��� ���� ���\n��� ����� ����� ��� ������" << endl;
			
			cout << "����� ���������: " << m.GetCountView() << endl;

			system("pause");

		}break;
		case 2: {

			cout << "������� ����: ";
			cin >> tk;

			bool f = m.remove(tk);

			if (!f)
				cout << "�������� �� ���������, ������ ����� ���" << endl;
			else
				cout << "������� ������� ������" << endl;

			cout << "����� ���������: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 3: {

			cout << "������� ����: ";
			cin >> tk;

			int* v = m.value(tk);

			if (v == NULL)
				cout << "������ ����� ��� � ������" << endl;
			else
				cout << "������� ��� ������ " << tk << " ����� " << *v << endl;

			cout << "����� ���������: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 4: {

			if (m.isEmpty())
				cout << "������ �����" << endl;
			else
				cout << "� ������ ���� ��������" << endl;

			cout << "����� ���������: " << m.GetCountView() << endl;

			system("pause");

		}break;
		case 5: {

			cout << "���������� ��������� � ������: " << m.size() << endl;

			cout << "����� ���������: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 6: {

			cout << "������� ����� �������: ";
			cin >> tt;
			cout << "������� ����: ";
			cin >> tk;

			if (m.changeElement(tt, tk))
				cout << "������� ������� ������" << endl;
			else
				cout << "������ ����� ���" << endl;

			cout << "����� ���������: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 7: {

			m.print();
			cout << endl;
			cout << "����� ���������: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 8: {
		
			m.printKey();

			cout << endl << "����� ���������: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 9: {

			cout << "������� ����: " << endl;
			cin >> tk;

			cout << "���������� ������: " << m.extraQ(tk) << endl;
			cout << "����� ���������: " << m.GetCountView() << endl;

			system("pause");

		}break;
		case 10: {
		
			m.clear();

			cout << "������ �������!" << endl;
			cout << "����� ���������: " << m.GetCountView() << endl;
			system("pause");
		
		} break;
		case 11: {
		
			do
			{
				cout << "� ����� ���������� ��������?" << endl;
				cout << "1. ������" << endl;
				cout << "2. ��������" << endl;

				cin >> ch;

				if (ch < 1 || ch > 2)
				{
					cout << "������� ������ ����� ����" << endl;
					system("pause");
				}

				system("cls");

			} while (ch < 1 || ch > 2);

			if (ch == 1)
				forIter_1(m);
			else
				forIter_2(m);
		
		}break;
		case 12: break;
		default:{
			cout << "����������� ������ �����, ����������� �����" << endl;
		}break;
		}

	} while (ch != 12);
}

int main()
{	
	system("chcp 1251");
	system("cls");

	menu();

	return 0;
}