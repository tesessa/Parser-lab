#include <vector>
#include <sstream>
#include "Rule.h"
#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"
#include "DataLogProgram.h"
#pragma once

//DatalogProgram, Rule, Predicate, and Parameter.
class Parser {
	private:
		vector<Token> tokens;
		int schemes = 0;
		int facts = 0;
		int rules = 0;
		int queries = 0;
		bool failure = false;
		string dataLog = "";
	//	Token fail;
		Predicate head = Predicate();
		vector<string> domain;	
		vector<Parameter> parameters;
		vector<Predicate> predicates;
		vector<Rule> rulesVector;
		stringstream output;
	public:
		Parser(const vector<Token>& tokens) : tokens(tokens) {}
		
		TokenType tokenType() const {
			return tokens.at(0).getType();
		} 

		string tokenValue() const {
			return tokens.at(0).getValue();
		}

		void advanceToken() {
			tokens.erase(tokens.begin());
		}
		
		void throwError() {
			cout << "error" << endl;
		}

		void match(TokenType t) {
			if(failure == true) {
				return;
			}
			Token s = tokens.at(0);
//			cout << s.toString() << endl;
//			cout << "match: " << t << endl;
			if(tokens.at(0).getType() == t) {
//				cout << "Success: " << tokens.at(0).toString() << endl;
				advanceToken();
			} else {
		//		cout << "failure " << s.toString() << endl;
//				cout << "in match" << endl;
				dataLog = "Failure!\n  " + s.toString() + "\n";
//				cout << dataLog << endl;
				failure = true;
	//			fail = token.at(0);
				//cout << "Failure: ";
				//cout << tokens.at(0).toString() << endl;
			}
		}

		void datalogProgram() { 
			match(SCHEMES);
			match(COLON);
			scheme();
			schemeList();
			output << "Schemes(" << schemes << "):" << endl;
//			cout << "B" << endl;
			for(Predicate loop : predicates) {
				output << "  " << loop.toString() << endl;
			}
			predicates.clear();
			match(FACTS);
			match(COLON);
			factList();
			output << "Facts(" << facts << "):" << endl;
			for(Predicate loop : predicates) {
				output << "  " << loop.toString() << "." << endl;
			}
			predicates.clear();
			match(RULES);
			match(COLON);
			ruleList();
			output << "Rules(" << rules << "):" << endl;
			for(Rule loop : rulesVector) {
				if(loop.toString() != "") {
					output << loop.toString() << endl;
				}
			}
			//Rule temp = Rule(head, predicates);
			//if(temp.toString() != "") {
			//	output << temp.toString() << endl;
			//}
			predicates.clear();
			match(QUERIES);
			match(COLON);
			query();
			queryList();
			output << "Queries(" << queries << "):\n";
			for(Predicate loop : predicates) {
				output << "  " << loop.toString() << "?" << endl;
			}
			match(EOFILE);
			if(failure == false) {
				dataLog = "Success!\n" + output.str();
			}
			DataLogProgram data = DataLogProgram(dataLog, domain, failure);
			cout << data.toString();
		}

		void schemeList() {
			if (tokenType() == ID && failure == false) {
				scheme();
				schemeList();
			} else {
				//lambda
			}
		}

		void factList() {
			if(tokenType() == ID && failure == false) {
				fact();
				factList();
			} else {
				//lambda
			}
		}

		void ruleList() {
			if(tokenType() == ID && failure == false) {
				rule();
				ruleList();
			} else {
				//lambda
			}
		}

		void queryList() {
			if(tokenType() == ID && failure == false) {
				query();
				queryList();
			} else {
				//lambda
			}
		}
		
		void scheme() {
			 string name = tokens.at(0).getValue();
                	 match(ID);
                         match(LEFT_PAREN);
			 Parameter p = Parameter(tokens.at(0).getValue());
			 parameters.push_back(p);
                         match(ID);
                         idList();
                         match(RIGHT_PAREN);
			 Predicate temp = Predicate(name, parameters);
			 predicates.push_back(temp);
			 schemes++;
			 parameters.clear();
//			 cout << "A" << endl;
                }

                void fact() {
			string name = tokens.at(0).getValue();
                	match(ID);
                        match(LEFT_PAREN);
			if(tokenType() == STRING) {
				string domainValue = tokens.at(0).getValue();
				domain.push_back(domainValue);
			}
			Parameter p = Parameter(tokens.at(0).getValue());
			parameters.push_back(p);
                        match(STRING);
                        stringList();
                        match(RIGHT_PAREN);
                        match(PERIOD);
			Predicate temp = Predicate(name, parameters);
			predicates.push_back(temp);
			facts++;
			parameters.clear();
                }

		void rule() {
			headPredicate();
			match(COLON_DASH);
			predicate();
			predicateList();
			match(PERIOD);
			rules++;
			Rule temp = Rule(head, predicates);
			rulesVector.push_back(temp);
			predicates.clear();
			parameters.clear();
			head = Predicate();
			
		}

		void query() {
			predicate();
			match(Q_MARK);
			queries++;
			parameters.clear();
		}

		void headPredicate() {
			string name = tokens.at(0).getValue();
			match(ID);
			match(LEFT_PAREN);
			Parameter p = tokens.at(0).getValue();
			parameters.push_back(p);
			match(ID);
			idList();
			match(RIGHT_PAREN);
			head = Predicate(name, parameters);
			parameters.clear();
		}

		void predicate() {
			string name = tokens.at(0).getValue();
			match(ID);
			match(LEFT_PAREN);
			parameter();
			parameterList();
			match(RIGHT_PAREN);
			Predicate test = Predicate(name, parameters);
			predicates.push_back(test);
			parameters.clear();
			//cout << test.toString() << endl;
		}

		void predicateList() {
			if (tokenType() == COMMA) {
				match(COMMA);
				predicate();
				predicateList();
			} else {
				//lambda
			}
		}

		void parameterList() {
			if (tokenType() == COMMA) {
				match(COMMA);
				parameter();
				parameterList();
			} else {
				//lambda
			}
		}

		void stringList() {
			if (tokenType() == COMMA) {
				match(COMMA);
				Parameter p = Parameter(tokens.at(0).getValue());
				parameters.push_back(p);
                        	if(tokenType() == STRING) {
                                	string domainValue = tokens.at(0).getValue();
                                	domain.push_back(domainValue);
                        	}	
				match(STRING);
				stringList();
			} else {
				//lambda
			}
		}

		void idList() {
			if (tokenType() == COMMA) {
				match(COMMA);
				Parameter p = Parameter(tokens.at(0).getValue());
  				parameters.push_back(p);
				match(ID);
				idList();
			} else {
				//lambda
			}
		}

		void parameter() {
		        Parameter p = Parameter(tokens.at(0).getValue());
			parameters.push_back(p);
                        if (tokenType() == STRING) {
                                match(STRING);
                        } else if (tokenType() == ID) {
                                match(ID);
                        }
		//	cout << "Parameter: " << p.toString() << endl;
                }
		
};
