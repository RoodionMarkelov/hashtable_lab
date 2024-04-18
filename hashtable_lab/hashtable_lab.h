#pragma once

#include <iostream>
#include <cmath>
#include <random>
#define A 30000
#define L 14
#define WORD_LENGHT sizeof(int)*8

using namespace std;

template <typename K, typename T>
struct Pair {
	K _key;
	T _value;
	Pair(K key, T value) : _key(key), _value(value) {}
};

template <typename K, typename T>
struct Node {
	Pair<K, T> _pair;
	int _flag;
	Node() : _pair(Pair<K, T>(0, 0)), _flag(0) {}
	Node(Pair<K, T> pair, int flag) : _pair(pair), _flag(flag) {}
};

template <typename K, typename T>
class HashTable {
	int _capacity;
	int _size;
	Node<K, T>* _ht;

	void clear() {
		_size = 0;
		_capacity = 0;
		delete _ht;
	}

	int Hash(K key) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		int tmp = key * A;
		int result = ((result >> L) | (result << WORD_LENGHT - L));
		return result % _capacity;
	}

	void clear() {
		_size = 0;
		_capacity = 0;
		delete _ht;
	}

public:
	int get_size() {
		return _size;
	}

	int get_capacity() {
		return _capacity;
	}

	HashTable(int capasity) : _capacity(capasity), _size(0) {
		_ht = new Node<K, T>[capasity];
	}

	HashTable(const HashTable<K, T> other) {
		HashTable<K, T> new_ht(other._capacity);
		for (int i = 0; i < _capacity; ++i) {
			if (other._ht[i]._flag == 1) {
				new_ht.insert(other._ht[i]._pair._key, other._ht[i]._pair._value);
			}
		}
		delete _ht;
		_ht = new_ht._ht;
		_capacity = other._capacity;
		_size = other._size;
	}

	HashTable operator=(const HashTable other) {
		HashTable new_ht(other);
		auto tmp = new_ht._ht;
		delete new_ht._ht;
		_ht = new_ht._ht;
		_capacity = other._capacity;
		_size = other._size;
	}

	~HashTable() {
		clear();
	}

	void print() const {
		if (_size == 0) {
			cout << "Hastable is empty." << endl;
			return;
		}
		cout << "Index and value of Hastable:" << endl;
		for (int i = 0; i < _capacity; ++i) {
			if (_ht[i]._flag == 1) {
				cout << "[" << i << "] : " << _ht[i]._pair._value << endl;
			}
		}
		cout << endl;
	}

	bool contains(T value) const {
		if (_size == 0) return false;
		for (int i = 0; i < _size; ++i) {
			if (_ht[i]._pair._value == value) {
				return true;
			}
		}
		return false;
	}

	T* search(K key) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		int index = Hash(key);
		if (_ht[index]._flag == 1 && ht[index]._pair._key == key) {
			return new ht[index]._pair._value;
		}
		if (_ht[index]._flag != 0) {
			int start_index = index;
			int  i = 1;
			do {
				index = (Hash(key) + i) % _size;
				i++;
				if (index == start_index) {
					return nullptr;
				}
			} while (_ht[index]._flag != 0 && (_ht[index]._flag == 2 || _ht[index]._pair._key != key));
			if (_ht[index]._flag != 1) return nullptr;

			else {
				T* element = new _ht[index]._pair._value;
				return element;
			}
		}
		else return nullptr;
	}

	void insert(K key, T value) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		if (_size == _capacity) {
			_capacity = _capacity * 2;
			HashTable<K, T> new_ht(_capacity);
			for (int i = 0; i < _capacity; ++i) {
				if (_ht[i]._flag == 1) {
					new_ht.insert(_ht[i]._pair._key, _ht[i]._pair._value);
				}
			}
			delete _ht;
			_ht = new_ht._ht;
		}
		int index = Hash(key);
		if (_ht[index]._flag == 1) {
			int  i = 1;
			do {
				index = (Hash(key) + i) % _size;
				i++;
			} while (_ht[index]._flag != 0);
		}
		_ht[index]._pair = Pair(key, value);
		_ht[index]._flag = 1;
		_size++;
	}

	void insert_or_assign(K key, T value) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		int index = Hash(key);
		if (_ht[index]._flag != 1) {
			_ht[index]._pair = Pair(key, value);
			_ht[index]._flag = 1;
			_size++;
		}
		else {
			_ht[index]._pair = Pair(key, value);
		}
	}

	bool erase(K key) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		int index = Hash(key);
		if (_ht[index]._flag == 0) return false;
		int start_index = index;
		int  i = 1;
		do {
			if (_ht[index]._flag == 1 && _ht[index]._pair._key == key) {
				_ht[index]._flag = 2;
				_size--;
				return true;
			}
			index = (Hash(key) + i) % _size;
			i++;
			if (index == start_index) {
				return false;
			}
		} while (_ht[index]._flag != 0);
		return false;
	}

	int count(K key) {
		int count = 0;
		int index = Hash(key);
		int start_index = index;
		int  i = 1;
		do {
			if (_ht[index]._flag == 1 && _ht[index]._pair._key == key) {
				return count;
			}
			index = (Hash(key) + i) % _size;
			i++;
			if (index == start_index) {
				return false;
			}
		} while (_ht[index]._pair != 0 && _ht[index]._pair._key != key);
	}
};

