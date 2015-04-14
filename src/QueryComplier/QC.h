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

#define  NAMEORDER 128
typedef std::pair<int, std::string> token;

const std::unordered_map<char, token> other_token = { { '(', { 0, "lquote" } }, { ')', { 1, "rquote" } }, { ';', { 2, "semi" } }, { '=', { 3, "equal" } }, { ',', { 4, "comma" } }, { '\'', { 5, "squote" } }, { '*', { 6, "all" } }, { '+', { 7, "plus" } }, { '-', { 8, "minus" } }, { '/', { 9, "div" } }, { '.', { 10, "point" } }, { '>', { 11, "greater" } }, { '<', { 12, "lesser" } } };

const std::unordered_map< std::string, int>  keyword = { { "select", 21 }, { "from", 22 }, { "where", 23 }, { "insert", 24 }, { "delete", 25 }, { "update", 26 }, { "and", 27 }, { "in", 28 }, { "like", 29 }, { "SELECT", 21 }, { "FORM", 22 }, { "WHERE", 23 }, { "INSERT", 24 }, { "DELETE", 25 }, { "UPDATE", 26 }, { "AND", 27 }, { "IN", 28 }, { "LIKE", 29 }, { "into", 30 }, { "INTO", 30 }, { "values", 31 }, { "VALUES", 31 }, { "drop", 32 }, { "DROP", 32 }, { "CREATE", 33 }, { "create", 33 }, { "load", 34 }, { "LOAD", 34 }, { "exit", 35 }, { "EXIT", 35 }, { "set", 36 }, { "SET", 36 }, { "help", 37 }, { "HELP", 37 }, { "print", 38 }, { "PRINT", 38 }, { "buffer", 39 }, { "BUFFER", 39 }, { "table", 40 }, { "TABLE", 40 }, { "index", 41 }, { "INDEX", 41 }, { "resize", 42 }, { "RESIZE", 42 }, { "reset", 43 }, { "RESET", 43 }, { "order", 44 }, { "ORDER", 44 }, { "group", 45 }, { "GROUP", 45 }, { "by", 46 }, { "BY", 46 }, { "avg", 47 }, { "AVG", 47 }, { "max", 48 }, { "MAX", 48 }, { "min", 49 }, { "MIN", 49 }, { "count", 50 }, { "COUNT", 50 }, { "sum", 51 }, { "SUM", 51 }, { "desc", 52 }, { "DESC", 52 }, { "asc", 53 }, {"ASC",53} };

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