#include <iostream>
#include <sstream>
#include "Predicate.h"

class Rule {
	private:
		Predicate headPredicate;
		vector<Predicate> predicates;
	public:
		Rule(Predicate a, vector<Predicate> b) {
			headPredicate = a;
			predicates = b;
		}

		string toString() {
			stringstream out;
		//	out << "Rules(" << predicates.size() << "):" << endl;
			if(predicates.size() > 0) {
				out << "  " <<  headPredicate.toString() << " :- ";
			}
			for(int i = 0; i < predicates.size(); i++) {
				if(i == predicates.size()-1) {
					out << predicates.at(i).toString() << ".";
				} else {
					out << predicates.at(i).toString() << ",";
				}
			}
			return out.str();
		}

//	vector<Parameter> parameters;
};
