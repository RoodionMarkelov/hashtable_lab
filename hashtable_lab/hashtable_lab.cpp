// hashtable_lab.cpp: определяет точку входа для приложения.
//

#include "hashtable_lab.h"

using namespace std;

int main()
{
	/////////////////////////////////////////////////////
	// TEST CLASS
	/////////////////////////////////////////////////////
	HashTable<int, int> hashtable_1(4);
	hashtable_1.print();
	hashtable_1.insert(0, 2);
	hashtable_1.insert(43684578, 17);
	hashtable_1.insert(436848, 6);
	hashtable_1.insert(26507, 5);
	hashtable_1.insert(26, 7);
	hashtable_1.print();

	cout << "Search " << hashtable_1.search(0) << ' ' << hashtable_1.search(25) << endl;
	cout << "Contains:" << hashtable_1.contains(2) << ' ' << hashtable_1.contains(10004) << endl;


	hashtable_1.insert_or_assign(6, 5);
	hashtable_1.insert_or_assign(26, 101);
	hashtable_1.print();


	hashtable_1.erase(26);
	hashtable_1.erase(25);
	hashtable_1.print();


	cout << "Copy " << endl;
	HashTable<int, int> hashtable_2(hashtable_1);
	hashtable_2.print();


	cout << "Operator = " << endl;
	HashTable<int, int> hashtable_3 = hashtable_1;
	hashtable_3.print();


	HashTable<int, int> hashtable_4(64, 0, 1000, -100, 0);
	hashtable_4.print();


	HashTable<double, int> hashtable_double_int(8, 1, 100, 4.0, 20.0);
	hashtable_double_int.print();


	HashTable<double, double> hashtable_double_double(8, 1.0, 100.0, 4.0, 20.0);
	hashtable_double_double.print();

	///////////////////////////////////////////
	// Count function Test
	///////////////////////////////////////////

	HashTable<int, int> for_count(16);
	for_count.print();

	for_count.insert(0, 1);
	for_count.insert(2976934, 2);
	for_count.insert(38686791, 3);
	for_count.insert(1547732, 4);
	for_count.insert(4362, 5);
	for_count.insert(559794, 6);
	for_count.insert(6799767, 7);
	for_count.insert(7687691, 8);
	for_count.insert(845782, 9);
	for_count.insert(8063467, 10);
	for_count.insert(6868, 11);
	for_count.insert(1669600989, 12);
	for_count.insert(17815, 13);
	for_count.insert(151455, 14);
	for_count.print();

	cout << "Count: " << for_count.count(1669600989) << ' ' << for_count.count(1) << endl <<
		"Count: " << for_count.Hash(4362) << ' ' << for_count.Hash(2976934) << ' ' << for_count.Hash(0) << ' ' 
		<< for_count.Hash(6799767) << ' ' << for_count.count(4362) << endl << endl;

	//////////////////////////////////////////////////////////
	// Task
	//////////////////////////////////////////////////////////

	/*cout << "Task: " << endl << endl;

	size_t size = 23;
	for (size_t i = 25; i <= 475; i += 50) {
		HashTable<int, int> hashtable_fot_task(i, size, -10000, 10000, 0, 1000000000);
		int count_of_collisions = 0;
		for (size_t j = 0; j < i; ++j) {
			if (hashtable_fot_task[j]._flag != 0) {
				if (hashtable_fot_task.count(hashtable_fot_task[j]._pair._key) > 0) {
					count_of_collisions++;
				}
			}
		}
		cout << "Capacity: " << i << " count_of_collisions = " << count_of_collisions << endl;
	}*/


	return 0;
}
