#include "table.h"

int table::hash_func(int key)
{
	return key % SIZE;
}

table::table()
{
	for (int i = 0; i < SIZE; i++)
	{
		mas[i] = nullptr;
	}
}

table::~table()
{
	for (int i = 0; i < SIZE; i++)
	{
		if (mas[i] != nullptr) {
			delete mas[i];
			mas[i] = nullptr;
		}
	}
}

void table::add(info* inf)
{
	int pos = hash_func(inf->key);
	if (mas[pos] != nullptr) {
		int i = 1;
		while (mas[pos] != nullptr)
		{
			if (mas[pos]->busy == 0)
				break;

			pos = hash_func(inf->key + i);
			i++;
		}
	}
	if (mas[pos] != nullptr)
		delete mas[pos];

	mas[pos] = inf;
}

info* table::find(int key)
{
	int pos = hash_func(key);
	int i = 1;
	while (mas[pos] != nullptr)
	{
		if (mas[pos]->key == key && mas[pos]->busy == 1)
			break;

		pos = hash_func(key + i);
		i++;
	}

	return mas[pos];
}

bool table::remove(int key)
{
	info* p = find(key);
	if (p != nullptr) {
		p->busy = 0;
		return true;
	}
	else {
		return false;
	}
}

void table::clear_deleted()
{
	info** ar = new info * [SIZE];
	int count = 0;

	for (int i = 0; i < SIZE; i++)
	{
		if (mas[i] != nullptr) {
			if (mas[i]->busy == 0)
				delete mas[i];
			else {
				ar[count] = mas[i];
				count++;
			}
		}
		mas[i] = nullptr;
	}

	for (int i = 0; i < count; i++) {
		add(ar[i]);
	}

	delete[] ar;
}

//void table::clear_deleted()
//{
//	table t;
//	for (int i = 0; i < SIZE; i++)
//	{
//		if (mas[i] != nullptr) {
//			if (mas[i]->busy == 0) {
//				delete mas[i];
//				mas[i] = nullptr;
//			}
//			else {
//				t.add(mas[i]);
//			}
//		}
//	}
//	for (int i = 0; i < SIZE; i++) {
//		if (t.mas[i] != nullptr)
//			mas[i] = new info(*(t.mas[i]));
//		else
//			mas[i] = nullptr;
//	}
//}

ostream& operator<<(ostream& out, const table& t)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (t.mas[i] != nullptr && t.mas[i]->busy == 1) {
			out << "Key = " << t.mas[i]->key << ", Data = " << t.mas[i]->data << endl;
		}
		else {
			out << "NULL" << endl;
		}
	}
	return out;
}
