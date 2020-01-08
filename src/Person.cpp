#include "Person.h"

const std::vector<std::vector<std::string>> Person::names_ = {
  {
    "Анна", "Тамара", "Раиса", "Лариса", "Зоя", "Ольга", "Полина", "Елена", 
    "Юлия", "Маргарита", "Любовь", "Виктория", "Алёна", "Татьяна", "Людмила", 
    "Наталья", "Валентина", "Алла", "Элла", "Арина"
  },
  {
    "Виктор", "Юрий", "Антон", "Артём", "Владислав", "Богдан", "Алексей", 
    "Иван", "Лев", "Руслан", "Фёдор", "Вадим", "Павел", "Ярослав", "Аркадий", 
    "Семён", "Даниил", "Евгений", "Григорий", "Валерий"
  }
};

const std::vector<std::vector<std::string>> Person::surnames_ = {
  {
    "Киселёва", "Казакова", "Горбачёва", "Щербакова", "Зимина", "Наумова", "Зыкова",
    "Ермакова", "Маркова", "Федотова", "Зиновьева", "Меркушева", "Кулакова", "Овчинникова", 
    "Алексеева", "Лаврентьева", "Ильина", "Тетерина", "Федосеева", "Муравьёва"
  },
  {
    "Афанасьев", "Фокин", "Колобов", "Богданов", "Самсонов", "Лукин", "Зыков",
    "Фомичёв", "Владимиров", "Николаев", "Моисеев", "Фомин", "Самойлов", "Блинов", 
    "Дьячков", "Туров", "Орехов", "Субботин", "Фадеев", "Наумов",
  }
};


const std::vector<std::vector<std::string>> Person::midnames_ = {
  {
    "Гаврииловна", "Даниловна", "Васильевна", "Иннокентьевна", "Дмитриевна", "Егоровна", 
    "Богдановна", "Святославовна", "Ростиславовна", "Александровна", "Семёновна", 
    "Георгиевна", "Андреевна", "Степановна", "Борисовна", "Матвеевна", "Тимуровна", 
    "Витальевна", "Львовна", "Романовна"
  },
  {
    "Владиславович", "Вадимович", "Семёнович", "Вячеславович", "Андреевич", "Степанович", 
    "Евгеньевич", "Геннадьевич", "Михайлович", "Олегович", "Григорьевич", "Ростиславович", 
    "Святославович", "Витальевич", "Петрович", "Даниилович", "Ярославович"
  }
};

Person::Person() {
  name_ = "";
  surname_ = "";
  midname_ = "";
  gender_ = 0;
  passportData_ = "";
  age_ = 0;
  salary_ = 0;
  money_ = 0;
}

Person::Person(const Person & person) {
  name_ = person.name_;
  surname_ = person.surname_;
  midname_ = person.midname_;
  passportData_ = person.passportData_;
  gender_ = person.gender_;
  age_ = person.age_;
  salary_ = person.salary_;
  money_ = person.money_;
}

std::string Person::getRandomName(int gender) {
  if (gender == -1) {
    gender = Random::getInt(0, 1);
  } else {
    gender %= 2;
  }

  return names_[gender][Random::getInt(0, names_.size() - 1)];
}

std::string Person::getRandomSurname(int gender) {
  if (gender == -1) {
    gender = Random::getInt(0, 1);
  } else {
    gender %= 2;
  }

  return surnames_[gender][Random::getInt(0, surnames_.size() - 1)];
}

std::string Person::getRandomMidname(int gender) {
  if (gender == -1) {
    gender = Random::getInt(0, 1);
  } else {
    gender %= 2;
  }

  return midnames_[gender][Random::getInt(0, midnames_.size() - 1)];
}

// setters

void Person::setName(const std::string & name) {
  name_ = name;
}

void Person::setSurname(const std::string & surname) {
  surname_ = surname;
}

void Person::setMidname(const std::string & midname) {
  midname_ = midname;
}

void Person::setFullName(const std::string & fullName) {
  std::vector<std::string> tokens = tokenize(fullName, ' ');

  setSurname(tokens[0]);
  setName(tokens[1]);
  setMidname(tokens[2]);
}

void Person::setGender(bool gender) {
  gender_ = gender;
}

void Person::setGender(const std::string &gender) {
  if (gender.find("м") != std::string::npos || gender.find("М") != std::string::npos) {
    gender_ = 1;
  } else if (gender.find("ж") != std::string::npos || gender.find("Ж") != std::string::npos) {
    gender_ = 0;
  }
}

void Person::setPassportData(const std::string & passportData) {
  passportData_ = passportData;
}

void Person::setAge(int age) {
  age_ = age;
}

void Person::setAge(const std::string &age) {
  age_ = std::stoi(age);
}

void Person::setSalary(int salary) {
  salary_ = salary;
}

void Person::setSalary(const std::string &salary) {
  salary_ = std::stoi(salary);
}

void Person::setMoney(long money) {
  money_ = money;
}

void Person::setMoney(const std::string &money) {
  money_ = std::stol(money);
}


void Person::setRandomProperties() {
  setGender(Random::getBool());
  setName(getRandomName());
  setSurname(getRandomSurname());
  setMidname(getRandomMidname());
  setAge(Random::getInt(25, 60));
  setSalary(Random::getInt(20, 150) * 1000);
  setMoney(Random::getInt(50000, 200000));

  std::stringstream ss;

  ss.fill('0');
  ss 
    << "60" << Random::getInt(80, 99) 
    << std::setw(3) << Random::getInt(0, 500) 
    << std::setw(3) << Random::getInt(0, 999);
  
  setPassportData(ss.str());
}

// getters

std::string Person::getName() const {
  return name_;
}

std::string Person::getSurname() const {
  return surname_;
}

std::string Person::getMidname() const {
  return midname_;
}

std::string Person::getFullName() const {
  std::string fullName = surname_ + ' ' + name_ + ' ' + midname_;

  return fullName;
}

bool Person::getGender() const {
  return gender_;
}

std::string Person::getPassportData() const {
  return passportData_;
}

int Person::getAge() const {
  return age_;
}
 
int Person::getSalary() const {
  return salary_;
}

long Person::getMoney() const {
  return money_;
}



// others

std::ostream& operator<<(std::ostream &out, const Person &person) {
  return person.print(out);
}

std::ostream& Person::print(std::ostream &out) const {
  out << "ФИО: " << getFullName() << '\n'
      << "Пол: " << (gender_ ? "муж." : "жен.") << '\n'
      << "Возраст: " << age_ << '\n'
      << "Паспортные данные: " << passportData_ << '\n'
      << "Зарплата: " << salary_ << " руб." << '\n'
      << "Деньги: " << money_ << " руб." << '\n';

  return out;
}
