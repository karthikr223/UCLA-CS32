#ifndef MAPH
#define MAPH

#include <iostream>
using KeyType = std::string;
using ValueType = double;
const int DEFAULT_MAX_ITEMS = 250;

class Map
{
public:
	Map();       
	bool empty() const; 
	int size() const;
	bool insert(const KeyType& key, const ValueType& value);
	bool update(const KeyType& key, const ValueType& value);
	bool insertOrUpdate(const KeyType& key, const ValueType& value);
	bool erase(const KeyType& key);
	bool contains(const KeyType& key) const;
	bool get(const KeyType& key, ValueType& value) const;
	bool get(int i, KeyType& key, ValueType& value) const;
	void swap(Map& other);
private:
	struct MapItem {
		KeyType m_key;
		ValueType m_val;
	};
	MapItem items[DEFAULT_MAX_ITEMS];
	int mapSize;
};

#endif
