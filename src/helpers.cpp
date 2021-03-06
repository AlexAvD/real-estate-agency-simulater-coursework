#include "helpers.h"

void setConsoleUTF8() {
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

std::vector<std::string> tokenize(const std::string &str, char separator) {
  std::vector<std::string> result;

	for (size_t start = 0, end = 0, len = str.length(); end < len; ++end) {
		if (str[end] != separator) {
			if (str[end + 1] == separator || str[end + 1] == '\0') {
				std::string substr = str.substr(start, end - start + 1);

				result.push_back(substr);
			} else if (str[end - 1] == separator) {
				start = end;
			} 
		}
	}

  return result;
}

std::string normalizeLine(const std::string &str) {
  if (isBlank(str)) {
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
		} else {
			++start;
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

std::string fixedBox(const std::string &str, int width, int paddingTopBottom, char border) {
	int strLen = str.length() - onlyCyrillic(str).length() / 2;
	int paddingLeftAndRight;
	int paddingLeft;
	int paddingRight;
	std::stringstream result;

	
	width = (width < strLen) ? strLen : width;
	paddingTopBottom = (paddingTopBottom < 0) ? 0 : paddingTopBottom;
	
	paddingLeftAndRight = width - strLen;
	paddingRight = paddingLeftAndRight / 2;
	paddingLeft = paddingLeftAndRight - paddingRight;

	// top outline
	result.fill(border);
	result << std::setw(width) << border << "\n";

	result.fill(' ');	

	for (int i = 0; i < paddingTopBottom; i++) {
		result << border << std::setw(width - 1) << border << "\n";
	}
	
	result 
		// left padding
		<< border << std::setw(paddingLeft - 1) << " "
		<< str
		// right padding
		<< std::setw(paddingRight - 1) << " " << border << "\n";

	for (int i = 0; i < paddingTopBottom; i++) {
		result << border << std::setw(width - 1) << border << "\n";
	}

	// bottom outline
	result.fill(border);
	result << std::setw(width) << border << "\n";

	
	return result.str();
}


std::string center(const std::string &str, int width) {
	// расчет размера строки с кирилическими символами 
	int len = str.length() - onlyCyrillic(str).length() / 2;

	if (len >= width) {
		return str;
	} 

	int paddingLeftRight = (width - len) / 2;
	
	std::stringstream ss;

	ss.fill(' ');
	
	ss 
		<< std::setw(paddingLeftRight) << "" 
		<< str
		<< std::setw(paddingLeftRight) << "";

	return ss.str();
}

std::string onlyCyrillic(const std::string &str) {
	std::string result = "";

	for (auto ch : str) {
		if (!isgraph(ch) && !isspace(ch)) {
			result.push_back(ch);
		}
	}

	return result;
}

std::string concat(const std::vector<std::string> & strings, char divider) {
  std::string result = "";
  size_t i = -1;
  size_t len = strings.size() - 1;

  while (++i < len) {
    result += strings[i] + divider;
  }

  result += strings[i];

  return result;
}

std::vector<std::string> readFile(const std::string & pathToFile) {
	std::ifstream file(pathToFile);
	std::vector<std::string> result;
	std::string line;

	if (file.is_open()) {
		
		while (!file.eof()) {
			getline(file, line);

			result.push_back(line);
		}

		file.close();
	} else {
		std::cerr << colorred << "Не удалось открыть файл \"" << pathToFile << "\"\n";
	}

	return result;
}

std::vector<std::map<std::string, std::string>> 
handleFile(const std::string & pathToFile, char separator) {
	std::vector<std::string> lines = readFile(pathToFile);
	std::vector<std::map<std::string, std::string>> result;
	std::map<std::string, std::string> item;

	for (const std::string & line : lines) {
		if (isBlank(line) && item.size() != 0) {
			result.push_back(item);
			item.clear();
		} else {
			if (line.find(separator) != std::string::npos) {
				std::vector<std::string> tokenizedLine = tokenize(line, ':');

				if (tokenizedLine.size() >= 2) {
					std::string key = normalizeLine(tokenizedLine[0]);
					std::string val = normalizeLine(tokenizedLine[1]);

					item[key] = val; 
				}
			}
		}
	}

	if (item.size()) {
		result.push_back(item);
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

std::ostream& colorred(std::ostream& out) {
	out << "\033[1;31m";

	return out;
}

std::ostream& endcolor(std::ostream& out) {
	out << "\033[0m";

	return out;
}

std::ostream& li(std::ostream& out) {
	out << "  • ";

	return out;
}

std::string divider(int nRepat, const std::string &ch, bool newLine) {
	std::string d;

	while(nRepat-- > 0) { d += ch; }

	if (newLine) { d += "\n"; }
	
	return d;
}

template <class T>
void print(const std::vector<T> &vector) {
  for (size_t i = 0, size = vector.size(); i < size; i++) {
    std::cout << vector[i] << ", ";
  }

  std::cout << '\n';
}

template void print<std::string>(const std::vector<std::string> &v);



/* 

asim при i от 0 до ...:

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
	if (num < 0) {
		num = 0;
	}

	if (growRate <= 0) {
		growRate = 0;
		num = 1;
	}

	return (max * num + min * growRate) / (num + growRate);
}

void wait(int ms) {
 std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int roundTo(int num, int digit) {
  return (num % digit) ? (num + digit * getSign(num) - (num % digit)) : num;
}

bool isTrueWord(const std::string &str) {
	return (std::find(TRUE_WORDS.begin(), TRUE_WORDS.end(), str) != TRUE_WORDS.end());
}

bool isFalseWord(const std::string &str) {
	return (std::find(FALSE_WORDS.begin(), FALSE_WORDS.end(), str) != FALSE_WORDS.end());
}