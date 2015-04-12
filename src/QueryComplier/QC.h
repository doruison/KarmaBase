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
#include <unordered_map>
#include<cwctype>
#include <map>
#include <cstring>

#define  NAMEORDER 64
typedef std::pair<int, std::string> token;

const std::unordered_map<char, token> other_token = { { '(', { 0, "lquote" } }, { ')', { 1, "rquote" } }, { ';', { 2, "semi" } }, { '=', { 3, "equal" } }, { ',', { 4, "comma" } }, { '\'', { 5, "squote" } }, { '*', { 6, "all" } }, { '+', { 7, "plus" } }, { '-', { 8, "minus" } }, { '/', { 9, "div" } }, { '.', { 10, "point" } }, { '>', { 11, "greater" } }, { '<', { 12, "lesser" } } };

const std::unordered_map< std::string, int>  keyword = { { "select", 21 }, { "from", 22 }, { "where", 23 }, { "insert", 24 }, { "delete", 25 }, { "update", 26 }, { "and", 27 }, { "in", 28 }, { "like", 29 }, { "SELECT", 21 }, { "FORM", 22 }, { "WHERE", 23 }, { "INSERT", 24 }, { "DELETE", 25 }, { "UPDATE", 26 }, { "AND", 27 }, { "IN", 28 }, { "LIKE", 29 }, { "into", 30 }, { "INTO", 30 }, { "values", 31 }, {"VALUES",31} };

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