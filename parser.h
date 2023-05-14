#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <utility>
#include <vector>

namespace parser {

std::pair<std::vector<std::string>, std::pair<bool, std::string>> parse(std::string s);
void calculate(std::pair<std::vector<std::string>, std::pair<bool, std::string>> Pair_d);

}

#endif // PARSER_H
