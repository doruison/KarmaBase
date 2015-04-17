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

const std::unordered_map<char, token> other_token = { { '(', { 0, "lquote" } }, { ')', { 1, "rquote" } }, { ';', { 2, "semi" } }, { '=', { 3, "equal" } }, { ',', { 4, "comma" } }, { '*', { 6, "all" } }, { '+', { 7, "plus" } }, { '-', { 8, "minus" } }, { '/', { 9, "div" } }, { '.', { 10, "point" } }, { '>', { 11, "greater" } }, { '<', { 12, "lesser" } }, { '!', { 13, "non" } } };

const std::unordered_map< std::string, int>  keyword = { { "select", 21 }, { "from", 22 }, { "where", 23 }, { "insert", 24 }, { "delete", 25 }, { "update", 26 }, { "and", 27 }, { "in", 28 }, { "like", 29 }, { "SELECT", 21 }, { "FROM", 22 }, { "WHERE", 23 }, { "INSERT", 24 }, { "DELETE", 25 }, { "UPDATE", 26 }, { "AND", 27 }, { "IN", 28 }, { "LIKE", 29 }, { "into", 30 }, { "INTO", 30 }, { "values", 31 }, { "VALUES", 31 }, { "drop", 32 }, { "DROP", 32 }, { "CREATE", 33 }, { "create", 33 }, { "load", 34 }, { "LOAD", 34 }, { "exit", 35 }, { "EXIT", 35 }, { "set", 36 }, { "SET", 36 }, { "help", 37 }, { "HELP", 37 }, { "print", 38 }, { "PRINT", 38 }, { "buffer", 39 }, { "BUFFER", 39 }, { "table", 40 }, { "TABLE", 40 }, { "index", 41 }, { "INDEX", 41 }, { "resize", 42 }, { "RESIZE", 42 }, { "reset", 43 }, { "RESET", 43 }, { "order", 44 }, { "ORDER", 44 }, { "group", 45 }, { "GROUP", 45 }, { "by", 46 }, { "BY", 46 }, { "avg", 47 }, { "AVG", 47 }, { "max", 48 }, { "MAX", 48 }, { "min", 49 }, { "MIN", 49 }, { "count", 50 }, { "COUNT", 50 }, { "sum", 51 }, { "SUM", 51 }, { "desc", 52 }, { "DESC", 52 }, { "asc", 53 }, { "ASC", 53 } };

class lexer{
public:	lexer(){}




		std::vector<token> operator()(const std::string &s);

private:
	token name(unsigned int &i);
	token digit(unsigned int &i);

	token sqlstring(unsigned int &i);

	std::vector<token> symbol_table;

	std::string input;
	std::string tc;





};



class parser{
public:
	parser(const std::vector<token>&  st) :symbol_table(st){}
	void lanch();





private:
	std::vector<token>	symbol_table;

	std::vector<token>::size_type i = 0;

	inline	void match(int s);
		


	void command();
	void ddl();
	void dml();
	void util();
	void nothing();
	void createtable();
	void createindex();
	void droptable();


	void dropindex();
	void query();
	void insert();
	void delete_sql();
	void update();

	void load();
	void exit();
	void set();
	void help();
	void print();
	//与sfu定义文件不同，这里为方便ll1解析，buffer下从句调换顺序
	void buffer();
	void non_mt_attrtype_list();
	void opt_relname();
	void non_mt_select_clause();
	void non_mt_aggrelattr_list();
	void opt_order_by_clause();

	void opt_group_by_clause();
	void relattr();
	void opt_where_clause();
	void attrtype();

	void aggrelattr();

	void ammsc();
	void non_mt_relattr_list();
	void non_mt_relation_list();
	void ordering_spec();

	void non_mt_cond_list();
	void condition();

	void op();
	void relattr_or_value();

	void values();
	void non_mt_value_list();
	void relation();
	void opt_asc_desc();
};
#endif