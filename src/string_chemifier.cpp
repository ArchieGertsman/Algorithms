#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <locale>
#include <vector>
#include <sstream>
#include <algorithm>

std::set<std::string> elems;
const auto MAX_SYM_LEN = 2;

std::vector<std::string> split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (std::getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

std::string chemifySym(std::string sym) {
	std::locale loc;
	sym[0] = std::toupper(sym[0], loc);
	if (sym.length() > 1) {
		sym[1] = std::tolower(sym[1], loc);
	}
	return sym;
}

std::string chemifyWord(const std::string &str) {
	for (auto sym_len = MAX_SYM_LEN; sym_len > 0; --sym_len) {
		if (sym_len > str.length()) continue;

		std::string sym = chemifySym(str.substr(0, sym_len));

		if (elems.find(sym) != elems.end()) {
			if (str.length() == sym_len) {
				return sym;
			}

			std::string rest = chemifyWord(str.substr(sym_len));
			if (!rest.empty()) {
				return sym + rest;
			}
		}
	}

	return "";
}

std::string chemify(const std::string &str) {
	auto toks = split(str, ' ');
	std::string ret = "";
	std::for_each(toks.begin(), toks.end(), [&](const std::string &str) { 
		std::string word = chemifyWord(str);
		ret += (!word.empty() ? word : str) + ' '; 
	});
	return ret;
}

int main() {
	std::ifstream stream("elements.txt");
	std::string line;
	while (std::getline(stream, line)) {
		elems.insert(line);
	}
	stream.close();

	std::cout << chemify("obtain money") << '\n'; // output: OBTaIn MoNeY
}
