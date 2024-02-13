#include <iostream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

class DataLogProgram {
	private:
		string output;
		vector<string> domain;
		bool failure;
	public:
		DataLogProgram(string o, vector<string> d, bool f) {
			output = o;
			domain = d;
			failure = f;
		}

		string toString() {
			stringstream factsDomain;
//			sort(domain.begin(), domain.end());
//			for(string loop : domain) {
//				cout << loop << endl;
//			}
			for(int i = 0; i < domain.size(); i++) {
				for(int j = 1; j < domain.size(); j++) {
					if(domain.at(i) == domain.at(j) && (j!=i)) {
						domain.erase(domain.begin()+j);
						j--;
					}
				}
			}
			sort(domain.begin(), domain.end());
			factsDomain << "Domain(" << domain.size() << "):\n";
			for(int i = 0; i < domain.size(); i++) {
				factsDomain << "  " <<  domain.at(i) << endl;
			}
			string finalOutput = "";
			if(failure == false) {
				finalOutput = output + factsDomain.str();
			} else {
				finalOutput = output;
			}
			return finalOutput;
		}
};
