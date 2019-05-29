#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>

std::pair<std::string, std::string> getFields(std::string s);
std::pair<std::string, std::string> searchRotor(int rotor_index);

#endif