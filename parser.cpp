#include <ctype.h>
#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "manager.h"


namespace parser {
using namespace std;

class Variable {
 public:
  Variable(string n, vector<double> v) {
    name = n;
    value = v;
  }
  Variable(vector<double> v) {
    name = "MyVector";
    value = v;
  }
  string getName() { return name; }
  vector<double>& getValue() { return value; }
  void setName(string s) { name = s; }
  void setValue(vector<double> n) { value = n; }
  Variable(const VariableData& VD) : name{ VD.shortNaming.toStdString() } {
      value = VD.measurements.toVector().toStdVector();
  }

 private:
  string name;
  vector<double> value;
  //double err;
};

vector<Variable> Variable_Data = {};

bool isUnique(QString n) {
  return Manager::instance()->isInManager(n);
}

template <typename T>
void remove(std::vector<T>& v, size_t index) {
  v.erase(v.begin() + index);
}

Variable VariableGet(string s) {
  VariableData* var = Manager::instance()->getVariableOrCalculated(QString::fromStdString(s));
  return Variable(*var);
}

int symPriority(char c) {
  int p = 0;
  switch (c) {
    case '+':
    case '-':
      p = 2;
      break;
    case '/':
    case '*':
      p = 3;
      break;
    case '^':
      p = 4;
      break;
    case '(':
      p = 0;
      break;
    case ')':
      p = 1;
      break;
    default:
      p = 230;
      break;
  }
  return p;
}

pair<vector<string>, pair<bool, string>> parse(string s) {
  vector<string> output;
  vector<char> sym;
  int i = 0;
  int number_of_brackets = 0;
  string lvalue = "";
  bool eq = false;
  for (char c : s) {
      if (c == '=') {
          eq = true;
          break;
      }
      lvalue += c;
  }

  if (!eq) {
      vector<double> k = {0};
      QVector<double> v_d = QVector<double>::fromStdVector(k);
      QList<double> l_d = QList<double>::fromVector(v_d);
      Manager::instance()->addCalculated(VariableData (QString::fromStdString(lvalue), QString::fromStdString(lvalue), l_d));
      vector<string> str {};
      return {str, {0, lvalue}};
  }
  else {
      string tmp_name = lvalue;
      if (isUnique(QString::fromStdString(lvalue))) {

        s = s.substr(i + 1, s.length() - i - 1);

        i = 0;
        lvalue = "";

        while (s[i] != '\0') {
          // Проверка на число

          if (isdigit(s[i])) {
            int number_of_dots = 0;
            while (isdigit(s[i]) or s[i] == '.') {
              lvalue += s[i];
              if (s[i] == '.') number_of_dots++;
              ++i;
            }
            if (number_of_dots > 1) {
              throw "BAD INPUT";
            }
            output.push_back(lvalue);
            --i;
            lvalue = "";
          }

          // Проверка на переменную или функцию

          else if (isalpha(s[i])) {
            while (isalpha(s[i])) {
              lvalue += s[i];
              ++i;
            }
            int number_of_comma = 0;

            // Если это функция

            if (s[i] == '{') {
              ++i;
              string word_for_func = "";
              while (s[i] == ',' or isdigit(s[i])) {
                int number_of_dots = 0;
                if (s[i] == ',') number_of_comma++;
                if (isdigit(s[i])) {
                  while (isdigit(s[i]) or s[i] == '.') {
                    word_for_func += s[i];
                    if (s[i] == '.') number_of_dots++;
                    ++i;
                  }
                  if (number_of_dots > 1) {
                    cout << "NUMBER OF DOTS > 1";
                    throw "BAD INPUT";
                  }
                  --i;
                  output.push_back(word_for_func);
                  word_for_func = "";
                }

                ++i;
              }
              if (isalpha(s[i])) {
              }

              if (s[i] == '}') {
                output.push_back(lvalue);
                string tmp_word = "{";
                tmp_word += to_string(number_of_comma + 1);
                tmp_word += "}";
                output.push_back(tmp_word);
              }
            }

            // Если это переменная-вектор с диапазоном

            else if (s[i] == '[') {
              if (isdigit(s[i + 1])) {
                ++i;
                string first_num = "";
                string second_num = "";
                while (isdigit(s[i])) {
                  first_num += s[i];
                  ++i;
                }
                --i;
                if (s[i + 1] == ':') {
                  if (isUnique(QString::fromStdString(lvalue))) {
                    i += 2;
                    output.push_back(lvalue);
                    while (isdigit(s[i])) {
                      second_num += s[i];
                      ++i;
                    }
                    string range_ = "[" + first_num + "," + second_num + "]";
                    output.push_back(range_);
                  }
                }
              }

            }

            // Если это переменная-вектор без диапазона

            else {
              if (isUnique(QString::fromStdString(lvalue))) {
                output.push_back(lvalue);
                --i;
              }
            }
            lvalue = "";
          }

          // Проверка на операцию

          else {
            if (s[i] == '(') {
              sym.push_back(s[i]);
              number_of_brackets++;

            } else if (s[i] == ')' and number_of_brackets) {
              string for_sym = "";
              for (int j = sym.size() - 1; j >= 0; --j) {
                if (sym[j] == '(') {
                  remove(sym, j);
                  break;
                } else {
                  for_sym += sym[j];
                  output.push_back(for_sym);
                  for_sym = "";
                  remove(sym, j);
                }
              }

              number_of_brackets--;
            } else {
              if ((symPriority(s[i + 1]) > 0 and symPriority(s[i + 1]) <= 4) or
                  symPriority(s[i - 1]) == 0) {
                throw "BAD INPUT";
              }

              else {
                string for_sym = "";
                for (int j = sym.size() - 1; j >= 0; --j) {
                  if (sym[j] == '(')
                    break;
                  else if (symPriority(s[i]) <= symPriority(sym[j])) {
                    for_sym += sym[j];
                    output.push_back(for_sym);
                    for_sym = "";
                    remove(sym, j);
                  }
                }
                sym.push_back(s[i]);
              }
            }
          }
          if (s[i + 1] == '\0') {
            string for_sym = "";
            for (int j = sym.size() - 1; j >= 0; --j) {
              for_sym += sym[j];
              output.push_back(for_sym);
              for_sym = "";
            }
          }
          ++i;
        }
        if (number_of_brackets == 0) {
          cout << endl;
          return {output, {1, tmp_name}};
        } else {
          cout << "WRONG NUMBER OF BRACKETS";
          throw "BAD INPUT";
        }
    }
    else {
          vector<double> k = {0};
          QVector<double> v_d = QVector<double>::fromStdVector(k);
          QList<double> l_d = QList<double>::fromVector(v_d);
          Manager::instance()->addCalculated(VariableData (QString::fromStdString(tmp_name), QString::fromStdString(lvalue), l_d));
          return {output, {0, tmp_name}};
    }
    }
}
// Функция, проверяющая, диапазон это или нет

pair<int, int> isrange(string s) {
  string first = "";
  string second = "";
  if (s[0] == '[' and s[s.length() - 1] == ']') {
    int i = 1;
    while (s[i] != ',') {
      first += s[i];
      ++i;
    }
    ++i;
    while (s[i] != ']') {
      second += s[i];
      ++i;
    }
    return {stoi(first), stoi(second)};
  }
  return {0, 0};
}

// Функция, проверяющая, количество аргументов функции это или нет

int isArgumentNumber(string s) {
  if (s[0] == '{' and s[s.length() - 1] == '}') {
    string tmp_num = "";
    for (int i = 1; i < s.length() - 1; ++i) tmp_num += s[i];

    return stoi(tmp_num);
  }

  return 0;
}

// Простейшие операции

double add(double a, double b) { return a + b; }

double substract(double a, double b) { return b - a; }

double multiplication(double a, double b) { return a * b; }

double exponentiation(double a, double b) { return pow(a, b); }

double division(double a, double b) { return b / a; }

// Общая функция для простейших операций

vector<double> op_func(vector<double> a, vector<double> b,
                       double (*op)(double, double)) {
  vector<double> tmp;
  if (a.size() == 1) {
    for (auto elem : b) {
      qInfo() << op(elem, b[0]) << endl;
      tmp.push_back(op(elem, a[0]));
    }
  } else if (b.size() == 1) {
    for (auto elem : a) {
      qInfo() << op(elem, b[0]) << endl;
      tmp.push_back(op(elem, b[0]));
    }
  } else if (a.size() > 1 and b.size() > 1 and a.size() == b.size()) {
    for (int i = 0; i < a.size(); ++i) {
      qInfo() << op(a[i], b[i]) << endl;
      tmp.push_back(op(a[i], b[i]));
    }
  } else {
    throw "WRONG SIZE!";
  }
  return tmp;
}

// Тестовая функция для функции вычисления минимального

vector<double> minimality(vector<Variable> elems, int count);

// Проверка корректности диапазона

bool arrangement_check(int first, int second, vector<double> vec) {
  if (first > second)
    return 0;
  else if (first < 0 or second < 0)
    return 0;
  else if (first > vec.size() or second > vec.size())
    return 0;
  return 1;
}

// Функция вычисления строки, полученной из parse()

void calculate(pair<vector<string>, pair<bool, string>> Pair_d) {
  vector<Variable> elements;
  vector<string> vec = Pair_d.first;
  string name = Pair_d.second.second;
  bool is_parsed = Pair_d.second.first;
  if (is_parsed) {
  for (int i = 0; i < vec.size(); ++i) {
    // Если это число

    if (strtod(vec[i].c_str(), NULL)) {
      elements.push_back({vector<double>{strtod(vec[i].c_str(), NULL)}});
    }

    // Если это переменная с диапазоном

    else if (isUnique(QString::fromStdString(vec[i])) and !isArgumentNumber(vec[i + 1]) and
             (isrange(vec[i + 1]).first or isrange(vec[i + 1]).second)) {
      int first = isrange(vec[i + 1]).first;
      int second = isrange(vec[i + 1]).second;
      vector<double> actual_vec = VariableGet(vec[i]).getValue();
      if (arrangement_check(first, second, actual_vec)) {
        vector<double> changed_vec;
        for (int j = first; j <= second; ++j)
          changed_vec.push_back(actual_vec[j]);
        elements.push_back({changed_vec});
      }
    }

    // Если это переменная без диапазона

    else if (isUnique(QString::fromStdString(vec[i])) and !isArgumentNumber(vec[i + 1]) and
             (!isrange(vec[i + 1]).first and !isrange(vec[i + 1]).second)) {
      elements.push_back({VariableGet(vec[i]).getValue()});
    }

    // Если это функция min

    else if (vec[i] == "min" and isArgumentNumber(vec[i + 1])) {
      vector<Variable> tmp_elements = elements;
      int argnum = isArgumentNumber(vec[i + 1]);
      for (int i = 0; i < argnum; ++i) {
        elements.pop_back();
      }
      vector<double> k = minimality(tmp_elements, isArgumentNumber(vec[i + 1]));
      elements.push_back(
          minimality(tmp_elements, isArgumentNumber(vec[i + 1])));

    }

    // Если это простейшие операции

    else if (vec[i] == "+") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, add));
    } else if (vec[i] == "-") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, substract));
    } else if (vec[i] == "*") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, multiplication));
    } else if (vec[i] == "/") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, division));
    } else if (vec[i] == "^") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, exponentiation));
    }
  }

  //QList<double> temp_list = QList<double>::fromVector(QVector<double>::fromStdVector(elements[0].getValue()));
  QList<double> tmp_list;
  for (auto i : elements[0].getValue())
      tmp_list.append(i);
  Manager::instance()->getVariableOrCalculated(QString::fromStdString(name))->measurements = tmp_list;
  }
}

vector<double> minimality(vector<Variable> elems, int count) {
  if (count == 1) {
    // Если аргумент всего один, то мы проверяем его размер
    vector<double> vec = elems.back().getValue();
    if (vec.size() == 1)
      // Если размер вектора равен 1, то возвращаем просто число
      return vec;
    else {
      // Если размер вектора больше 1, то это вектор чисел, находим там
      // минимальное
      double tmp_min = elems.back().getValue()[0];
      for (auto i : vec) {
        tmp_min = min(tmp_min, i);
      }

      vector<double> tmp_min_holder{tmp_min};
      return tmp_min_holder;
    }

  }
  // Если аргументов несколько, то проверяем, все ли аргументы - вектора,
  // состоящие более чем из одного элемента. Возвращаемым значением тогда
  // будет вектор минимальных чисел. В противном случае мы просто вернем одно
  // число
  else {
    bool number_existence = 0;
    vector<Variable> tmp_elems = elems;
    vector<Variable> actual_elems;
    for (int i = 0; i < count; ++i) {
      if (tmp_elems.back().getValue().size() == 1) number_existence = 1;
      actual_elems.push_back(tmp_elems.back());
      tmp_elems.pop_back();
    }

    if (number_existence) {
      double tmp_min = tmp_elems.back().getValue()[0];
      for (auto i : actual_elems) {
        vector<double> tmp_vec = i.getValue();
        for (auto j : tmp_vec) {
          tmp_min = min(tmp_min, j);
        }
      }
      vector<double> tmp_min_holder{tmp_min};
      return tmp_min_holder;
    } else {
      int vec_size = 0;
      vector<double> tmp_min_holder(actual_elems.back().getValue().size());
      while (vec_size < actual_elems.back().getValue().size()) {
        double tmp_min = tmp_elems.back().getValue()[0];
        for (auto i : actual_elems) {
          tmp_min = min(tmp_min, i.getValue()[vec_size]);
        }
        tmp_min_holder.push_back(tmp_min);
        vec_size++;
      }

      return tmp_min_holder;
    }
  }
}
}
