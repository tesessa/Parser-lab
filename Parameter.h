#include <iostream>

#pragma once

class Parameter {
	private:
		string name;
	public:
		Parameter(string name) : name(name) {}
		string toString() {
			return name;
		}
};
