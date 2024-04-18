// hashtable_lab.cpp: определяет точку входа для приложения.
//

#include "hashtable_lab.h"

using namespace std;

//int hashfun(int key) {
//	if (key < 0) throw runtime_error("Key cann`t be neggative.");
//	int tmp = key * A;
//	int result = ((result >> L) | (result << WORD_LENGHT - L));
//	return result % 2;
//}

int main()
{
	HashTable<int, int> hashtable_1(2);
	hashtable_1.print();
	cout << "capacity = " << hashtable_1.get_capacity() << " " << "size = " << hashtable_1.get_size() << endl;
	hashtable_1.insert(0, 2);
	hashtable_1.insert(1, 3);
	hashtable_1.insert_or_assign(0,2);

	cout << hashtable_1.contains(2) << endl;
	cout << hashtable_1.erase(0) << endl;
	
	hashtable_1.print();
	cout << "capacity = " << hashtable_1.get_capacity() << " " << "size = " << hashtable_1.get_size() << endl;

	/*cout << hashfun(1);*/
}
