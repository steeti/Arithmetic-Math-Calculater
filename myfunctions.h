#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H
bool goodPair(string&a,string&b);
bool isNumber(string&s);
bool isVariable(string&s);
bool isOperator(string&s);
bool isOperator2(char c);
void unaryToBinary(vector<string> & tokens);
void fix(string & eq ,vector<string> & tokens);
bool infixToPostfix(vector<string>&tokens,vector<string>&postfix);
void tokenise(string & eq ,vector<string> & tokens, int index);
bool evaluate(string&variable,vector<string>&postfix);
bool check(vector<string>&tokens);
int operatorPriority(string&a);
double integerValue(string&s);
#endif