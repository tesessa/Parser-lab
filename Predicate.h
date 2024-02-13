#include "Parameter.h"
#include <vector>
#include <iostream>
#include <sstream>
#pragma once

class Predicate {
	private:
		string name;
		vector<Parameter> parameters;
	public:
		Predicate(string a, vector<Parameter> b) {
			name = a;
			parameters = b;
		}
		Predicate() {
			name = "";
		}
		string toString() {
			stringstream out;
			out << name << "(";
			for(int i = 0; i < parameters.size(); i++) {
				if(i != parameters.size()-1) {
					out << parameters.at(i).toString();
					out << ",";
				} else {
					out << parameters.at(i).toString();
				}
			}
			out << ")";
			return out.str();
		}
};
