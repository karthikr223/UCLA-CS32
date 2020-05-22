#include "Map.h"
#include <iostream>

Map::Map() {
	mapSize = 0;
}

bool Map::empty() const {
	if (mapSize == 0) {
		return true;
	}
	return false;
}

int Map::size() const {
	return mapSize;
}


bool Map::insert(const KeyType& key, const ValueType& value) {
	if (mapSize >= DEFAULT_MAX_ITEMS) {
		return false;
	}
	for (int i = 0; i < mapSize; i++) {
		if (items[i].m_key == key) {
			return false;
		}
	}
	items[mapSize].m_key = key;
	items[mapSize].m_val = value;
	mapSize++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
	for (int i = 0; i < mapSize; i++) {
		if (key == items[i].m_key) {
			items[i].m_val = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
	for (int i = 0; i < mapSize; i++) {
		if (key == items[i].m_key) {
			items[i].m_val = value;
			return true;
		}
	}
	if (mapSize < DEFAULT_MAX_ITEMS) {
		items[mapSize].m_key = key;
		items[mapSize].m_val = value;
		mapSize++;
		return true;
	}
	return false;
}

bool Map::erase(const KeyType& key) {
	for (int i = 0; i < mapSize; i++) {
		if (key == items[i].m_key) {
			for (int j = i; j < mapSize; j++) {
				items[j] = items[j + 1];
			}
			mapSize--;
			return true;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const {
	for (int i = 0; i < mapSize; i++) {
		if (key == items[i].m_key) {
			return true;
		}
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
	for (int i = 0; i < mapSize; i++) {
		if (key == items[i].m_key) {
			value = items[i].m_val;
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
	if (i >= 0 && i < size()) {
		key = items[i].m_key;
		value = items[i].m_val;
		return true;
	}
	return false;
}

void Map::swap(Map& other) {
	MapItem temp[DEFAULT_MAX_ITEMS];

	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		temp[i] = items[i];
		items[i] = other.items[i];
		other.items[i] = temp[i];
	}

	int tempSize = mapSize;
	mapSize = other.size();
	other.mapSize = tempSize;

}