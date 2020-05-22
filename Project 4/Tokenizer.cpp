#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const string& s) const;
private:
	vector<char> m_separators;
};

TokenizerImpl::TokenizerImpl(string separators)
{
	for (int i = 0; i < separators.length(); i++)
		m_separators.push_back(separators[i]);
}

vector<string> TokenizerImpl::tokenize(const string& s) const
{
	int stringStart = 0;
	vector<string> tokenString;
	for (int i = 0; i < s.length(); i++) {
		for (int j = 0; j < m_separators.size(); j++) {
			if (s[i] == m_separators[j]) {
				if (i-stringStart != 0) {
					tokenString.push_back(s.substr(stringStart, i - stringStart));
					stringStart = i + 1;
				}
				else {
					stringStart = i + 1;
				}
			}
		}
		if (i == s.length() - 1) {
			if (stringStart != i + 1) {
				tokenString.push_back(s.substr(stringStart, i - stringStart + 1));
			}
		}
	}
	return tokenString;

}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const string& s) const
{
    return m_impl->tokenize(s);
}
