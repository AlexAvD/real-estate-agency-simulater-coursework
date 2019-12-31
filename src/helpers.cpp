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
    char ch = str[end];
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

  return str.substr(start, start + end);
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

std::vector<std::map<std::string, std::string>> readFile(const std::string & fileName) {
	std::ifstream file(fileName);
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

		file.close();
	} 
	 
  return result;
}


/* std::ostream& operator<<(std::ostream &out, const std::vector<std::string> & v) {
	out << "[ ";

  for (size_t i = 0, len = v.size(); i < len; i++) {
    out << v[i];

    if (i != len - 1) {
      out << ", ";
    } else {
			out << " ";
		}
  }

  out << ']' << std::endl;

  return out;
} */