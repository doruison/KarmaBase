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


void parser::lanch(){
		try{
			command();
		}
		catch (std::invalid_argument err){
			std::cout << err.what() << std::endl;
		};
#ifdef PARSERDEBUG


#endif



	}




	inline	void parser::match(int s){
		std::cout << s;
		if (i < symbol_table.size())
			std::cout << symbol_table[i].second << " |";
		else std::cout << "outrange" << std::endl;
		if (i < symbol_table.size() && s == symbol_table[i].first)
		{
			i++;
#ifdef PARSERDEBUG
			std::cout << "匹配" + symbol_table[i].second << std::endl;

#endif

		}
		else throw std::invalid_argument("  非法记号！" + symbol_table[i].second);



	}


	//lanch() 未修正
	void parser::command(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号2！" + symbol_table[i].second);
		if (symbol_table[i].first == 32 || symbol_table[i].first == 33)
			ddl();
		else 	if (symbol_table[i].first == 21 || symbol_table[i].first == 25 || symbol_table[i].first == 24 || symbol_table[i].first == 26)
			dml();
		else 	if (symbol_table[i].first >= 34 && symbol_table[i].first <= 39)
			util();
		else nothing();




	}
	void parser::ddl(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号3！" + symbol_table[i].second);
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
		else 			throw std::invalid_argument("非法记号4！" + symbol_table[i].second);





	}
	void parser::dml(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号5！" + symbol_table[i].second);
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
			throw std::invalid_argument("非法记号6！" + symbol_table[i].second);

		}
	}
	void parser::util(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号7！" + symbol_table[i].second);
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
			throw std::invalid_argument("非法记号8！" + symbol_table[i].second);

		}
	}
	void parser::nothing(){}
	void parser::createtable(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号9！" + symbol_table[i].second);


		match(33);
		match(40);
		match(NAMEORDER);
		match(0);
		non_mt_attrtype_list();
		match(1);






	}
	void parser::createindex(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号10！" + symbol_table[i].second);
		match(33);
		match(41);
		match(NAMEORDER);
		match(0);
		match(NAMEORDER);
		match(1);




	}
	void parser::droptable(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号11！" + symbol_table[i].second);


		match(32);
		match(40);
		match(NAMEORDER);

	}



	void parser::dropindex(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号12！" + symbol_table[i].second);

		match(32);
		match(41);
		match(NAMEORDER);
		match(0);
		match(NAMEORDER);
		match(1);




	}
	void parser::query(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号13！" + symbol_table[i].second);
		match(21);
		non_mt_select_clause();
		match(22);
		non_mt_relation_list();
		opt_where_clause();
		if (i< symbol_table.size() && symbol_table[i].first == 44)
		{
			opt_order_by_clause();
			if (i< symbol_table.size() && symbol_table[i].first == 45)

				opt_group_by_clause();
		}
		else if (i< symbol_table.size() && symbol_table[i].first == 45)
		{
			opt_group_by_clause();

			if (i< symbol_table.size() && symbol_table[i].first == 44)
				opt_order_by_clause();

		}

	}
	void parser::insert(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号14！" + symbol_table[i].second);

		match(24);
		match(30);
		match(NAMEORDER);
		//insert into单独指定属性的情形。nameorder应判断属性。暂未实现。
		if (i< symbol_table.size() && symbol_table[i].first == 0)
		{
			match(0);
			match(NAMEORDER);
			while (symbol_table[i].first == 4)
			{
				match(4);
				match(NAMEORDER);
			}
			match(1);

		}
		match(31);

		match(0);
		non_mt_value_list();
		match(1);








	}
	void parser::delete_sql(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号15！" + symbol_table[i].second);

		match(25);
		match(22);
		match(NAMEORDER);

		opt_where_clause();








	}
	void parser::update(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号16！" + symbol_table[i].second);

		match(26);
		match(NAMEORDER);
		match(36);

		relattr();
		match(3);
		relattr_or_value();
		while (i < symbol_table.size() && symbol_table[i].first == 4)
		{
			match(4);
			relattr();
			match(3);
			relattr_or_value();

		}
		opt_where_clause();






	}

	void parser::load(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号19！" + symbol_table[i].second);

		match(34);
		match(NAMEORDER);
		match(0);
		match(NAMEORDER + 2);
		match(1);





	}
	void parser::exit(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号20！" + symbol_table[i].second);

		match(35);







	}
	void parser::set(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号21！" + symbol_table[i].second);

		match(36);
		match(NAMEORDER);
		match(3);
		match(NAMEORDER + 2);






	}
	void parser::help(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号22！" + symbol_table[i].second);


		match(37);
		opt_relname();






	}
	void parser::print(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号23！" + symbol_table[i].second);

		match(38);
		match(NAMEORDER);







	}
	//与sfu定义文件不同，这里为方便ll1解析，buffer下从句调换顺序
	void parser::buffer(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号24！" + symbol_table[i].second);

		if (i + 1 < symbol_table.size() && symbol_table[i + 1].first == 43)
		{
			//reset action

		}
		else if (i + 1 < symbol_table.size() && symbol_table[i + 1].first == 42)
		{
			//resize action

		}
		else		 throw std::invalid_argument("非法记号25！" + symbol_table[i].second);


	}
	void parser::non_mt_attrtype_list(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号26！" + symbol_table[i].second);
		attrtype();

		if (i < symbol_table.size() && symbol_table[i].first == 4){
			match(4);
			non_mt_attrtype_list();
		}




	}
	void parser::opt_relname(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号27！" + symbol_table[i].second);
		if (symbol_table[i].first == NAMEORDER)
			match(NAMEORDER);


	}
	void parser::non_mt_select_clause(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号28！" + symbol_table[i].second);


		if (symbol_table[i].first == 6)
			match(6);
		else if (symbol_table[i].first == NAMEORDER || (symbol_table[i].first >= 47 && symbol_table[i].first <= 51))
			non_mt_aggrelattr_list();
		else	throw std::invalid_argument("非法记号29！" + symbol_table[i].second);




	}
	void parser::non_mt_aggrelattr_list(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号30！" + symbol_table[i].second);
		aggrelattr();
		if (i< symbol_table.size() && symbol_table[i].first == 4)
		{

			match(4);
			non_mt_aggrelattr_list();
		}




	}


	void parser::opt_order_by_clause(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号31！" + symbol_table[i].second);


		if (44 == symbol_table[i].first){

			match(44);
			match(46);
			ordering_spec();
		}
		else nothing();

	}

	void parser::opt_group_by_clause(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号32！" + symbol_table[i].second);


		if (45 == symbol_table[i].first){

			match(45);
			match(46);
			relattr();
		}
		else nothing();

	}
	void parser::relattr(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号33！" + symbol_table[i].second);
		match(NAMEORDER);
		if (i< symbol_table.size() && symbol_table[i].first == 10)
		{

			match(10);
			match(NAMEORDER);
		}





	}
	void parser::opt_where_clause(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号34！" + symbol_table[i].second);


		if (23 == symbol_table[i].first){

			match(23);
			non_mt_cond_list();
		}
		else nothing();

	}
	void parser::attrtype(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号35！" + symbol_table[i].second);
		match(NAMEORDER);
		match(NAMEORDER);
	}



	void parser::aggrelattr(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号36！" + symbol_table[i].second);
		//开头时ammsc的情况
		if (symbol_table[i].first <= 51 && symbol_table[i].first >= 47)
		{
			ammsc();
			match(0);
			//ammsc '(' T_STRING 开头
			if (i< symbol_table.size() && symbol_table[i].first == NAMEORDER)
			{
				match(NAMEORDER);
				if (i< symbol_table.size() && symbol_table[i].first == 10)
				{
					match(10);
					match(NAMEORDER);
				}

			}
			else	if (i< symbol_table.size() && symbol_table[i].first == 6)
				match(6);
			else 	throw std::invalid_argument("非法记号37！" + symbol_table[i].second);

			match(1);
		}
		else if (i< symbol_table.size() && symbol_table[i].first == NAMEORDER)
		{
			match(NAMEORDER);
			if (i< symbol_table.size() && symbol_table[i].first == 10)
			{
				match(10);
				match(NAMEORDER);
			}
		}
		else 		throw std::invalid_argument("非法记号38！" + symbol_table[i].second);

	}


	void parser::ammsc(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号39！" + symbol_table[i].second);
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
			throw std::invalid_argument("非法记号40！" + symbol_table[i].second);

		}
	}

	void parser::non_mt_relattr_list(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号41！" + symbol_table[i].second);
		relattr();

		if (4 == symbol_table[i].first){

			match(4);
			non_mt_relattr_list();
		}








	}
	void parser::non_mt_relation_list(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号42！" + symbol_table[i].second);
		relation();
		if (i< symbol_table.size() && symbol_table[i].first == 4)
		{

			match(4);
			non_mt_relation_list();
		}







	}

	void parser::ordering_spec(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号43！" + symbol_table[i].second);
		relattr();
		opt_asc_desc();




	}
	void parser::opt_asc_desc(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号44！" + symbol_table[i].second);
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


	void parser::non_mt_cond_list(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号45！" + symbol_table[i].second);
		condition();
		if (i<symbol_table.size() && 27 == symbol_table[i].first){

			match(27);
			non_mt_cond_list();
		}


	}
	void parser::condition(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号46！" + symbol_table[i].second);
		relattr();
		if (i < symbol_table.size() && symbol_table[i].first == 28)
		{
			match(28);
			match(0);
			query();
			match(1);

		}
		else if (i < symbol_table.size() && (symbol_table[i].first == 3 || (symbol_table[i].first >= 11 && symbol_table[i].first <= 13)))
		{
			op();
			relattr_or_value();
		}
		else throw std::invalid_argument("非法记号46！" + symbol_table[i].second);

	}

	void parser::op(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号17！" + symbol_table[i].second);
		if (symbol_table[i].first == 11 || symbol_table[i].first == 12)
		{
			match(symbol_table[i].first);
			if (i< symbol_table.size() && symbol_table[i].first == 3)
				match(3);


		}
		else if (symbol_table[i].first == 13)
		{
			match(13);
			match(3);


		}
		else if (symbol_table[i].first == 3)
			match(3);
		else	throw std::invalid_argument("非法记号18！" + symbol_table[i].second);
	}
	void parser::relattr_or_value(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号49！" + symbol_table[i].second);
		switch (symbol_table[i].first){
		case NAMEORDER:
			relattr();
			break;
		case NAMEORDER + 2:
			values();
			break;

		case NAMEORDER + 3:
			values();
			break;
		case NAMEORDER + 4:
			values();
			break;

		default:
			throw std::invalid_argument("非法记号50！" + symbol_table[i].second);

		}
	}


	void parser::values(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号49！" + symbol_table[i].second);
		switch (symbol_table[i].first){
		case NAMEORDER + 2:
			match(NAMEORDER + 2);
			break;
		case NAMEORDER + 3:
			match(NAMEORDER + 3);
			break;
		case NAMEORDER + 4:
			match(NAMEORDER + 4);
			break;


		default:
			throw std::invalid_argument("非法记号50！" + symbol_table[i].second);

		}
	}
	void parser::non_mt_value_list(){

		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号53！" + symbol_table[i].second);
		values();
		if (4 == symbol_table[i].first){

			match(4);
			non_mt_value_list();
		}

	}


	void parser::relation(){
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号54！" + symbol_table[i].second);
		match(NAMEORDER);

	}


















