#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "table.h"
using namespace std;

info* create_info() {
	info* inf = new info();
	inf->busy = 1;
	cout << "Введите ключ ";
	cin >> inf->key;
	cout << "Введите данные: ";
	cin.ignore();
	cin.getline(inf->data, 100);
	return inf;
}

int main()
{
	setlocale(LC_ALL, "rus");

	{
		table t;
		int action;

		do
		{
			cout << "1.Добавить данные" << endl;
			cout << "2.Поиск по ключу" << endl;
			cout << "3.Вывод таблицы" << endl;
			cout << "4.Удаление по ключу" << endl;
			cout << "5.Очистка от удаленных" << endl;
			cout << "0.Выход" << endl;

			cin >> action;

			if (action == 1) {
				info* inf = create_info();
				t.add(inf);
			}
			else if (action == 2) {
				int key;
				cout << "Введите ключ: ";
				cin >> key;

				info* inf = t.find(key);
				if (inf != nullptr) {
					cout << "Запись найдена: " << inf->data << endl;
				}
				else {
					cout << "Нет такой записи" << endl;
				}
			}
			else if (action == 3) {
				cout << t << endl;
			}
			else if (action == 4) {
				int key;
				cout << "Введите ключ: ";
				cin >> key;

				if (t.remove(key)) {
					cout << "Операция успешно выполнена" << endl;
				}
				else {
					cout << "Нет такой записи" << endl;
				}
			}
			else if (action == 5) {
				t.clear_deleted();
			}
		} while (action != 0);

	}

	_CrtDumpMemoryLeaks();
}
