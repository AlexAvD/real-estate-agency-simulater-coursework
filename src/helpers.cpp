#include "helpers.h"

void setRus() {
  system("chcp 65001 > nul");
}

bool isBlank(const std::string & str) {
  for (char ch : str) {
    if (!isspace(ch)) {
      return false;
    }
  }

  return true;
}

std::vector<std::string> tokenize(const std::string & str, char separator) {
  std::vector<std::string> result;

	for (size_t start = 0, end = 0, len = str.length(); end < len; ++end) {
		if (str[end] != separator) {
			if (str[end + 1] == separator || str[end + 1] == '\0') {
				result.push_back(str.substr(start, end - start + 1));
			} else if (str[end - 1] == separator) {
				start = end;
			} 
		}
	}

  return result;
}

std::string normalizeLine(const std::string & str) {
  if (str.length() == 0) {
    return "";
  }

  std::vector<std::string> tokens;

	for (size_t start = 0, end = 0, len = str.length(); end < len; ++end) {
		if (!isspace(str[end])) {
			if (isspace(str[end + 1]) || str[end + 1] == '\0') {
				tokens.push_back(str.substr(start, end - start + 1));
			} else if (isspace(str[end - 1])) {
				start = end;
			} 
		}
	}

  return (tokens.size() != 0) ? concat(tokens, ' ') : "";
}

std::string trim(const std::string & str) {
  size_t start = -1;
  size_t end = str.length();

  while (isspace(str[++start]))
    ;

  while (isspace(str[--end]))
    ;

  return str.substr(start, end - start + 1);
}

std::string concat(const std::vector<std::string> & strings, char ch) {
  std::string result = "";
  size_t i = -1;
  size_t len = strings.size() - 1;

  while (++i < len) {
    result += strings[i] + ch;
  }

  result += strings[i];

  return result;
}

//std::vector<std::map<std::string, std::string>> 

std::vector<std::string> readFile(const std::string & fileName) {
	std::ifstream file(fileName);
	std::vector<std::string> result;
	std::string line;

	if (file.is_open()) {
		
		while (!file.eof()) {
			getline(file, line);

			result.push_back(line);
		}
	}

	return result;

	/* std::ifstream file(fileName);
	std::vector<std::map<std::string, std::string>> result;
	

	if (file.is_open()) {
		std::map<std::string, std::string> item;
		std::string line;

		while (!file.eof()) {
			getline(file, line);

			if (isBlank(line) && item.size() != 0) {
				result.push_back(item);
				item.clear();
			} else {
				if (line.find(':') != std::string::npos) {
					std::vector<std::string> tokenizedLine = tokenize(line, ':');
					std::string key = normalizeLine(tokenizedLine[0]);
					std::string val = normalizeLine(tokenizedLine[1]);

					item[key] = val; 
				}
			}
		}

		file.close(); */
	//} 
	 
  // return result;
}

std::vector<std::map<std::string, std::string>> 
handleFile(const std::string & fileName, char separator) {
	std::vector<std::string> lines = readFile(fileName);
	std::vector<std::map<std::string, std::string>> result;
	std::map<std::string, std::string> item;

	for (const std::string & line : lines) {
			if (isBlank(line) && item.size() != 0) {
				result.push_back(item);
				item.clear();
			} else {
				if (line.find(separator) != std::string::npos) {
					std::vector<std::string> tokenizedLine = tokenize(line, ':');
					std::string key = normalizeLine(tokenizedLine[0]);
					std::string val = normalizeLine(tokenizedLine[1]);

					item[key] = val; 
				}
			}
	}

	return result;
}

bool chance(int percent) {
	percent = (percent > 100) ? 100 : ((percent < 0) ? 0 : percent);

	return (Random::getInt(1, 100) <= percent); 
}

int countEqualElements(const std::vector<std::string> & src, const std::vector<std::string> & elements) {
	size_t nSimilar = 0;

	for (const std::string & str : elements) {
		auto it = std::find(src.begin(), src.end(), str);

		if (it != src.end()) {
			++nSimilar;
    }
	}

	return nSimilar;
}

std::ostream& clrll(std::ostream& out) {
    out << "\x1b[1A\x1b[0K";
    return out;
}

std::ostream& clrl(std::ostream& out) {
    out << "\r\x1b[0K";
    return out;
}


template <class T>
void print(const std::vector<T> &v) {
  for (size_t i = 0, size = v.size(); i < size; i++) {
    std::cout << v[i] << ", ";
  }

  std::cout << '\n';
}


template void print<std::string>(const std::vector<std::string> &v);

/* 

asim Example:

asim(i, 0, 100, 0):     | asim(i, 0, 100, 1):   | asim(i, 0, 100, 5):   | asim(i, 0, 100, 10):
----------------------------------------------------------------------------------------------
 0                      |  0                    |  0                    |  0
50                      | 50                    | 16                    |  9
66                      | 66                    | 28                    | 16
75                      | 75                    | 37                    | 23
80                      | 80                    | 44                    | 28
83                      | 83                    | 50                    | 33
85                      | 85                    | 54                    | 37
87                      | 87                    | 58                    | 41
88                      | 88                    | 61                    | 44
90                      | 90                    | 64                    | 47
90                      | 90                    | 66                    | 50
...                     | ...                   | ...                   | ...
100                     | 100                   | 100                   | 100

*/

double asymp(double num, double min, double max, double growRate) {
	growRate = (growRate < 1) ? 1 : growRate;

	return (max * num + min * growRate) / (num + growRate);
}