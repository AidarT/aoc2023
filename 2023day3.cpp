#include <fstream>
#include <string>
#include <iostream>
#include <regex>
#include <map>
#include <vector>

using namespace std;

void fillMap(string line, const regex &re, const int &x, const int line_size, map<vector<int>, string> &dict) {
	cmatch res = cmatch{};
	int shift = 0;
	while (regex_search(line.c_str(), res, re)) {
		int y = res.prefix().second - res.prefix().first + shift;
		dict[{x, y}] = res[0];
		line = res.suffix();
		shift = line_size - line.size();
	}
}

int main() {
	int answer1 = 0;
	int answer2 = 0;
	regex reNum(R"(\d+)");
	regex reSymb(R"([^.|^\d])");
	regex reGear(R"([*])");
	map<vector<int>, string> symb;
	map<vector<int>, string> numb;
	map<vector<int>, string> gears;
	ifstream ifile("input1.txt", ios::in);
	if (ifile.is_open()) {
		string line;
		int x = 0; int y = 0;		
		while (getline(ifile, line)) {
			fillMap(line, reSymb, x, line.size(), symb);
			fillMap(line, reNum, x, line.size(), numb);
			fillMap(line, reGear, x, line.size(), gears);
			x++;
		}
		//part1
		for (const auto& n : numb) {
			x = n.first[0];
			y = n.first[1];
			int key = 0;
			for (int x_temp = x - 1; (x_temp <= x + 1) && (key == 0); x_temp++) {
				int bord_max = y + n.second.size();
				for (int y_temp = y - 1; y_temp <= bord_max; y_temp++) {
					if (symb.count({ x_temp, y_temp })) {
						answer1 += stoi(n.second);
						key = 1;
						break;
					}
				}
			}
		}

		//part2
		for (const auto& gear : gears) {
			x = gear.first[0];
			y = gear.first[1];
			vector <int> count;				
			for (const auto& n : numb) {
				int x_temp = n.first[0];
				int y_temp = n.first[1];
				if (abs(x_temp - x) <= 1) {
					if ((y-y_temp <= n.second.size() && y_temp <= y) || (y_temp-y <= 1 && y_temp > y)) {
						count.push_back(stoi(n.second));
					}
				}
			}
			if (count.size() == 2) {
				answer2 += count[0] * count[1];
			}
		}
		
		std::cout << answer1 << endl;
		std::cout << answer2 << endl;
	}
	return 0;
}
