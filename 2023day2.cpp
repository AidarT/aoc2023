#include <fstream>
#include <string>
#include <iostream>
#include <regex>

using namespace std;



int main2() {
	auto res = cmatch{};
	regex re(R"(\d+)");
	ifstream ifile("input1.txt", ios::in);
	if (ifile.is_open()) {
		string line;
		int answer1 = 0;
		while (getline(ifile, line)) {
			string delimiter = ":";
			string game = line.substr(0, line.find(delimiter));
			regex_search(game.c_str(), res, re);
			int game_num = int(*res[0].first) - '0';
			line = line.substr(line.find(delimiter)+1, line.size()-1);
			delimiter = ";";
			while (line.find(delimiter)) {

			}
			
			string first = "-1", last = "-1";
			while (regex_search(line.c_str(), res, re)) {
				if (first == "-1") {
					first = *res[0].first;
				}
				last = *res[0].first;
				line = res.suffix();
			}
			answer1 += stoi(first + last);


		}
		cout << answer1 << endl;
	}
	return 0;
}
