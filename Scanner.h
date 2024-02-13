#pragma once
#include "Token.h"
#include <string>
#include <cctype>
#include <vector>

class Scanner {
	private:
		string input;
		int line = 1;
		TokenType type = UNDEFINED;
		string value = "";
		int tempLines = 0;
		string input2;
		vector<Token> tokens;
		int numOfTokens = 0;
	public:
		Scanner(const string& input) : input(input) {}

		string getInput() {
		   return input;
		}

		vector<Token> getTokens() {
			while(input.length() != 0) {
				Token t = scanToken();
				tokens.push_back(t);
			}
			return tokens;
		}

		void loopThrough() {
			   Token test = scanToken();
			   cout << test.toString() << endl;
			while(input.length() != 0) {
			   Token t = scanToken();
			   cout << t.toString() << endl;
			}
			cout << "Total Tokens = " << numOfTokens << endl;
		}

		Token scanToken() {
//		    cout << line << " ";
//		    cout << input << endl;
	            if(input.empty()) {
		          type = EOFILE;
			  value = "";
		    } else {
		         if(input.at(0) == '\n') {
			      line++;
			      input = input.substr(1);
			 }

/*			 if (input.at(0) == '#') {
                             if(input.at(1) == '|' && input.length() > 1) {
                               cout << "in here" << endl;
                               string temp;
                               temp  = input.substr(1);
                               for(long unsigned int i = 0; i < temp.length(); i++) {
                                  if(temp.find("|#") > input.length()) {
                                     input2 = input;
                                  //   type = UNDEFINED;
                                     input = input.substr(input.length()-1);
                                     break;
                                   } else if(input.substr(i,2) == "|#") {
                                      input2 = input.substr(0, i+2);
                                    //  type = COMMENT;
                                      input = input.substr(i+2);
                                      break;
                                  }
                               }
                             } else {
                                for(long unsigned int i = 0; i < input.length(); i++) {
                                    if(input.at(i) == '\n') {
//                                    line++;
                                      input2 = input.substr(0,i);
                                    //  cout << input2 << "end" << endl;
                        //            cout << input.substr(i) << "end"  << endl;
                        //            type = COMMENT;
                                      input = input.substr(i);
                                      break;
                                   }
                                }
                             }
                        //     cout << input << endl;
                          //   value = input2;
                         }*/

			 while(input.length() > 0 && isspace(input.at(0))) {
			     if(input.at(0) == '\n') {
			        line++;
			//	cout << "line: " << line << endl;
			     }
			     input = input.substr(1);
			 }
		  if(input.empty()) {
			     type = EOFILE;
			     value = "";
			     line = line + tempLines;
			  } else {
			  while(input.at(0) == '#') {
			  if (input.at(0) == '#') {
                             if(input.at(1) == '|' && input.length() > 1) {
                               cout << "in here" << endl;
                               string temp;
                               temp  = input.substr(1);
                               for(long unsigned int i = 0; i < temp.length(); i++) {
                                  if(temp.find("|#") > input.length()) {
                                     input2 = input;
                                  //   type = UNDEFINED;
                                     input = input.substr(input.length()-1);
                                     break;
                                   } else if(input.substr(i,2) == "|#") {
                                      input2 = input.substr(0, i+2);
                                    //  type = COMMENT;
                                      input = input.substr(i+2);
                                      break;
                                  }
                               }
                             } else {
                                for(long unsigned int i = 0; i < input.length(); i++) {
                                    if(input.at(i) == '\n') {
//                                    line++;
                                      input2 = input.substr(0,i);
                                    //  cout << input2 << "end" << endl;
                        //            cout << input.substr(i) << "end"  << endl;
                        //            type = COMMENT;
                                      input = input.substr(i);
                                      break;
                                   }
                                }
                             }
                         while(input.length() > 0 && isspace(input.at(0))) {
                             if(input.at(0) == '\n') {
                                line++;
                        //      cout << "line: " << line << endl;
                             }
                             input = input.substr(1);
                         }

//                             cout << input << endl;
                          //   value = input2;
                         }
			 }
			   if(input.at(0) == '\'') {
			      string temp = input.substr(1);
			      for(long unsigned int i = 0; i < temp.length(); i++) {
			         if(temp.find("'") > input.length()) {
				    for(long unsigned int j = 0; j < input.length(); j++) {
                                       if(input.at(j) == '\n') {
                                           tempLines++;
                                        }
                                    }
				    tempLines--;
				    type = UNDEFINED;
				    input2 = input;
				    input = input.substr(input.length() -1);
				    break;
				 } else if(temp.at(i) == '\'') {
				    input2 = input.substr(0,i+2);
				    type = STRING;
				    input = input.substr(i+2);
				    break;
				 }
			      }
				 value = input2;
			}  else if (isalpha(input.at(0))) {
			       if(input.length() >=6 && (input.substr(0,6) == "Rules:" ||
			       				input.substr(0,6) == "Rules\n")) {
			          type = RULES;
				  value = "Rules";
				  input = input.substr(5);
			       } else if(input.length() >= 8 && (input.substr(0,8) == "Queries:" ||
			       					input.substr(0,8) == "Queries\n")) {
				   type = QUERIES;
				   value = "Queries";
				   input = input.substr(7);
			       } else if(input.length() >= 8 && (input.substr(0,8) == "Schemes:" ||
			       					input.substr(0,8) == "Schemes\n")) {
				   type = SCHEMES;
				   value = "Schemes";
				   input = input.substr(7);
			       } else if(input.length() >= 6 &&  (input.substr(0,6) == "Facts:" ||
			       					input.substr(0,6) == "Facts\n")) {
			           type = FACTS;
				   value = "Facts";
				   input = input.substr(5);
			       } else {
			          // this next loop won't work, we don't have temp
			          for(long unsigned int j = 0; j < input.length(); j++) {
			              if(!(isalpha(input.at(j)) || isdigit(input.at(j)))) {
				          input2 = input.substr(0,j);
					  break;
				      }   
			           }
			          type = ID;
			          value = input2;
			          input = input.substr(input2.length());
			      }
		        }  else if (input.at(0) == ',') {
			     type = COMMA;
		             value = ",";
			     input = input.substr(1);
			} else if (input.at(0) == '.') {
			     type = PERIOD;
			     value = ".";
			     input = input.substr(1);
			} else if (input.at(0) == '(') {
			     type = LEFT_PAREN;
			     value = "(";
			     input = input.substr(1);
		        } else if (input.at(0) == ')') {
			     type = RIGHT_PAREN;
			     value = ")";
			     input = input.substr(1);
			 } else if (input.at(0) == '?') {
			 //     cout << "line: " << line << endl;
			   //   cout << input << endl;
			     type = Q_MARK;
			     value = "?";
			     input = input.substr(1);
			 } else if (input.substr(0,2) == ":-") {
			     type = COLON_DASH;
			     value = ":-";
			     input = input.substr(2);
			 } else if (input.at(0) == ':') {
			      type = COLON;
			      value = ":";
			      input = input.substr(1);
			 } else if (input.at(0) == '*') {
			     type = MULTIPLY;
			     value = "*";
			     input = input.substr(1);
			 } else if (input.at(0) == '+') {
			     type = ADD;
			     value = "+";
			     input = input.substr(1);
			 } else if (input.at(0) == '#') {
			     if(input.at(1) == '|' && input.length() > 1) {
			       cout << "in here" << endl;
			       string temp;
			       temp  = input.substr(1);
			       for(long unsigned int i = 0; i < temp.length(); i++) {
			          if(temp.find("|#") > input.length()) {
				     input2 = input;
				  //   type = UNDEFINED;
				     input = input.substr(input.length()-1);
				     break;
			           } else if(input.substr(i,2) == "|#") {
				      input2 = input.substr(0, i+2);
				    //  type = COMMENT;
				      input = input.substr(i+2);
				      break;
				  } 
			       }
			     } else {
			        for(long unsigned int i = 0; i < input.length(); i++) {
				    if(input.at(i) == '\n') {
//				      line++;
				      input2 = input.substr(0,i);
				    //  cout << input2 << "end" << endl;
			//	      cout << input.substr(i) << "end"  << endl;
			//	      type = COMMENT;
				      input = input.substr(i);
				      break;
				   }
				}
			     }
			 while(input.length() > 0 && isspace(input.at(0))) {
                             if(input.at(0) == '\n') {
                                line++;
                        //      cout << "line: " << line << endl;
                             }
                             input = input.substr(1);
                         }

			//     cout << input << endl;
			  //   value = input2;
			 } else if (input.empty()) {
			     type = EOFILE;
			     value = "";
			   } else {
			      type = UNDEFINED;
			      value = input.at(0);
			      input = input.substr(1);
			   }
		     }
	            }
		     numOfTokens++;
//		     tokens.push_back(Token(type,value,line));
		     return Token(type, value, line);
		}
};
