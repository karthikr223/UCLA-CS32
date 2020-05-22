#include "MyHash.h"
#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

class TranslatorImpl
{
public:
	TranslatorImpl();
	~TranslatorImpl();
	bool pushMapping(string ciphertext, string plaintext);
	bool popMapping();
	string getTranslation(const string& ciphertext) const;
private:
	struct stackElement {
		MyHash<char,char> mappingtable;
		stackElement* prev;
	};
	stackElement* top;
};

TranslatorImpl::TranslatorImpl() {
	top = new stackElement;
	char c = 'a';
	for (int i = 0; i < 26; i++) {
		top->mappingtable.associate(c, '?');
		c += 1;
	}
	top->prev = nullptr;
}

TranslatorImpl::~TranslatorImpl() {
	bool x = true;
	while (x == true) {
		x = this->popMapping();
	}
	delete top;
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{

	if (ciphertext.length() != plaintext.length())
		return false;
	for (int i = 0; i < ciphertext.length(); i++) {
		if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
			return false;
	}
	for (int j = 0; j < plaintext.length(); j++) {
		char c = 'a';
		for (int k = 0; k < 26; k++) {
			if (*top->mappingtable.find(c) == tolower(plaintext[j])) {
				if (tolower(ciphertext[j]) != c) {
					return false;
				}
			}
			c++;
		}
	}
	stackElement* newMap = new stackElement;
	char c = 'a';
	for (int m = 0; m < 26; m++) {
		for (int l = 0; l < ciphertext.length(); l++) {
			if (tolower(ciphertext[l]) == c) {
				if (*top->mappingtable.find(c) == '?') {
					newMap->mappingtable.associate(c, tolower(plaintext[l]));
					break;
				}
				else {
					if (*top->mappingtable.find(c) != tolower(plaintext[l]))
						return false;
				}
			}
			if (l == ciphertext.length() - 1)
				newMap->mappingtable.associate(c, *top->mappingtable.find(c));
		}
		c++;
	}
	stackElement* temp = top;
	top = newMap;
	top->prev = temp;
	return true;
}

bool TranslatorImpl::popMapping()
{
	if (top->prev == nullptr)
		return false;
	else {
		stackElement* temp = top;
		top = top->prev;
		delete temp;
		return true;
	}
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	string translatedtext = "";
	for (int i = 0; i < ciphertext.length(); i++) {
		if (!isalpha(ciphertext[i])) {
			translatedtext += ciphertext[i];
		}
		else {
			char c = *top->mappingtable.find(tolower(ciphertext[i]));
			if (isalpha(c)) {
				if (isupper(ciphertext[i])) {
					c = toupper(c);
				}
			}
			translatedtext += c;
		}
	}
	return translatedtext;
}


//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
	m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
	delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
	return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
	return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
	return m_impl->getTranslation(ciphertext);
}


