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
/**
 * Function to check if an operator has precedence over the other 
*/
bool hasPrecedence( char a, char b ) {
	if( a == '*' || a == '/' ) {
		return true;
	}
	if( a == '$' || a == '(' ) {
		return false;
	} 

	return b == '+' || b == '-';
}
 
/**
 * Function to perform the arithmetic operations of the Fractions
*/
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

/**
 * Function to process the symbols given in the input string
*/
void processSymbol(string s, int &first) {

	// Check to see if first is a number
	if(isdigit(s[first])) {
		int var;
		string target = "";
		string test;
		while(isdigit(s[first])){
			var = s[first] - '0';
			target += to_string(var);
			first++;
		}

		int result = stoi(target);
		Fraction fValue(result, 1);

		numStack.push(fValue);
	} 

	// Check to see if first is a letter
	else if ( isalpha(s[first])  ) {
		string st(1, s[first]);
		
		Fraction val = myDict.search(st);
		numStack.push(val);
		first++;
	}

	// Check to see if first is an open bracket
	else if(s[first] == '(') {
		opStack.push(s[first]);
		first++;
	}

	// Check to see if first is a closed bracket
	else if( s[first] == ')' ) {
		while( opStack.peek() != '(' ) {
			doOperation(numStack, opStack);
		}

		opStack.pop();
		first++;
	}
	// Check to see if first is an operator
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

/**
 * Scans the arithmetic expression and changes the value of first if an equals sign is found 
*/
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

/**
 * Function to evaluate the input string and give the result
*/
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

	string s;
	while(true) {
		cout << "Enter an expression, or press Cntrl + C to exit: ";
		cin >> s;

		Fraction value(evaluate(s));

		cout << value << endl;
	}

	return 0;
}
