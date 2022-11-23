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
		cout << "Дейсвтия: " << endl;
		cout << "1. Установить итератор на начало" << endl;
		cout << "2. Установить итератор на конец" << endl;
		cout << "3. Инкремеровать итератор" << endl;
		cout << "4. Декрементировать итератор" << endl;
		cout << "5. Разыменовать итератор" << endl;
		cout << "6. Выйти в главное меню" << endl;

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
				cout << "Ключ: " << (*it)->key << "\nЗначение: " << (*it)->val << endl;

			system("pause");
		}break;
		case 6: break;
		default: {
			cout << "Такого пункта нет в меню" << endl; 
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
		cout << "Дейсвтия: " << endl;
		cout << "1. Установить итератор на начало" << endl;
		cout << "2. Установить итератор на конец" << endl;
		cout << "3. Инкремеровать итератор" << endl;
		cout << "4. Декрементировать итератор" << endl;
		cout << "5. Разыменовать итератор" << endl;
		cout << "6. Выйти в главное меню" << endl;

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
				cout << "Ключ: " << (*it)->key << "\nЗначение: " << (*it)->val << endl;

			system("pause");
		}break;
		case 6: break;
		default: {
			cout << "Такого пункта нет в меню" << endl;
			system("pause");
		} break;
		}

	} while (ch != 6);
}

void menu()
{
	int ch = -1, size = 0, tmpC = 0, tt, tk;
	MyTree<int> m;

	cout << "ВНИМАНИЕ! У всех дробных чисел будет взята целая часть,\nа остальные не целочисленные элементы заменены на 0\n" << endl;



	do
	{
		cout << "Введите размер дерева: ";
		cin >> size;

		if (size <= 0)
		{
			cout << "Недопустимый размер, введите число больше 0" << endl;
			system("pause");
		}
		
		system("cls");

	} while (size <= 0);


	do
	{
		cout << "Как будем заполнять дерево?" << endl;
		cout << "1. Случайными цифрами" << endl;
		cout << "2. Вручную" << endl;

		cin >> ch;

		if (ch < 1 || ch > 2)
		{
			cout << "Неккоректно выбран пункт" << endl;
			system("pause");
		}

		system("cls");

	} while (ch < 1 || ch > 2);

	if (ch == 1)
	{
		tmpC = 0;
		for (int i = 0; i < size; i++)
		{
			m.insert(rand() % 10, i);
			tmpC += m.GetCountView();
		}
	}
	else
	{
		tmpC = 0;
		cout << "Вводите элементы " << size << " раз:" << endl;

		for (int i = 0; i < size; i++)
		{
			cin >> tt;
			m.insert(tt, i);
			tmpC += m.GetCountView();
		}
	}

	cout << "Элементы успешно вставлены!" << endl;
	cout << "Общее число обращений: " << tmpC << endl;
	system("pause");
	
	do
	{
		system("cls");

		cout << "Выберете пункт: " << endl;
		cout << "1. Вставить значение" << endl;
		cout << "2. Удалить по ключу" << endl;
		cout << "3. Получить значение по ключу" << endl;
		cout << "4. Проверить дерево на содержание элементов" << endl;
		cout << "5. Количество элементов в дереве" << endl;
		cout << "6. Изменить элемент по ключу" << endl;
		cout << "7. Вывести дерево" << endl;
		cout << "8. Вывести ключи" << endl;
		cout << "9. Вывести ключи больше заданного" << endl;
		cout << "10. Очистить дерево" << endl;
		cout << "11. Работать с итераторами" << endl;
		cout << "12. Выход" << endl;

		cin >> ch;
		system("cls");

		switch (ch)
		{
		case 1: {

			cout << "Введите вставляемый элемент: ";
			cin >> tt;

			cout << "Введите ключ: ";
			cin >> tk;

			bool f = m.insert(tt, tk);

			if (f)
				cout << "Эдемент вставлен успешно!" << endl;
			else
				cout << "Элемент под таким ключем уже есть или\nдля этого ключа нет предка" << endl;
			
			cout << "Число обращений: " << m.GetCountView() << endl;

			system("pause");

		}break;
		case 2: {

			cout << "Введите ключ: ";
			cin >> tk;

			int* re = m.remove(tk);

			if (re == NULL)
				cout << "Удаление не произошло, такого ключа нет" << endl;
			else
				cout << "Элемент успешно удален" << endl;

			cout << "Число обращений: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 3: {

			cout << "Введите ключ: ";
			cin >> tk;

			int* v = m.value(tk);

			if (v == NULL)
				cout << "Такого ключа нет в дереве" << endl;
			else
				cout << "Элемент под ключем " << tk << " равен " << *v << endl;

			cout << "Число обращений: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 4: {

			if (m.isEmpty())
				cout << "Дерево пусто" << endl;
			else
				cout << "В дереве есть элементы" << endl;

			cout << "Число обращений: " << m.GetCountView() << endl;

			system("pause");

		}break;
		case 5: {

			cout << "Количество элементов в дереве: " << m.size() << endl;

			cout << "Число обращений: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 6: {

			cout << "Введите новый элемент: ";
			cin >> tt;
			cout << "Ввежите ключ: ";
			cin >> tk;

			if (m.changeElement(tt, tk))
				cout << "Элемент успешно изменён" << endl;
			else
				cout << "Такого ключа нет" << endl;

			cout << "Число обращений: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 7: {

			m.print();
			cout << endl;
			cout << "Число обращений: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 8: {
		
			m.printKey();

			cout << endl << "Число обращений: " << m.GetCountView() << endl;
			system("pause");

		}break;
		case 9: {

			cout << "Введите ключ: " << endl;
			cin >> tk;

			cout << "Количество ключей: " << m.extraQ(tk) << endl;
			cout << "Число обращений: " << m.GetCountView() << endl;

			system("pause");

		}break;
		case 10: {
		
			m.clear();

			cout << "Дерево очищено!" << endl;
			cout << "Число обращений: " << m.GetCountView() << endl;
			system("pause");
		
		} break;
		case 11: {
		
			do
			{
				cout << "С каким итератором работаем?" << endl;
				cout << "1. Прямой" << endl;
				cout << "2. Обратный" << endl;

				cin >> ch;

				if (ch < 1 || ch > 2)
				{
					cout << "Неверно выбран пункт меню" << endl;
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
			cout << "Некорректно выбран пункт, попытайтесь снова" << endl;
		}break;
		}

	} while (ch != 12);
}

void forTest()
{
	cout << "123321" << endl;
	ofstream sl_i("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/sl_i.txt"),
		sl_r("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/sl_r.txt"),
		vr_i("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/vr_i.txt"),
		vr_r("D:/FFFFFFFFFFFFFFFFFFFFFFFFFFFF/vr_r.txt");

	MyTree<int> sl;
	
	for (int i = 1; i <= 19; i++)
	{
		int tmp_c = 0;
		sl.clear();

		for (int j = 0; j < pow(2, i); j++)
		{
			sl.insert(rand() % 100, j);
			tmp_c += sl.GetCountView();
		}

		sl_i << tmp_c << endl;

		sl.remove(pow(2, i) / 2);
		tmp_c = sl.GetCountView();

		sl_r << tmp_c << endl;
	}

	for (int i = 1; i <= 19; i++)
	{
		int tmp_c = 0;
		sl.clear();

		for (int j = 0; j < pow(2, i); j++)
		{
			sl.insert(rand() % 100, pow(2, j) - 1);
			tmp_c += sl.GetCountView();
		}

		vr_i << tmp_c << endl;

		sl.remove(pow(2, i) / 2 - 1);

		tmp_c = sl.GetCountView();

		vr_r << tmp_c << endl;
	}

}

int main()
{	
	system("chcp 1251");
	system("cls");

	if (true)
	{
		menu();
	}
	else
		forTest();

	return 0;
}