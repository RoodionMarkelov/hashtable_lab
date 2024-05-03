#pragma once

#include <iostream>
#include <cmath>
#include <random>
#define WORD_LENGHT sizeof(size_t)*8

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
	~Node() = default;
};

template <typename K, typename T>
class HashTable {

public:
	size_t _capacity;
	size_t _size;
	Node<K, T>* _ht;

	void _swap(HashTable<K, T>& other) noexcept {
		std::swap(_capacity, other._capacity);
		std::swap(_size, other._size);
		std::swap(_ht, other._ht);
	}

	size_t Hash(K key) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		size_t a = 27510;
		size_t l = 27;
		size_t tmp = size_t((key * a)) % size_t(pow(2, 64));
		size_t result = ((tmp >> l) | (tmp << WORD_LENGHT - l));
		return result % _capacity;
	}

	size_t get_size() const{
		return _size;
	}

	size_t get_capacity() const {
		return _capacity;
	}

	HashTable(size_t capasity) : _capacity(capasity), _size(0) {
		_ht = new Node<K, T>[capasity];
	}

	HashTable(size_t capacity, T min_value, T max_value, K k_min, K k_max) {
		_capacity = capacity;
		_size = 0;
		_ht = new Node<K, T>[_capacity];
		for (size_t i = 0; i < _capacity; ++i) {
			K key = (K)(k_min + (double)(rand()) / RAND_MAX * (k_max - k_min + 1));
			if (key < 0) {
				key = abs(key);
			}
			T value = (T)(min_value + (double)(rand()) / RAND_MAX * (max_value - min_value + 1));
			insert(key, value);
		}
	}

	HashTable(size_t capacity, size_t size, T min_value, T max_value, K k_min, K k_max) {
		_capacity = capacity;
		_size = 0;
		_ht = new Node<K, T>[_capacity];
		for (size_t i = 0; i < size; ++i) {
			K key = (K)(k_min + (double)(rand()) / RAND_MAX * (k_max - k_min + 1));
			if (key < 0) {
				key = abs(key);
			}
			T value = (T)(min_value + (double)(rand()) / RAND_MAX * (max_value - min_value + 1));
			insert(key, value);
		}
	}

	HashTable(const HashTable<K, T>& other) {
		_capacity = other._capacity;
		_size = other._size;
		_ht = new Node<K, T>[_capacity];
		for (size_t i = 0; i < _capacity; ++i){
			if (other._ht[i]._flag == 1) {
				_ht[i]._pair = Pair(other._ht[i]._pair._key, other._ht[i]._pair._value);
				_ht[i]._flag = 1;
			}
		}
	}

	HashTable<K,T> operator=(const HashTable<K, T>& other) {
		HashTable<K, T> copy(other);
		copy._swap(*this);
		return *this;
	}

	Node<K, T>& operator[](const size_t index) {
		return _ht[index];
	}

	~HashTable() {
		_capacity = 0;
		_size = 0;
		delete[] _ht;
	}

	void print() const {
		if (_size == 0) {
			cout << "Hastable is empty." << endl << endl;
			return;
		}
		cout << "capacity = " << _capacity << " " << "size = " << _size << endl;
		cout << "Index and value of Hastable:" << endl;
		for (size_t i = 0; i < _capacity; ++i) {
			if (_ht[i]._flag == 1) {
				cout << "[" << i << "] : " << _ht[i]._pair._value << endl;
			}
		}
		cout << endl;
	}

	bool contains(T value) {
		if (_size == 0) return false;
		for (size_t i = 0; i < _size; ++i) {
			if (_ht[i]._pair._value == value) {
				return true;
			}
		}
		return false;
	}

	/*bool contains(K key) {
		if (_size == 0) return false;
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		size_t index = Hash(key);
		if (_ht[index]._flag == 1 && _ht[index]._pair._key == key) {
			return true;
		}
		if (_ht[index]._flag != 0 && _ht[index]._pair._key != key) {
			size_t start_index = index;
			size_t  i = 1;
			do {
				index = (Hash(key) + i) % _capacity;
				i++;
				if (index == start_index) {
					return false;
				}
			} while (_ht[index]._flag != 0 && (_ht[index]._flag == 2 || _ht[index]._pair._key != key));

			if (_ht[index]._flag == 0) return false;

			else {
				return true;
			}
		}
		else return false;
	}*/

	T* search(K key) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		size_t index = Hash(key);
		if (_ht[index]._flag == 1 && _ht[index]._pair._key == key) {
			return &_ht[index]._pair._value;
		}
		if (_ht[index]._flag != 0 && _ht[index]._pair._key != key) {
			size_t start_index = index;
			size_t  i = 1;
			do {
				index = (Hash(key) + i) % _capacity;
				i++;
				if (index == start_index) {
					return nullptr;
				}
			} while (_ht[index]._flag != 0 && (_ht[index]._flag == 2 || _ht[index]._pair._key != key));

			if (_ht[index]._flag == 0) return nullptr;

			else {
				return &_ht[index]._pair._value;
			}
		}
		else return nullptr;
	}

	void insert(K key, T value) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		if (_size == _capacity) {
			_capacity =_capacity * 2;
			HashTable<K, T> new_ht(_capacity);
			for (size_t i = 0; i < _capacity; ++i) {
				if (_ht[i]._flag == 1) {
					new_ht.insert(_ht[i]._pair._key, _ht[i]._pair._value);
				}
			}
			new_ht._swap(*this);
		}
		size_t index = Hash(key);
		if (_ht[index]._flag == 1) {
			size_t  i = 1;
			do {
				index = (Hash(key) + i) % _capacity;
				i++;
			} while (_ht[index]._flag == 1);
		}
		_ht[index]._pair = Pair(key, value);
		_ht[index]._flag = 1;
		_size++;
	}

	void insert_or_assign(K key, T value) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		size_t index = Hash(key);
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
		size_t index = Hash(key);
		if (_ht[index]._flag == 0) return false;
		size_t start_index = index;
		size_t  i = 1;
		do {
			if (_ht[index]._flag == 1 && _ht[index]._pair._key == key) {
				_ht[index]._flag = 2;
				_size--;
				return true;
			}
			index = (Hash(key) + i) % _capacity;
			i++;
			if (index == start_index) {
				return false;
			}
		} while (_ht[index]._flag != 0);
		return false;
	}

	int count(K key) {
		if (key < 0) throw runtime_error("Key cann`t be neggative.");
		int count = 0;
		size_t index = Hash(key);
		if (_ht[index]._flag == 1 && _ht[index]._pair._key == key) {
			return 0;
		}
		if (_ht[index]._flag != 0 && _ht[index]._pair._key != key) {
			size_t start_index = index;
			size_t  i = 1;
			do {
				if (Hash(_ht[index]._pair._key) == Hash(key)) count++;
				index = (Hash(key) + i) % _capacity;
				i++;
				if (index == start_index) {
					return 0;
				}
			} while (_ht[index]._flag != 0 && (_ht[index]._flag == 2 || _ht[index]._pair._key != key));
			if (_ht[index]._flag == 0) return 0;
			else return count;
		}
	}

};

