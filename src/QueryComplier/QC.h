#ifndef LEXER
#define LEXER
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<cctype>
#include<numeric>
#include <memory>
#include <gtest/gtest.h>
#include <map>
#include<cwctype>

#include <cstring>


typedef std::pair<int, std::string> token;

const std::map<char, token> other_token = { { '(', { 0, "lquote" } }, { ')', { 1, "rquote" } }, { ';', { 2, "semi" } }, { '=', { 3, "equal" } }, { ',', { 4, "comma" } }, { '\'', { 5, "squote" } }, { '*', { 6, "all" } } };

class lexer{
public:	lexer(){}




		std::vector<token> operator()(const std::string &s);

private:
	token name(int &i);



	std::vector<token> symbol_table;

	std::string input;
	std::string tc;





};
#endif