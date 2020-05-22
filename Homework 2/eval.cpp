#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool precedence(char a, char b) {
	if (a == '*' || a == '/') {
		if (b == '*' || b == '/') {
			return true;
		}
		else {
			return false;
		}

	}
	if (a == '+' || a == '-') {
		return true;
	}
}

bool checkIfValid(string infix) {
	if (!islower(infix[0]) && infix[0] != '(') {
		return false;
	}
	if (!islower(infix[infix.length() - 1]) && infix[infix.length() - 1] != ')') {
		return false;
	}
	for (unsigned i = 0; i < infix.length() - 1; i++) {
		if (!islower(infix[i]) && infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/'&&infix[i] != '('&& infix[i] != ')') {
			return false;
		}
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
			if (infix[i + 1] == '+' || infix[i + 1] == '-' || infix[i + 1] == '*' || infix[i + 1] == '/' || infix[i] == ')') {
				return false;
			}
		}
		if (islower(infix[i])) {
			if (islower(infix[i + 1]) || infix[i + 1] == '(') {
				return false;
			}
		}
		if (infix[i] == '(') {
			if (!islower(infix[i + 1]) && infix[i + 1] != '(' ) {
				return false;
			}
		}
		if (infix[i] == ')') {
			if (infix[i + 1] != '+' && infix[i + 1] != '-' && infix[i + 1] != '*' && infix[i + 1] != '/' && infix[i + 1] != ')') {
				return false;
			}
		}
	}
	int count = 0;
	for (int j = 0; j < infix.length(); j++) {
		if (infix[j] == '(') {
			count += 1;
		}
		if (infix[j] == ')') {
			count -= 1;
		}
		if (count < 0) {
			return false;
		}
	}
	if (count != 0) {
		return false;
	}
	return true;
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
	string temp = "";
	for (int i = 0; i < infix.length(); i++) {
		if (infix[i] != ' ') {
			temp += infix[i];
		}
	}
	infix = temp;
	if (checkIfValid(infix)) {
		postfix = "";
		stack<char> charStack;
		for (int i = 0; i < infix.length(); i++) {
			char ch = infix[i];
			switch (ch) {
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				postfix += ch;
				break;
			case ' ':
				break;
			case '(':
				charStack.push(ch);
				break;
			case ')':
				while (charStack.top() != '(') {
					postfix += charStack.top();
					charStack.pop();
				}
				charStack.pop();
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				while (!charStack.empty() && charStack.top() != '(' && precedence(ch, charStack.top())) {
					postfix += charStack.top();
					charStack.pop();
				}
				charStack.push(ch);
				break;


			}
		}
		while (!charStack.empty()) {
			postfix += charStack.top();
			charStack.pop();
		}
	

		stack<ValueType> operandStack;
		for (int k = 0; k < postfix.length(); k++) {
			if (islower(postfix[k])) {
				ValueType value;
				values.get(postfix[k], value);
				if (!values.get(postfix[k], value)) {
					return 2;
				}
				operandStack.push(value);
			}
			else {
				ValueType operand2 = operandStack.top();
				operandStack.pop();
				ValueType operand1 = operandStack.top();
				operandStack.pop();
				if (postfix[k] == '+') {
					operandStack.push(operand1 + operand2);
				}
				else if (postfix[k] == '-') {
					operandStack.push(operand1 - operand2);
				}
				else if (postfix[k] == '*') {
					operandStack.push(operand1 * operand2);
				}
				else if (postfix[k] == '/') {
					if (operand2 == 0) {
						return 3;
					}
					operandStack.push(operand1 / operand2);
				}

			}
		}
		result = operandStack.top();
		return 0;
	}
	else
		return 1;
}




