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
#include"QC.h"
#include <cstring>
//#define PARSERDEBUG


class parser{
public:
	std::vector<token>	symbol_table;





	std::vector<token>::size_type i = 0;
	parser(const std::vector<token>&  st) :symbol_table(st){}
	void lanch(){
		try{
			command();
		}
		catch (std::invalid_argument err){
			std::cout << err.what() << std::endl;
		};
#ifdef PARSERDEBUG


#endif



	}




	inline	void match(int s){
		std::cout << s;

		if (i < symbol_table.size() && s == symbol_table[i].first)
		{
			i++;
#ifdef PARSERDEBUG
			std::cout << "匹配" + symbol_table[i].second<<std::endl;

#endif

		}
		else throw std::invalid_argument("非法记号！" + symbol_table[i].second);



	}

	void match(const std::string &s){

		if (i < symbol_table.size() && s == symbol_table[i].second)
			i++;
		else throw std::invalid_argument("非法记号！" + symbol_table[i].second);


	}
	//lanch() 未修正
	void command(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		if (symbol_table[i].first == 32 || symbol_table[i].first == 33)
			ddl();
		else 	if (symbol_table[i].first == 21 || symbol_table[i].first == 25 || symbol_table[i].first == 24 || symbol_table[i].first == 26)
			dml();
		else 	if (symbol_table[i].first >= 34 && symbol_table[i].first <= 39)
			util();
		else nothing();




	}
	void ddl(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		if (i + 1 < symbol_table.size() && symbol_table[i].first == 33 && symbol_table[i + 1].first == 40)
		{
			createtable();

		}
		else if (i + 1 < symbol_table.size() && symbol_table[i].first == 33 && symbol_table[i + 1].first == 41)
		{
			createindex();

		}
		else if (i + 1 < symbol_table.size() && symbol_table[i].first == 32 && symbol_table[i + 1].first == 40)
		{

			droptable();

		}

		else if (i + 1 < symbol_table.size() && symbol_table[i].first == 32 && symbol_table[i + 1].first == 41)
		{

			dropindex();

		}
		else 			throw std::invalid_argument("非法记号！" + symbol_table[i].second);





	}
	void dml(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		switch (symbol_table[i].first){
		case 21:
			query();
			break;
		case 24:
			insert();
			break;
		case 25:
			delete_sql();
			break;
		case 26:
			update();
			break;
		default:
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		}
	}
	void util(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		switch (symbol_table[i].first){
		case 34:
			load();
			break;
		case 36:
			exit();
			break;
		case 37:
			set();
			break;
		case 38:
			help();
			break;
		case 39:
			print();
			break;
		case 40:
			buffer();
			break;


		default:
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		}
	}
	void nothing(){}
	void createtable(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);


		match(33);
		match(40);
		match(NAMEORDER);
		match(0);
		non_mt_attrtype_list();
		match(1);






	}
	void createindex(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		match(33);
		match(41);
		match(NAMEORDER);
		match(0);
		match(NAMEORDER);
		match(1);




	}
	void droptable(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);


		match(32);
		match(40);
		match(NAMEORDER);

	}



	void dropindex(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		match("drop");
		match("index");
		match(NAMEORDER);
		match(0);
		match(NAMEORDER);
		match(1);




	}
	void query(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		match(21);
		non_mt_select_clause();
		match(22);
		non_mt_relation_list();
		opt_where_clause();
		if (symbol_table[i].first == 44)
		{
			opt_order_by_clause();
			if (symbol_table[i].first == 45)

				opt_group_by_clause();
		}
		if (symbol_table[i].first == 45)
		{
			opt_group_by_clause();

			if (symbol_table[i].first == 44)
				opt_order_by_clause();

		}

	}
	void insert(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		match(24);
		match(30);
		match(NAMEORDER);
		match("values");
		match(0);
		non_mt_value_list();
		match(1);








	}
	void delete_sql(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		match(25);
		match(22);
		match(NAMEORDER);

		opt_where_clause();








	}
	void update(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		match(26);
		match(NAMEORDER);
		match(36);

		relattr();
		match("eq");
		relattr_or_value();
		opt_where_clause();






	}
	void load(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		match(34);
		match(NAMEORDER);
		match(0);
		match("qstring");
		match(1);





	}
	void exit(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		match(35);







	}
	void set(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		match(36);
		match(NAMEORDER);
		match("eq");
		match("qstring");






	}
	void help(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);


		match(37);
		opt_relname();






	}
	void print(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		match(38);
		match(NAMEORDER);







	}
	//与sfu定义文件不同，这里为方便ll1解析，buffer下从句调换顺序
	void buffer(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		if (i + 1 < symbol_table.size() && symbol_table[i + 1].first == 43)
		{
			//reset action

		}
		else if (i + 1 < symbol_table.size() && symbol_table[i + 1].first == 42)
		{
			//resize action

		}
		else		 throw std::invalid_argument("非法记号！" + symbol_table[i].second);


	}
	void non_mt_attrtype_list(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		attrtype();

		if (i < symbol_table.size() && symbol_table[i].first == 4){
			match(4);
			non_mt_attrtype_list();
		}




	}
	void opt_relname(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		if (symbol_table[i].first == NAMEORDER)
			match(NAMEORDER);


	}
	void non_mt_select_clause(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);


		if (symbol_table[i].first == 6)
			match(6);
		else if (symbol_table[i].first == NAMEORDER || (symbol_table[i].first >= 47 && symbol_table[i].first <= 51))
			non_mt_aggrelattr_list();
		else	throw std::invalid_argument("非法记号！" + symbol_table[i].second);




	}
	void non_mt_aggrelattr_list(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		aggrelattr();
		if (symbol_table[i].first == 4)
		{

			match(4);
			non_mt_aggrelattr_list();
		}




	}
	

	void opt_order_by_clause(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);


		if (44 == symbol_table[i].first){

			match(44);
			match(46);
			ordering_spec();
		}
		else nothing();

	}
	
	void opt_group_by_clause(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);


		if (45 == symbol_table[i].first){

			match(45);
			match(46);
			relattr();
		}
		else nothing();

	}
	void relattr(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		match(NAMEORDER);
		if (symbol_table[i].first == 10)
		{

			match(10);
			match(NAMEORDER);
		}





	}
	void opt_where_clause(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);


		if (23 == symbol_table[i].first){

			match(23);
			non_mt_cond_list();
		}
		else nothing();

	}
	void attrtype(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		match(NAMEORDER);
		match(NAMEORDER);
	}
	


	void aggrelattr(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		//开头时ammsc的情况
		if (symbol_table[i].first <= 51 && symbol_table[i].first >= 47)
		{
			ammsc();
			match(0);
			//ammsc '(' T_STRING 开头
			if (symbol_table[i].first == NAMEORDER)
			{
				match(NAMEORDER);
				if (symbol_table[i].first == 10)
				{
					match(10);
					match(NAMEORDER);
				}

			}
			else	if (symbol_table[i].first == 6)
				match(6);
			else 	throw std::invalid_argument("非法记号！" + symbol_table[i].second);

			match(1);
		}
		else if (symbol_table[i].first == NAMEORDER)
		{
			match(NAMEORDER);
			if (symbol_table[i].first == 10)
			{
				match(10);
				match(NAMEORDER);
			}
		}
		else 		throw std::invalid_argument("非法记号！" + symbol_table[i].second);

	}	


	void ammsc(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		switch (symbol_table[i].first){
		case 47:
			match(47);
			break;
		case 48:
			match(48);
			break;
		case 49:
			match(49);
			break;
		case 50:
			match(50);
			break;
		case 51:
			match(51);
			break;

		default:
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		}
	}

	void non_mt_relattr_list(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		relattr();

		if (4 == symbol_table[i].first){

			match(",");
			non_mt_relattr_list();
		}








	}
	void non_mt_relation_list(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		relation();
		if (symbol_table[i].first == 4)
		{

			match(4);
			non_mt_relation_list();
		}







	}
	
	void ordering_spec(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		relattr();
		opt_asc_desc();




	}
	void opt_asc_desc(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		switch (symbol_table[i].first){
		case 52:
			match(52);
			break;
		case 53:
			match(53);
			break;


		default:
			break;
		}
	}


	void non_mt_cond_list(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		condition();
		if (27 == symbol_table[i].first){

			match(27);
			non_mt_cond_list();
		}


	}
	void condition(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		relattr();
		op();
		relattr_or_value();

	}
	//关系运算符。暂时仅实现= > <，不等于不大于不小于未实现
	void op(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		switch (symbol_table[i].first){
		case 3:
			match(3);
			break;
		case 11:
			match(11);
			break;
		case 12:
			match(12);
			break;

		default:
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		}

	}
	void relattr_or_value(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		switch (symbol_table[i].first){
		case NAMEORDER:
			relattr();
			break;
			//应为“value”对应值
		case 2:
			value();
			break;


		default:
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);

		}
	}
	void value(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		switch (symbol_table[i].first){
		case 1:
			match("qstring");
			break;
		case 2:
			match("int");
			break;
		case 3:
			match("real");
			break;
		default:
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		}
	}
	void non_mt_value_list(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		value();
		if (4 == symbol_table[i].first){

			match(4);
			non_mt_value_list();
		}

	}


		void relation(){
			if (i >= symbol_table.size())
				throw std::invalid_argument("非法记号！" + symbol_table[i].second);
			match(NAMEORDER);

		}

















	

};























	int main()
	{



		lexer l;

		std::vector<token>	symbol_table;

		symbol_table = l("INSERT INTO SPJ( SNO, JNO, PNO, QTY) VALUES(北京, J6, P4); ");
		for (auto a : symbol_table)
		{
			std::cout << a.first << ":" << a.second << std::endl;
		}
		decltype(symbol_table.size()) n = 0;
		std::cout << "DECLTYPEtest  " << n << std::endl;
		symbol_table = l("select t from 产品 where 单价=6000 and 产品名称 in (select * from it )");
		std::cout << symbol_table.size() << std::endl;

		//若输入非法，Lexer抛出异常，symbol_table清空
		if (symbol_table.size() > 0)
		{
			for (auto a : symbol_table)
			{
				std::cout << a.first << ":" << a.second << std::endl;
			}
			std::cout << std::endl;

			//parser ps(symbol_table);
			//ps.lanch();
		}
		return 0;
}