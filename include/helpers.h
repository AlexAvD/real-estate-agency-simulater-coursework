#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>
#include "Random.h"

const std::vector<std::string> TRUE_WORDS = {
  "1", "Да", "да", "ДА",
  "Есть", "есть", "ЕСТЬ",
  "True", "true", "TRUE"
};

const std::vector<std::string> FALSE_WORDS =  {
  "0", "Нет", "нет", "НЕТ",
  "False", "false", "FALSE"
};

/* функция устанавливает кодировку консоли на utf-8 */
void setConsoleUTF8();

/* функция убирает все начальные и конечные пробельные символы  */
bool isBlank(const std::string & str);

/* функция разбивает строку "str" на токена по разделителю "separator" */
std::vector<std::string> tokenize(const std::string & str, char separator);

/* функция убирает все начальные, конечные и повторяющиеся подряд пробелы */
std::string normalizeLine(const std::string & str);

/**
 * функция соединяет конкатенирует vector "strings" состоящий из строк,
 * разделяю их разделителем "divider" 
 */
std::string concat(const std::vector<std::string> &strings, char divider = ' ');

/* функция убирает все начальные и конечные пробельные символы */
std::string trim(const std::string &str);

/** 
 * фукция создает рамку вокруг текста "str", длинной "width", состояющую из символа "border", 
 * с в верхними и нимжними отступами равными "paddingTopBottom"
 */
std::string fixedBox(const std::string &str, int width = 0, int paddingTopBottom = 0, char border = '#');

/* функция на основе ширины "width" довобаляет к строке "str" начальные пробелы и конечные пробелы */
std::string center(const std::string &str, int width);


/* функция возвращает строку состоющую только из кириллических символов */
std::string onlyCyrillic(const std::string &str);

/* шанс "percent"%, что будет true */
bool chance(int percent = 100);

/* функция возвращает количество совпадающих строк вектора "elements" в векторе "src" */
int countEqualElements(const std::vector<std::string> & src, const std::vector<std::string> & elements);

/* функция считывает файл и возвращает vector состоящий из строк файла */
std::vector<std::string> readFile(const std::string & pathToFile);

/** 
 *  функция считывает файл и возвращает vector, состоящий из конейнераов типа map, 
 *  состоящий из строк разбитых по разделителю "separator"   
 */
std::vector<std::map<std::string, std::string>> handleFile(const std::string & pathToFile, char separator);

/* функция перемешиват vector */
template <class T>
std::vector<T> *shuffleVector(std::vector<T> *src) {
  for (size_t i = 0, size = src->size() - 1; i < size; i++) {
    int randPos = Random::getInt(0, size);

    std::swap((*src)[i], (*src)[randPos]);
  }

  return src;
} 

/* вывод всех данных контейнреа vector */
template <class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> & vector) {
  for (size_t i = 0, size = vector.size(); i < size; i++) {
    out << vector[i] << "\n\n";
  }

  return out;
}

/* вывод всех данных контейнреа stack */
template <class T>
std::ostream& operator<<(std::ostream &out, std::stack<T> stack) {
  while (!stack.empty()) {
		out << stack.top() << "\n\n";

		stack.pop();
	} 
  return out;
}

/* вывод всех данных контейнреа map */
template <class T, class L> 
std::ostream& operator<<(std::ostream &out, const std::map<T, L> & map) {
  for (auto const & [key, val] : map) {
    out << key << " : " << val << '\n';
  }

  return out;
}

/* вывод всехо элементов вектораp в консоль */
template <class T>
void print(const std::vector<T> &vector);

/* манипулятор очищающий предыдущую строку */
std::ostream& clrll(std::ostream& out);

/* манипулятор очищающий текущую строку */
std::ostream& clrl(std::ostream& out);

/* манипулятор делающий текс вывода карсным */
std::ostream& colorred(std::ostream& out);

/* манипулятор границы вывода цветного текста */
std::ostream& endcolor(std::ostream& out);

/* манипулятор создающий элемент списка, добаляя в вывод "  • "  */
std::ostream& li(std::ostream& out);

/* генерирут строку, состоющую из "ch", которая повторяется "nRepeat" раз */
std::string divider(int nRepeat, const std::string &ch, bool newLine = true);

/* функция замараживает текущий поток на время "ms" */
void wait(int ms);

/**
 *  фунция возращает число от "min" до "max" на основе числа "num"
 *  с коэффициентов роста "growRate" 
 **/
double asymp(double num, double min, double max, double growRate = 0.001);

/* функция определяющая и возвращающая знак числа */
template <class T>
int getSign(T num) {
  return (num >= 0) - (num <= 0);
}

/* функция округляет число "num" д  о значения "digit" */
int roundTo(int num, int digit);

/* функция проверяет лежит ли число в диапазоне от "min" до "max" */
template <class T>
bool isBetween(T num, T min, T max) {
  return (num >= min) && (num <= max);
}

/* проверяет является ли строка "str" положительным словом из вектора "TRUE_WORDS" */
bool isTrueWord(const std::string &str);

/* проверяет является ли строка "str" отрицательным словом из вектора "FALSE_WORDS" */
bool isFalseWord(const std::string &str);
