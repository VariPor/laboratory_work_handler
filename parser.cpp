#include <ctype.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class Variable {
 public:
  Variable(string n, vector<double> v) {
    name = n;
    value = v;
    err = 0;
  }
  Variable(vector<double> v) {
    name = "MyVector";
    value = v;
    err = 0;
  }
  string getName() { return name; }
  vector<double>& getValue() { return value; }
  void setName(string s) { name = s; }
  void setValue(vector<double> n) { value = n; }

 private:
  string name;
  vector<double> value;
  double err;
};

vector<Variable> Variable_Data = {};

bool isUnique(vector<Variable> Variable_Data, string n) {
  for (int i = 0; i < Variable_Data.size(); ++i) {
    if (Variable_Data[i].getName() == n) return false;
  }
  return true;
}

template <typename T>
void remove(std::vector<T>& v, size_t index) {
  v.erase(v.begin() + index);
}

bool VariableCheck(string s) {
  for (auto i : Variable_Data) {
    if (s == i.getName()) return true;
  }
  return false;
}

Variable VariableGet(string s) {
  for (auto i : Variable_Data) {
    if (s == i.getName()) {
      return i;
    }
  }
  Variable k = {"", vector<double>{}};
  return k;
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

vector<string> parse(string s) {
  vector<string> output;
  vector<char> sym;
  int i = 0;
  int number_of_brackets = 0;
  string lvalue = "";

  while (s[i] != '=') {
    lvalue += s[i];
    ++i;
  }

  if (isUnique(Variable_Data, lvalue)) {
    vector<double> k = {0};
    Variable_Data.push_back(Variable{lvalue, k});
  }

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
        cout << "NUMBER OF DOTS > 1";
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
            if (VariableCheck(lvalue)) {
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
        if (VariableCheck(lvalue)) {
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
      for (auto i : output)
          cout << i << " ";
      cout << endl;
    return output;
  } else {
    cout << "WRONG NUMBER OF BRACKETS";
    throw "BAD INPUT";
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

double add(double a, double b) { return a + b; }

double substract(double a, double b) { return b - a; }

double multiplication(double a, double b) { return a * b; }

double exponentiation(double a, double b) { return pow(b, a); }

double division(double a, double b) { return b / a; }

// Общая функция для простейших операций

vector<double> op_func(vector<double> a, vector<double> b,
                       double (*op)(double, double)) {
    cout << endl << a.size() << " " << b.size() << endl;
  vector<double> tmp;
  if (a.size() == 1) {
    for (auto elem : b) {
      tmp.push_back(op(elem, a[0]));
    }
  } else if (b.size() == 1) {
    for (auto elem : a) {
      tmp.push_back(op(elem, b[0]));
    }
  } else if (a.size() > 1 and b.size() > 1 and a.size() == b.size()) {
    for (int i = 0; i < a.size(); ++i) {
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

vector<double> calculate(vector<string> vec) {
  vector<Variable> elements;
  double tmp_num = 0;

  for (int i = 0; i < vec.size(); ++i) {
      
    // Если это число
      
    if (strtod(vec[i].c_str(), NULL)) {
      elements.push_back({vector<double>{strtod(vec[i].c_str(), NULL)}});
    }
      
    // Если это переменная с диапазоном
      
    else if (VariableCheck(vec[i]) and !isArgumentNumber(vec[i + 1]) and
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
      
    else if (VariableCheck(vec[i]) and !isArgumentNumber(vec[i + 1]) and
               (!isrange(vec[i + 1]).first and !isrange(vec[i + 1]).second)) {
      elements.push_back({VariableGet(vec[i]).getValue()});
    }
    
    // Если это функция min
      
    else if (vec[i] == "min" and isArgumentNumber(vec[i + 1])) {
        vector<Variable> tmp_elements = elements;
        cout << elements.size() << endl;
        for (auto i : elements) {
            cout << i.getValue()[0] << ". ";
        }
        cout << "WORKS";
        cout << endl;
        int argnum = isArgumentNumber(vec[i + 1]);
        for (int i = 0; i < argnum; ++i) {
            elements.pop_back();
        }
        vector<double> k = minimality(tmp_elements, isArgumentNumber(vec[i + 1]));
        for (auto i : k)
            cout << i << " ";
        cout << endl;
      elements.push_back(minimality(tmp_elements, isArgumentNumber(vec[i + 1])));
        
    }
    
    // Если это простейшие операции
      
    else if (vec[i] == "+") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, add));
    }
    else if (vec[i] == "-") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, substract));
    }
    else if (vec[i] == "*") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, multiplication));
    }
    else if (vec[i] == "/") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, division));
    }
    else if (vec[i] == "^") {
      vector<double> a = elements.back().getValue();
      elements.pop_back();
      vector<double> b = elements.back().getValue();
      elements.pop_back();
      elements.push_back(op_func(a, b, exponentiation));
    }
  }

  return elements[0].getValue();
}

int main() {
  string s;
  Variable_Data.push_back(Variable("a", {1, 2, 3, 4}));
  Variable_Data.push_back(Variable("b", {2, 2, 2, 2}));
  Variable_Data.push_back(Variable("c", {-2, -3, -4, -4}));
  Variable_Data.push_back(Variable("z", {0, 0, 0, 0}));
  s = "k=a*0";
  vector<double> ans = calculate(parse(s));
  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i] << " ";
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
        cout << tmp_min << "THATS RESULT" << endl;
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
