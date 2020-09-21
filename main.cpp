//Saad Teeti
//sht318
#include "header.h"
#include "myfunctions.h"
using namespace std;
map<string,double> value;
map<string,int> idx;
vector<bool> bad;
vector<vector<string> > postfixTokens;
int main(int argc, char* args[]) {
	string line;
	vector<vector<string> > tokens;
	vector<string> eq;
	string filename;
	string filename2;
    for (int i = 1; i < argc; i++) {
		if (strcmp(args[i],"-i")==0) 
			filename=args[i+1];
		else if (strcmp (args[i],"-o")==0){
			filename2=args[i+1];
		}
	}
	// opening file
	ifstream fin(filename);
	if(not fin.is_open())
	{
		cout<<"Can't open the file"<<endl;
		return EXIT_FAILURE;

	}
	// getting each line from the file
	while(getline(fin,line)){
		eq.push_back(line);
		bad.push_back(1);
	}
	tokens.resize(eq.size());
	postfixTokens.resize(eq.size());
	// for loop for tokenization
	// and checking if input i svalid or not for every equation.
	for(int i = 0 ; i < eq.size() ; i++){
		tokenise(eq[i],tokens[i],i);
		bad[i]=check(tokens[i]);
		
		
	}

	for(int i = 0 ; i < eq.size() ; i++){
		fix(eq[i],tokens[i]);
		
	}

	

	//for loop for each valid input convert it to postfix order
	for(int i = 0 ; i < eq.size() ; i++){
		if(!bad[i]){
			// if the equation contains single variable or number then the postfix order of it is only this single token
			// for example a=7; postfix order 7
			if(tokens[i].size()==4){
				postfixTokens[i].push_back(tokens[i][2]);
			}else{
				bad[i]=!infixToPostfix(tokens[i],postfixTokens[i]);
			}
		}
	}
	// if filename argument passed then output into a text file  else output on the screen
	if (filename2.length()!=0)
	{
		ofstream myfile;
		myfile.open(filename2);
		for(int i = 0 ; i < eq.size() ; i++){
			evaluate(tokens[i][0],postfixTokens[i]);
				if(bad[i]){
					myfile << tokens[i][0] << " = invalid"<< endl;
		}		else{
					myfile << tokens[i][0] << " = " << (value[tokens[i][0]]==floor(value[tokens[i][0]])?(int)floor(value[tokens[i][0]]):(value[tokens[i][0]])) << " ;"<<endl;
		}
	}

	}
	else
	// for loop for evaluation and outputting th value and the result of the equations
	{
		for(int i = 0 ; i < eq.size() ; i++){
			evaluate(tokens[i][0],postfixTokens[i]);
			if(bad[i]){
				cout << tokens[i][0] << " = invalid"<< endl;
			}else{
				cout << tokens[i][0] << " = " << (value[tokens[i][0]]==floor(value[tokens[i][0]])?(int)floor(value[tokens[i][0]]):(value[tokens[i][0]])) << " ;"<<endl;
			}
		}
	}


    return 0;
}