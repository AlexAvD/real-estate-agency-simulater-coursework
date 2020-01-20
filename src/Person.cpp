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
}

Person::Person(const Person & person) {
  name_ = person.name_;
  surname_ = person.surname_;
  midname_ = person.midname_;
  passportData_ = person.passportData_;
  gender_ = person.gender_;
  age_ = person.age_;
}

Person::~Person() {
  
}


std::string Person::getRandomName(bool gender) {
  return names_[gender][Random::getInt(0, names_[gender].size() - 1)];;
}

std::string Person::getRandomSurname(bool gender) {
  return surnames_[gender][Random::getInt(0, surnames_[gender].size() - 1)];
}

std::string Person::getRandomMidname(bool gender) {
  return midnames_[gender][Random::getInt(0, midnames_[gender].size() - 1)];
}

std::map<std::string, std::string> 
Person::setProperties(const std::map<std::string, std::string> &properties) {
  std::map<std::string, std::string> remainingProperties;

  for (const auto &[key, val] : properties) {
    if (key == "Имя") {
      setName(val);
    } else if (key == "Фамилия") {
      setSurname(val);
    } else	if (key == "Отчество") {
      setMidname(val);
    } else if (key == "ФИО") {
      setFullName(val);
    } else if (key == "Пол") {
      setGender(val);
    } else if (key == "Возраст") {
      setAge(std::stoi(val));
    } else if (key == "Паспортные данные") {
      setPassportData(val);
    } else {
      remainingProperties[key] = val;
    }
  }

  return remainingProperties;
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
  if (
      gender.find("м") != std::string::npos || 
      gender.find("М") != std::string::npos
    ) {
    gender_ = 1;
  } else {
    gender_ = 0;
  }
}

void Person::setPassportData(const std::string &passportData) {
  passportData_ = passportData;
}

void Person::setAge(int age) {
  age_ = age;
}


void Person::setRandomProperties(int gender) {
  gender = (gender == -1) ? Random::getInt(0, 1) : gender % 2;

  setGender(gender);
  setName(getRandomName(gender));
  setSurname(getRandomSurname(gender));
  setMidname(getRandomMidname(gender));
  setAge(Random::getInt(25, 60));

  std::stringstream ss;

  ss.fill('0');

  ss 
    << "60"         << Random::getInt(80, 99) 
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
  return surname_ + ' ' + name_ + ' ' + midname_;
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

// others

std::ostream& operator<<(std::ostream &out, const Person &person) {
  return person.print(out);
}

std::ostream& Person::print(std::ostream &out) const {
  out 
    << li << "ФИО: " << getFullName() << '\n'
    << li << "Пол: " << (gender_ ? "муж." : "жен.") << '\n'
    << li << "Возраст: " << age_ << '\n'
    << li << "Паспортные данные: " << passportData_ << '\n';

  return out;
}
