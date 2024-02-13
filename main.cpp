#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Scanner.h"
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) {
        string filename = argv[1];
        ifstream in;
        in.open(filename);
        stringstream ss;
        ss << in.rdbuf();
        string input = ss.str();
        in.close();

	Scanner s = Scanner(input);
	vector<Token> tokens;
	tokens = s.getTokens();

//	for(Token loop : tokens) {
//		cout << loop.toString() << endl;
//	}

	Parser p = Parser(tokens);
	p.datalogProgram();

//	vector<Token> tokens = {
//	  Token(ID,"Ned",2),
//	  Token(LEFT_PAREN,"(",2),
//	  Token(ID,"Ted",2),
//          Token(COMMA,",",2),
//          Token(ID,"Zed",2),
//          Token(RIGHT_PAREN,")",2),		
//	  Token(ID,"Ned",2),
//	  Token(LEFT_PAREN, "(", 2),
//	  Token(RIGHT_PAREN, ")", 2),
//	};
//	Parser p = Parser(tokens);
//	p.scheme();
//	p.idList();
}
