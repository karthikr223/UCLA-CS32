// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
#ifndef MYHASH
#define MYHASH

#include "provided.h"


template<typename KeyType, typename ValueType>
class MyHash
{
public:
	MyHash(double maxLoadFactor = 0.5):mlf(maxLoadFactor),usedbuckets(0),totalbuckets(100) {
		if (maxLoadFactor <= 0)
			mlf = 0.5;
		else if (maxLoadFactor > 2)
			mlf = 2.0;

		m_array = new Bucket[100];
		
	}
	~MyHash() {
		for (int i = 0; i < totalbuckets; i++) {
			Bucket* curr = m_array[i].next;
			while (curr != nullptr) {
				Bucket* temp = curr;
				curr = curr->next;
				delete temp;
			}
		}
		delete[]m_array;
	}
	void reset() {
		for (int i = 0; i < totalbuckets; i++) {
			Bucket* curr = m_array[i].next;
			while (curr != nullptr) {
				Bucket* temp = curr;
				curr = curr->next;
				delete temp;
			}
		}
		delete[]m_array;
		m_array = new Bucket[100];
		totalbuckets = 100;
		usedbuckets = 0;
	}
	void associate(const KeyType& key, const ValueType& value) {
		unsigned int hash(const KeyType& k);
		int hashvalue = hash(key) % totalbuckets;
		if (m_array[hashvalue].occupied == false) {
			m_array[hashvalue].b_key = key;
			m_array[hashvalue].b_val = value;
			m_array[hashvalue].occupied = true;
			usedbuckets += 1;
		}
		else {
			Bucket* curr = m_array[hashvalue].b_curr;
			while (curr != nullptr) {
				if (key == curr->b_key) {
					curr->b_val = value;
					break;
				}
				Bucket* prev = curr;
				curr = curr->next;
				if (curr == nullptr) {
					Bucket* newBucket = new Bucket;
					newBucket->b_key = key;
					newBucket->b_val = value;
					newBucket->occupied = true;
					usedbuckets += 1;
					prev->next = newBucket;
					break;
				}
			}
		}

		if (getLoadFactor() > mlf) {
			Bucket* newArray = new Bucket[totalbuckets * 2];
			for (int i = 0; i < totalbuckets; i++) {
				Bucket* transferbucket = m_array[i].b_curr;
				while (transferbucket!= nullptr && transferbucket->occupied == true) {
					unsigned int hash(const KeyType& k);
					int newhashvalue = hash(transferbucket->b_key) % (totalbuckets * 2);
					if (newArray[newhashvalue].occupied = false) {
						newArray[newhashvalue].b_key = transferbucket->b_key;
						newArray[newhashvalue].b_val = transferbucket->b_val;
						newArray[newhashvalue].occupied = true;
					}
					else {
						Bucket* curr2 = newArray[newhashvalue].b_curr;
						while (curr2 != nullptr) {
							Bucket* prev2 = curr2;
							curr2 = curr2->next;
							if (curr2 == nullptr) {
								Bucket* newBucket = new Bucket;
								newBucket->b_key = transferbucket->b_key;
								newBucket->b_val = transferbucket->b_val;
								newBucket->occupied = true;
								prev2->next = newBucket;
								break;
							}
						}
					}
					transferbucket = transferbucket->next;
				}
			}
			for (int i = 0; i < totalbuckets; i++) {
				Bucket* d = m_array[i].next;
				while (d != nullptr) {
					Bucket* temp = d;
					d = d->next;
					delete temp;
				}
			}
			delete[]m_array;
			m_array = newArray;
			totalbuckets *= 2;
		}

	}
	int getNumItems() const {
		return usedbuckets;
	}
	double getLoadFactor() const {
		return double(usedbuckets) /double(totalbuckets);
	}

      // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const {
		unsigned int hash(const KeyType& k);
		int hashvalue = hash(key) % totalbuckets;
		if (m_array[hashvalue].occupied == true) {
			Bucket* findBucket = m_array[hashvalue].b_curr;
			while (findBucket != nullptr) {
				if (findBucket->b_key == key) {
					return &findBucket->b_val;
				}
				findBucket = findBucket->next;
			}
		}
		return nullptr;
	}

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
	struct Bucket {
		Bucket() :next(nullptr), occupied(false),b_curr(this) {}
		Bucket* b_curr;
		Bucket* next;
		KeyType b_key;
		ValueType b_val;
		bool occupied;
	};
	Bucket* m_array;
	double mlf;
	int usedbuckets;
	int totalbuckets;
};
#endif