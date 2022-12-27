#pragma once
#define SIZE 10
#include <iostream>
using namespace std;

struct info
{
	int busy;
	int key;
	char data[100];
};

class table
{
private:
	info* mas[SIZE];
	int hash_func(int key);

public:
	table();
	~table();

	void add(info* inf);
	info* find(int key);
	bool remove(int key);
	void clear_deleted();
	friend ostream& operator<<(ostream& out, const table& t);
};

