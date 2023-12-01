#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

//int main() {
//	ifstream ifile("input1.txt", ios::in);
//	if (ifile.is_open()) {
//		string line;
//		int a, b;
//		getline(ifile, line);
//		stringstream ss(line);
//		ss >> a;
//		ss >> b;
//		int fg = 1;
//	}
//	return 0;
//}


int main() {
	ifstream ifile("input1.txt", ios::in);
	if (ifile.is_open()) {
		string line;
		int answer = 0;
		while (getline(ifile, line)) {
			stringstream ss(line);
			auto res = cmatch{};
			regex re(R"(\d)");
			string first = "-1", last = "-1";
			while (regex_search(line.c_str(), res, re)) {
				if (first == "-1") {
					first = *res[0].first;
				}
				last = *res[0].first;
				line = res.suffix();
			}
			answer += stoi(first + last);			
		}
		cout << answer << endl;
	}
	return 0;
}