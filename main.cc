// Harsh Shah
// Assignment 1

#include "iostream"
#include "stdlib.h"
#include "fraction.h"
#include "dictionary.h"
#include "stack.h"

using namespace std;

Stack<Fraction> numStack;
Stack<char> opStack;
Dictionary<string, Fraction> myDict;


unsigned int hash(string s) {
  unsigned int pos=0;

  for (int i=0;i<s.length();i++)
    pos = pos * i + s[i];

  return pos;
}

bool hasPrecedence( char a, char b ) {
	if( a == '*' || a == '/' ) {
		return true;
	}
	if( a == '$' || a == '(' ) {
		return false;
	} 

	return b == '+' || b == '-';
}
 
void doOperation( Stack<Fraction> &numStack, Stack<char> &opStack ) {

	Fraction right = numStack.pop();
	Fraction left = numStack.pop();
	char oper = opStack.pop();
	Fraction answer(0, 1);
	if( oper == '+' ) {
		answer = left + right;
	}
	if( oper == '-' ) {
		answer = left - right;
	}
	if( oper == '*' ) {
		answer = left * right;
	}
	if( oper == '/' ) {
		answer = left / right;
	}	
	numStack.push(answer);
}

void processSymbol(string s, int &first) {

	if(isdigit(s[first])) {
		int var;
		string value2 = "";
		string test;
		while(isdigit(s[first])){
			var = s[first] - '0';
			value2 += to_string(var);
			first++;
		}

		test = value2;
		int result2 = stoi(value2);
		Fraction value3(result2, 1);

		numStack.push(value3);
	} 

	else if ( isalpha(s[first])  ) {
		string st(1, s[first]);
		
		Fraction val = myDict.search(st);
		numStack.push(val);
		first++;
	}

	else if(s[first] == '(') {
		opStack.push(s[first]);
		first++;
	}

	else if( s[first] == ')' ) {
		while( opStack.peek() != '(' ) {
			doOperation(numStack, opStack);
		}

		opStack.pop();
		first++;
	}

	else if( s[first] == '+' || s[first] == '-' || s[first] == '*' || s[first] == '/' ) {
		while( hasPrecedence( opStack.peek(), s[first] ) ) {
			doOperation(numStack, opStack);
		}
		// cout << s[first] << endl;
		opStack.push(s[first]);
		first++;
	}

	else {
		first++;
	}
}


void scanForEqual(string s, int &first, string &dest){
	int i;
	for(i = 0; i < s.length(); i++) {
		if(s[i] == '=') {
			break;
		}
	}
	if( i < s.length() ) {
		first = i + 1;
	
		for( i = 0; i < first; i++ ) {
			if( isalpha(s[i]) || s[i] == '_' ) {
				while(isalnum(s[i]) || s[i] == '_') {
					dest += s[i];
					i++;
				}
				break;
			}
	}
}
}

Fraction evaluate(string s) {
	numStack.clear();
	opStack.clear();

	opStack.push('$');

	int first = 0;
	string dest = "";

	Fraction result(0, 1);

	scanForEqual(s, first, dest);

	while(first < s.length()) {
		processSymbol(s, first);
	} 


	while(opStack.peek()!= '$') {
		doOperation(numStack, opStack);
	}
	
	if( dest != "" ) {
		try {
			myDict.insert(dest, numStack.peek());
		} catch(DuplicateKeyException e) {
			myDict.update(dest, numStack.peek());
		}
	}

	return numStack.pop();
}


int main() {

	string ab = "x12=14*(52/7)";

	Fraction as(evaluate(ab));

	cout << as << endl;

	return 0;
} 