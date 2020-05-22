#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
#include<iostream>
using namespace std;

class DecrypterImpl
{
public:
	DecrypterImpl();
	~DecrypterImpl();
	bool load(string filename);
	vector<string> crack(const string& ciphertext);
private:
	vector<string> subcrack(const string& ciphertext);
	WordList* m_wordlist;
	Translator* m_translator;
	Tokenizer* m_tokenizer;
	vector<string> decryptlist;
};

DecrypterImpl::DecrypterImpl() {
	m_wordlist = new WordList;
	m_translator = new Translator;
	m_tokenizer = new Tokenizer(",;:.!()[]{}-\"#$%^& 1234567890");
}

DecrypterImpl::~DecrypterImpl() {
	delete m_wordlist;
	delete m_tokenizer;
	delete m_translator;
}

bool DecrypterImpl::load(string filename)
{
	return(m_wordlist->loadWordList(filename));
}

vector<string> DecrypterImpl::subcrack(const string& ciphertext) {
	vector<string> tokens = m_tokenizer->tokenize(ciphertext);
	int maxuncrackedpos = 0;
	int maxuncracked = 0;
	for (int i = 0; i < tokens.size(); i++) {
		int qm = 0;
		string translated = m_translator->getTranslation(tokens[i]);
		for (int j = 0; j < translated.length(); j++) {
			if (translated[j] == '?')
				qm++;
		}
		if (qm > maxuncracked && qm>0) {
			maxuncracked = qm;
			maxuncrackedpos = i;
		}
	}
	string max = tokens[maxuncrackedpos];
	string translated = m_translator->getTranslation(max);
	vector<string> matchingwords = m_wordlist->findCandidates(max, translated);
	if (matchingwords.size() == 0) {
		m_translator->popMapping();
		return decryptlist;
	}

	for (int k = 0; k < matchingwords.size(); k++) {
		for (int l = 0; l < max.length(); l++) {
			bool x = m_translator->pushMapping(string(1, max[l]), string(1, matchingwords[k][l]));
			if (x == false) {
				for (int q = 0; q< l; q++) {
					m_translator->popMapping();
				}
				goto nextword;
			}
			if (l == max.length() - 1) {
				string newdecrypt = m_translator->getTranslation(ciphertext);
				vector<string> plaintext = m_tokenizer->tokenize(newdecrypt);
				bool isfullyDecrypted = true;
				for (int n = 0; n < plaintext.size(); n++) {
					for (int o = 0; o < plaintext[n].length(); o++) {
						if (plaintext[n][o] == '?') {
							isfullyDecrypted = false;
							break;
						}
						if (o == plaintext[n].length() - 1) {
							if (!m_wordlist->contains(plaintext[n])) {
								for (int p = 0; p <= l; p++)
									m_translator->popMapping();
								goto nextword;
							}
						}
					}
				}
				if (!isfullyDecrypted) {
					subcrack(ciphertext);
					goto nextword;
				}
				else {
					decryptlist.push_back(newdecrypt);
					sort(decryptlist.begin(), decryptlist.end());
					for (int r = 0; r <= l; r++)
						m_translator->popMapping();
					goto nextword;
				}
			}
		}
	nextword:
		;
	}
	for (int s = 0; s <= matchingwords[0].length(); s++)
		m_translator->popMapping();
	return decryptlist;
}
vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	decryptlist.clear();
	bool x = true;
	while (x == true) 
		x = m_translator->popMapping();
	return subcrack(ciphertext);
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
