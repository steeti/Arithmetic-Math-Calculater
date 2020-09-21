//Saad Teeti
//sht318
#include "header.h"
#include "myfunctions.h"
using namespace std;

// check if the token is a number
bool isNumber(string&s){
	for(int i = 0 ; i < s.length() ; i++)
		if(s[i]=='.')continue;
		else if(s[i]>'9'||s[i]<'0')
			return false;
	return true;
}
// check if the token is a variable or not through the map of the index 
bool isVariable(string&s){
	return idx.find(s)!=idx.end();
}
// checks if the token is an operator or not
bool isOperator(string&s){
	return s[0]=='!'||s[0]=='*'||s[0]=='+'||s[0]=='/'||s[0]=='-'||s[0]=='%'||s[0]=='@';
}
// check if the character is an operater
bool isOperator2(char ch){
	return ch=='*'||ch=='+'||ch=='/'||ch=='-';
}
// check if the equation is valid or not
bool check(vector<string>&tokens){
	while(tokens.back().empty())tokens.pop_back();
	if(tokens.back()!=";")
		return true;
	int ctr=0;
	for(int i = 0 ; i < tokens.size() ; i++){
		if(tokens[i]=="=")
			ctr++;
	}
	if(ctr==1)
		return false;
	return true;
}

// converts the intger token into an integer 
double integerValue(string&s){
	double res=0;
	int ctr=1;
	bool b=0;
	for(int i = 0 ; i < s.size() ; i++){
		if(s[i]=='.'){
			b=1;
			continue;
		}
		res*=10;
		res+=(s[i]-'0');
		if(b)ctr*=10;
	}
	return res/ctr;
}
// unary operators have the heighest priority
int operatorPriority(string&a){
    if(a[0]=='!') 
        return 2;
    if(a=="*"||a=="/"||a=="//"||a=="%")
        return 1;
    return 0;
}
// good pair operators
bool goodPair(string&a,string&b){
	int x,y;
	x=operatorPriority(a);
	y=operatorPriority(b);
	return x<=y;
}
// functions used to fix the unary tokens and converts tokens that are of the same type of operators into either two or one
// for example +++ would be |+| |++| 
void fix(string & eq ,vector<string> & tokens){
    vector<string> newTokens;
    bool flag=true;
    newTokens.push_back(tokens[0]);
    // for loops that checks in the tokens for operators and push them into new token vector
    for(int i = 1 ; i < tokens.size() ; i++){
        if(isNumber(tokens[i])||isVariable(tokens[i])){
            newTokens.push_back(tokens[i]);

        //if statment to seperate -- to two differnt token if the previous character is a number or a variable
        }else if(tokens[i]=="--"&&(isNumber(tokens[i-1])||isVariable(tokens[i-1]))){
            newTokens.push_back("-");
            newTokens.push_back("-");
        }else{
        	// else statemnt to seperate each tokens of operations, depending on the number of tokens, even seperates in twos while odd and seperate in one then the rest in twos
            int sz=tokens[i].size();
            string tmp ="";
            tmp+=tokens[i][0];
            if(tokens[i][0]=='/'&&tokens[i].size()>2){
                flag=false;
            }
            if(sz%2==1){
                newTokens.push_back(tmp);
                sz--;
            }
            tmp = tmp+tmp;
            while(sz!=0){
                newTokens.push_back(tmp);
                sz-=2;
            }
            if(newTokens.back()=="//")
                newTokens.back()="@";
            
        }
    }
    // for loop to convert the unary tokens into ! + the unnary token
    for(int i = 0 ; i < newTokens.size() ; i++){
        if(newTokens[i]=="--"||newTokens[i]=="**"||newTokens[i]=="++"||(newTokens[i]=="-"&&i!=0&&!(isNumber(tokens[i-1])||tokens[i-1]==")"||isVariable(tokens[i-1])))){
            newTokens[i]="!"+newTokens[i];
        }
    }
    tokens.clear();
    // for loop to push the new tokens into tokens
    for(int i =0 ; i < newTokens.size() ; i++)
    {
    	tokens.push_back(newTokens[i]);
    }
    if(flag==false&&tokens.back()==";"){
        tokens.pop_back();
    }
}


// tokenization function that takes the equation and the vector of tokens
void tokenise(string & eq ,vector<string> & tokens, int index){
	
	string cur = "";

	for(int i = 0 ; i < eq.size(); i++){
		if(eq[i]!=' '){
	
		//first if statments check on those character because they would always be single tokens
			if(eq[i]=='('||eq[i]==')'||eq[i]=='%'||eq[i]=='='||eq[i]==';'){
				// if the string is not empty then it would be added to the tokens vector
				if(!cur.empty()){
					tokens.push_back(cur);
					//cout<<"1"<<cur<<endl;
				}
				//clear the string and make it equal to eq[i]
				//eq[i] is euqal to the current character in the equation
				cur="";
				cur+=eq[i];
				//add the string to the token 
				//cout<<"2"<<cur<<endl;
				tokens.push_back(cur);
				// clear the string
				cur="";
			// if the string is empty then make cur equal to eq[i]
			}else if(cur.empty()){
				cur+=eq[i];
			// first if statement the last character in the current tokken is of the same type of current character in the equation 
			// For example 'a' and 'b' have the same type, '+' and '+' have the same type, 5 and * dont have the same type.
			}else if(isOperator2(eq[i])==isOperator2(cur[cur.size()-1])){
				//check if two diffeent operations are followed by each other, for example 5* -1
				if(eq[i]!=cur[cur.size()-1]&&isOperator2(eq[i])){
					// if so then add the first operation to the vector token, and then we check back the second operation and we add it to current token
					tokens.push_back(cur);
					cur="";
				}
				cur+=eq[i];
			}
			else {
				//otherwise push the current token into vector token and make the new current token equals to the current character
				tokens.push_back(cur);

				cur="";
				cur+=eq[i];
			}
		}
	}
	idx[tokens[0]]=index;
	tokens.push_back(cur);
    
	
}
// function to convert form infex to postfix
bool infixToPostfix(vector<string>&tokens,vector<string>&postfix){
	stack <string> st;
	st.push("(");
	tokens.pop_back();
	tokens.push_back(")");
	tokens.push_back(";");
	int i=2;
	string curToken="";
	while(!st.empty()){
		if(i>=tokens.size()){
			return false;
		// returns false if the number of the paranthesis weren't right, which return invalid at the end
		}
		curToken = tokens[i++];
		// number of variable is encountered add them to postfix
		if (isNumber(curToken)||isVariable(curToken))
			postfix.push_back(curToken);
		// if paranthases encountred push it into a stack
		else if(curToken=="(")
			st.push(curToken);
		// if operator is encountered 
		else if(isOperator(curToken)){ 
			// repeatedly pop from stack and add to Postfix each operator(on the top of the stack) which has the same or higher precedence than operator
			while (!st.empty() and isOperator(st.top()) and goodPair(curToken,st.top())){
				
				postfix.push_back(st.top());
				st.pop();
			}
			st.push(curToken);
		}
		else if(curToken==")"){
			// if right paranathesis encountered then pop from stack and add to postfic each operator until the left paranthesis is encountered
			while(!st.empty() and (st.top()!="(" or st.top()[0]=='!')){
				postfix.push_back(st.top());
				st.pop();
			}
			st.pop();
		}
	}
	return true;
	
}
bool evaluate(string&variable,vector<string>&postfix){
	//if invalid dont calculate it
	if(bad[idx[variable]]){
		return false;
	}
	//if it was calculated before dont calculate it
	if(value.find(variable)!=value.end()){
		return true;
	}
	stack<double> numbers;
	for(int i = 0 ; i < postfix.size() ; i++){
		//if the token is a number then insert it into the stack
		if(isNumber(postfix[i])){
			numbers.push(integerValue(postfix[i]));
		}
		//if the token is a variable then check if it is valid or not
		if(isVariable(postfix[i])){
			//evaluate the variable and if it is valid then it will return true
			// if it was valid then push the value of it
			if(evaluate(postfix[i],postfixTokens[idx[postfix[i]]])){
				numbers.push(value[postfix[i]]);
			}else{
				// if its not valid, mark the equation as invalid equation and return false
				bad[idx[variable]]=true;
				return false;
			}
		}
		// if the element is an operator then pop 2 elements from stack
		// apply operater and push the results back to stack
		if(isOperator(postfix[i])){
            
			double num1,num2;
			num2=numbers.top();
			numbers.pop();
			if(postfix[i][0]!='!'){
                num1=numbers.top();
			    numbers.pop();
            }
            // cases for evaluation
			switch(postfix[i][0]){
				case '*':
					num1*=num2;
					break;
				case '+':
					num1+=num2;
					break;
				case '/':
					// checking if divided by 0 to return invalid input at the end
					if (num2==0)
					{
						bad[idx[variable]]=true;
						return false;
					}
					else
					{ 
						num1/=num2;
					}


					break;
				case '@':
					// checking if divided by 0 to return invalid input at the ned
					if (num2==0)
					{
						bad[idx[variable]]=true;
						return false;
					}
					else
					{
						num1=num1/num2;
						num1= floor(num1);
					}
	
					break;
				case '-':
					num1-=num2;
					break;
				case '%':
					num1 = (int)(num1)%(int)(num2);
					break;
                default:
                    if(postfix[i]=="!-"){
                        num1=-num2;
                    }
                    if(postfix[i]=="!--"){
                        num1=--num2;
                    }
                    if(postfix[i]=="!++"){
                        num1=++num2;
                    }
                    if(postfix[i]=="!**"){
                        num1=num2*num2;
                    }
			}
			numbers.push(num1);

		}
	}
	value[variable]=numbers.top(); // the value fromt he top of the stack is the final answer and its stored in the map
	return true;
}
