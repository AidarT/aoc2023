#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

string number_(const string &line, bool first, const map<string, string> &m_dict) {	
	int index = (first ? line.size()+1 : -1);
	int index_temp;
	string ans;
	if (first) {
		for (const auto& el: m_dict) {
			index_temp = line.find(el.first, 0);
			if (index_temp < index && index_temp >= 0) {
				ans = el.second;
				index = index_temp;
			}
		}
	}
	else {
		for (const auto& el : m_dict) {
			index_temp = line.rfind(el.first);
			if (index_temp > index) {
				ans = el.second;
				index = index_temp;
			}
		}
	}
	return ans;
}

int main() {
	map<string, string> m_dict;
	m_dict["one"] = "1";
	m_dict["two"] = "2";
	m_dict["three"] = "3";
	m_dict["four"] = "4";
	m_dict["five"] = "5";
	m_dict["six"] = "6";
	m_dict["seven"] = "7";
	m_dict["eight"] = "8";
	m_dict["nine"] = "9";
	m_dict["1"] = "1";
	m_dict["2"] = "2";
	m_dict["3"] = "3";
	m_dict["4"] = "4";
	m_dict["5"] = "5";
	m_dict["6"] = "6";
	m_dict["7"] = "7";
	m_dict["8"] = "8";
	m_dict["9"] = "9";
	ifstream ifile("input1.txt", ios::in);
	if (ifile.is_open()) {
		string line, line2;
		int answer1 = 0;
		int answer2 = 0;
		while (getline(ifile, line)) {
			stringstream ss(line);
			line2 = line;
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
			answer1 += stoi(first + last);
			
			// part 2
			
			first = number_(line2, true, m_dict);
			last = number_(line2, false, m_dict);
			answer2 += stoi(first + last);


		}
		cout << answer1 << endl;
		cout << answer2 << endl;
	}
	return 0;
}
