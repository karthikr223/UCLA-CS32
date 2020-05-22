#include <iostream>
#include <algorithm>
#include <fstream>
#include "MyHash.h"
#include "provided.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::ifstream;

class WordListImpl
{
public:
	bool loadWordList(string filename);
	bool contains(string word) const;
	vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
	string findStringPattern(string s) const;
	MyHash<string, vector<string>> wordlist;
};

string WordListImpl::findStringPattern(string s) const {
	string pattern = "a";
	char currentchar = 'b';
	for (int i = 1; i < s.length(); i++) {
		for (int j = 0; j < i; j++) {
			if (tolower(s[i]) == tolower(s[j])) {
				pattern += pattern[j];
				break;
			}
			if (j == i - 1) {
				pattern += currentchar;
				currentchar += 1;
			}
		}

	}
	return pattern;
}

bool WordListImpl::loadWordList(string filename)
{
	wordlist.reset();
	ifstream infile(filename);    // infile is a name of our choosing
	if (!infile)		        // Did opening the file fail?
	{
		return false;
	}
	string s;
	while (getline(infile, s))
	{
		for (int i = 0; i < s.length(); i++) {
			if (!isalpha(s[i]) && s[i] != '\'') {
				break;
			}
			if (isupper(s[i])) {
				s[i] = tolower(s[i]);
			}
			if (i == s.length() - 1) {
				vector<string>w;
				if (wordlist.find(findStringPattern(s)) == nullptr) {
					w.push_back(s);
					wordlist.associate(findStringPattern(s), w);
				}
				else {
					w = *wordlist.find(findStringPattern(s));
					w.push_back(s);
					wordlist.associate(findStringPattern(s), w);
				}
			}
		}
	}
	return true;
}

bool WordListImpl::contains(string word) const
{
	for (int i = 0; i < word.length(); i++) {
		if (isupper(word[i])) {
			word[i] = tolower(word[i]);
		}
	}
	if (wordlist.find(findStringPattern(word)) == nullptr)
		return false;
	else {
		vector<string> w = *wordlist.find(findStringPattern(word));
		if (std::find(w.begin(), w.end(), word) != w.end())
			return true;
		else
			return false;
	}
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	vector<string> candidates;
	if (wordlist.find(findStringPattern(cipherWord)) == nullptr)
		return candidates;
	else {
		vector<string> returnstring;
		candidates = *wordlist.find(findStringPattern(cipherWord));
		for(int i =0;i<candidates.size();i++) {
			for (int j = 0; j < currTranslation.length(); j++) {
				if (currTranslation[j] != '?') {
					if (currTranslation[j] == '\'') {
						if (candidates[i][j] != '\'')
							break;
					}
					else if (tolower(currTranslation[j]) != candidates[i][j])
						break;
				}
				if (j == currTranslation.length() - 1) {
					returnstring.push_back(candidates[i]);
				}
			}
		}
		return returnstring;
	}
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
	return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
	return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
	return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
	m_impl = new WordListImpl;
}

WordList::~WordList()
{
	delete m_impl;
}

bool WordList::loadWordList(string filename)
{
	return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
	return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
	return m_impl->findCandidates(cipherWord, currTranslation);
}
