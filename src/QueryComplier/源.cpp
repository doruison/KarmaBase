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



class parser{
public:

inline	void match(const int s){
		try{
			if (s == symbol_table[i + 1].first)
				i++;
			else throw std::invalid_argument("非法记号！");
		}
		catch (std::invalid_argument err){
			std::cout << err.what << std::endl;
		};

	}

	void match(const std::string &s){
		try{
			if (s == symbol_table[i + 1].second)
				i++;
			else throw std::invalid_argument("非法记号！");
		}
		catch (std::invalid_argument err){
			std::cout << err.what << std::endl;
		};

	}

	void Query(){
		match(21);
		sellist();
		match(22);
			from();
			conditions();

	}

	void sellist(){
		attribute();
		while (symbol_table[i + 1].first == 4)
		{
			i++;
			attribute();

		}
	}
	void from(){
		relation();
		while (symbol_table[i + 1].first == 4)
		{
			i++;
			relation();

		}
	}
	void conditions(){
		condition();
		while (symbol_table[i + 1].first == 27)
		{
			i++;
			condition();
		}
	}

	void condition(){
		attribute();
		if (symbol_table[i + 1].first == 3)
		{
			//match(3);
			i++;
			attribute();
		}
		else if (symbol_table[i + 1].first == 28)
		{
		
			//match(28);
			i++;

			//此处可能造成无穷递归
			Query();
		
		}
		else {
			match(29);
			pattern();
		
		
		}



	}

	void attribute(){
		//匹配当前数据库的任意属性
		//尚未实现
		i++;


	}
	void relation(){
		//必须是表名
		//尚未实现
		i++;

	}
	void pattern(){
		//必须是单引号括起来的SQL字符串
		//尚未实现
		i++;

	}
















private:
	lexer l;
	std::vector<token> && symbol_table = std::move(l("!#$&*( ^^%INSERT INTO SPJ( SNO, JNO, PNO, QTY) VALUES(北京, J6, P4); "));
	//(decltype (std::vector<token>.size())) i = 0;
	decltype (symbol_table.size()) i = 0;


};












int main()
{



	lexer l;
	//右值引用：测试
	std::vector<token> && symbol_table = move(l("!#$&*( ^^%INSERT INTO SPJ( SNO, JNO, PNO, QTY) VALUES(北京, J6, P4); "));
	for (auto a : symbol_table)
	{
		std::cout << a.first << ":" << a.second << std::endl;
	}


	//右值引用：测试
	symbol_table = move(l("INSERT INTO SPJ( SNO, JNO, PNO, QTY) VALUES(北京, J6, P4); "));
	for (auto a : symbol_table)
	{
		std::cout << a.first << ":" << a.second << std::endl;
	}


	return 0;
}