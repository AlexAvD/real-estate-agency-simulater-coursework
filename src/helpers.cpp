#include "helpers.h"

void setRus() {
  system("chcp 65001 > nul");
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

  return concat(tokens, ' ');;
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
