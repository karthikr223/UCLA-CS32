#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m;
	assert(m.empty() && m.size() == 0); //check if map is empty
	m.insert("Fred", 123);           //add two valid nodes
	m.insert("Lucy", 456);
	assert(!m.empty() && m.size() == 2);//check if empty and size functions are working correctly
	assert(!m.insert("Fred", 123));  //check if insert function returns false when map already contains the key
	assert(m.size() == 2);             //checks that map was not modified


	Map m2;
	m2 = m;               //check if assignment operator works, if it does, copy contructor(and swap function) also works correctly as it is called in the assignment operator
	Map m3(m);         //checking if copy constructor works separately
	assert(m.contains("Fred") && m.contains("Lucy") && m.size() == 2);
	assert(m2.contains("Fred") && m2.contains("Lucy") && m2.size() == 2);
	assert(m3.contains("Fred") && m3.contains("Lucy") && m3.size() == 2);

	m.update("Fred", 789);             //update a value
	assert(m.size() == 2);
	KeyType k;
	ValueType v;
	m.get("Fred", v);      //check if update function worked correctly above, testing get when key is present
	assert(v == 789);
	assert(!m.update("Ethel", 123)); //checks if update function works correctly when map does not contain the name

	m.insertOrUpdate("Fred", 789);     //checks if insertorupdate works when the update is required
	m.insertOrUpdate("Ethel", 111);    //checks if insertorupdate works when the insert is required
	m.get("Fred", v);
	assert(v == 789 && m.size() == 3);
	assert(!m.erase("Ricky"));                //checks if erase does nothing when key is not present in map
		m.erase("Fred");                        //checks if erase function works when key is present
	m.erase("Lucy");
	m.erase("Ethel");
	assert(m.empty() && m.size() == 0);
	m.insertOrUpdate("Fred", 123);          //checks if insertorupdate works when map is empty
	assert(m.contains("Fred") && m.size() == 1);      //testing contains functions also
	assert(!m.contains("Lucy"));                  //contains function when key is not present

	m.swap(m2);                               //checking swap function
	assert(m.contains("Fred") && m.contains("Lucy") && m.size() == 2);
	assert(m2.contains("Fred") && m2.size() == 1);

	assert(v == 789);
	assert(!m.get("Ethel", v));               //checking get function when key is not present 
	assert(v == 789);                         //v is unchanged

	KeyType all;                             //checking if 3 argument get function works as per spec
	ValueType total = 0;
	for (int n = 0; n < m.size(); n++)
	{
		KeyType k;
		ValueType v;
		m.get(n, k, v);
		all += k;
		total += v;
	}
	assert(all == "FredLucy" && total == 579);  //checks if all the items of the list have been retrieved (579 is 123 + 456)

	assert(m.get(1, k, v) && (k == "Fred" || k == "Lucy"));  //calling get repeatedly with the same first parameter copies the same key and value each time
	KeyType k2;
	assert(m.get(1, k2, v) && k2 == k);

	Map m4(m);
	m4.insert("Ethel", 111);
	m4.insert("Ricky", 222);
	m4.erase("Lucy");
	assert(m.contains("Fred") && m.contains("Lucy") && m.size() == 2); //contents of m
	assert(m4.contains("Fred") && m4.contains("Ethel") && m4.contains("Ricky") && m4.size() == 3); //contents of m4
	Map result;
	assert(combine(m, m4, result));
	assert(result.contains("Fred") && result.contains("Lucy") && result.contains("Ethel") && result.contains("Ricky") && result.size() == 4);   //checks if combine works when there are repeated names in both maps, as well as unique names
	combine(m, m4, result);
	assert(result.contains("Fred") && result.contains("Lucy") && result.contains("Ethel") && result.contains("Ricky") && result.size() == 4);  //checks if combine works when result is not empty
	combine(m, m4, m);
	assert(m.contains("Fred") && m.contains("Lucy") && m.contains("Ethel") && m.contains("Ricky") && result.size() == 4); //check that combine works for aliasing
	m4.update("Fred", 789);
	assert(!combine(m, m4, result)); //combine should return false as value is different in both maps

	subtract(m, m4, result);        //testing subtract function when result is not empty
	assert(result.contains("Lucy"));
	subtract(m, m4, m);  //testing subtract function for aliasing


}

int main()
{
	test();
	cout << "Passed all tests" << endl;
	int x;
	cin >> x;
}