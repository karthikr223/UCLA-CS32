#include "Map.h"

Map::Map():mapSize(0) {                           //initializes head and tail next and prev pointers to nullptr
	head = new Node;
	head->prev = nullptr;
	tail = new Node;
	head->next = nullptr;
	tail->prev = nullptr;
	tail->next = nullptr;
}

Map::~Map() {                                    
	Node* p = head;
	while (p != nullptr) {                      
		Node* n = p->next;                  //temp pointer n holds the next pointer while the current node is deleted
		delete p;
		p = n;
	}

}

Map::Map(const Map& other):mapSize(0) {
	head = new Node;
	tail = new Node;
	head->prev = nullptr;
	head->next = nullptr;
	tail->prev = nullptr;
	tail->next = nullptr;                            //initializes head and tail next and prev pointers to nullptr
	Node* p = other.head->next;                     //temp pointer starting on the node after the dummy head node 
	for (int i = 0; i < other.mapSize; i++) {
		this->insert(p->m_key, p->m_val);           //inserts into map data from equivalent node in other
		p = p->next;
	}
}

Map& Map::operator = (const Map& rhs) {
	if (this != &rhs) {
		Map temp(rhs);
		swap(temp);
	}
	return *this;
}


bool Map::empty() const{
	if (mapSize == 0)
		return true;
	else
		return false;
}

int Map::size() const {
	return mapSize;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
	if (mapSize == 0) {                         //if map is empty
		Node* item = new Node;                 //create new node, change head and tail pointers, update key and value
		head->next = item;
		tail->prev = item;
		item->next = tail;
		item->prev = head;
		item->m_key = key;
		item->m_val = value;
		mapSize++;
		return true;
	}
	else {
		if (this->contains(key))                       //if key is present, return false	
			return false;
		else {
			Node* item = new Node;                     //if key not present, node added to end of the list by modifying the last node and tail dummy node
			tail->prev->next = item;
			item->prev = tail->prev;
			item->next = tail;
			tail->prev = item;
			item->m_key = key;
			item->m_val = value;
			mapSize++;
			return true;
		}
	}
}

bool Map::update(const KeyType& key, const ValueType& value) {
	Node* t = head->next;
	while (t != nullptr) {
		if (t->m_key == key) {                               //if key present, m_val is modified to value
			t->m_val = value;
			return true;
		}
		t = t->next;
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
	if (mapSize == 0) {                             //if map is empty, use same method as insert to add node
		Node* item = new Node;
		head->next = item;
		tail->prev = item;
		item->next = tail;
		item->prev = head;
		item->m_key = key;
		item->m_val = value;
		mapSize++;
		return true;
	}
	else {
		Node* t = head->next;
		while (t != nullptr) {
			if (t->m_key == key) {                   //if key is present, the corresponding value is updated according to the parameter
				t->m_val = value;
				return true;
			}
			t = t->next;
		}
		Node* item = new Node;                     //if key not present, new node added to the end of the list by modifying the last node next pointer and tail dummy node prev pointer
		tail->prev->next = item;
		item->prev = tail->prev;
		item->next = tail;
		tail->prev = item;
		item->m_key = key;
		item->m_val = value;
		mapSize++;
		return true;
	}
}

bool Map::erase(const KeyType& key) {
	Node* t = head->next;
	while (t != nullptr) {
		if (t->m_key == key) {                                       //once node containing key is found, surrounding nodes are odified to connect to each other and node is deleted
			t->prev->next = t->next;
			t->next->prev = t->prev;
			delete t;
			mapSize--;
			return true;
		}
		t = t->next;
	}
	return false;
}

bool Map::contains(const KeyType& key) const {
	Node* t = head->next;
	while (t != nullptr) {                                    
		if (t->m_key == key) {                        //returns true on finding key in the list
			return true;
		}
		t = t->next;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
	Node* t = head->next;
	while (t != nullptr) {
		if (t->m_key == key) {                    //returns true and copies the corresponding m_val data into value (upon finding key)
			value = t->m_val;
			return true;
		}
		t = t->next;
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {       
	if (i >= 0 && i < size()) {                                 
		Node* t = head->next;
		for (int j = 0; j < i; j++) {                            //iterates i times allowing the pointer to reach the ith node, after which m_key and m_val data is copied to key and value
			t = t->next;
		}
		key = t->m_key;
		value = t->m_val;
		return true;
	}
	else
		return false;
}

void Map::swap(Map& other) {
	int tempSize = mapSize;                              //swaps map size data member and head and tail dummy pointers using temp variables
	mapSize = other.mapSize;
	other.mapSize = tempSize;

	Node* temphead = head;
	head = other.head;
	other.head = temphead;

	Node* temptail = tail;
	tail = other.tail;
	other.tail = temptail;
}

bool combine(const Map& m1, const Map& m2, Map& result) {
	bool returnbool = true;                             //return variable
	Map tempmap;
	for (int i = 0; i < m1.size(); i++) {          //iterating through m1
		KeyType k;
		ValueType v;
		m1.get(i, k, v);
		if (m2.contains(k)) {                    //if key is also in m2, check if value is same and if so insert into result, otherwise set return variable to false
			ValueType v2;
			m2.get(k, v2);
			if (v2 == v) {
				tempmap.insert(k, v);
			}
			else {
				returnbool = false;
			}
		}
		else {
			tempmap.insert(k, v);             //if key not in m2, insert into result
		}
	}

	for (int j = 0; j < m2.size(); j++) {  //iterating through m2
		KeyType k;
		ValueType v;
		m2.get(j, k, v);
		if (!m1.contains(k)) {             //if key not in m1, add to result, since all keys in both m1 and m2 will already have been added
			tempmap.insert(k, v);
		}
	}
	result.swap(tempmap);
	return returnbool;
}

void subtract(const Map& m1, const Map& m2, Map& result) {
	Map tempmap;
	for (int i = 0; i < m1.size(); i++) {         //iterate through m1
		KeyType k;
		ValueType v;
		m1.get(i, k, v);
		if (!(m2.contains(k))) {                  //if key is in m1 but not m2, insert intro result
			tempmap.insert(k, v);
		}
	}
	result.swap(tempmap);
}
