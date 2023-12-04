#include <fstream>
#include <string>
#include <iostream>
#include <regex>
#include <map>
#include <vector>

using namespace std;



int main() {
	int answer1 = 0;
	int answer2 = 0;
	cmatch res = cmatch{};
	regex reNum(R"(\d+)");
	regex reSymb(R"([^.|^\d])");
	map<vector<int>, string> symb;
	map<vector<int>, string> numb;
	map<vector<int>, string> gears;
	ifstream ifile("input1.txt", ios::in);
	if (ifile.is_open()) {
		string line;
		int x = 0; int y = 0;
		while (getline(ifile, line)) {
			string line2 = line;
			int shift = 0;
			while (regex_search(line2.c_str(), res, reSymb)) {
				y = res.prefix().second - res.prefix().first + shift;
				symb[{x,y}] = res[0];
				line2 = res.suffix();
				shift = line.size() - line2.size();
			}
			line2 = line;
			shift = 0;
			while (regex_search(line2.c_str(), res, reNum)) {
				y = res.prefix().second - res.prefix().first + shift;
				numb[{x, y}] = res[0];
				line2 = res.suffix();
				shift = line.size()-line2.size();
			}
			x++;
		}
		//part1
		for (const auto& el : numb) {
			x = el.first[0];
			y = el.first[1];
			int key = 0;
			for (int x_temp = x - 1; (x_temp <= x + 1) && (key == 0); x_temp++) {
				int bord_max = y + el.second.size();
				for (int y_temp = y - 1; y_temp <= bord_max; y_temp++) {
					if (symb.count({ x_temp, y_temp })) {
						answer1 += stoi(el.second);
						key = 1;
						break;
					}
				}
			}
			
		}

		//part2
		
		cout << answer1 << endl;
	}
	return 0;
}
