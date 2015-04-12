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
	parser(const std::vector<token>&  st):symbol_table(st){}
	void lanch(){
		try{
			Query();
		}
		catch (std::invalid_argument err){
			std::cout << err.what() << std::endl;
		};
#ifdef PARSERDEBUG

		
#endif
	
	
	
	}




private:
inline	void match( int s){
	std::cout << s;
			if (i<symbol_table.size()&&s == symbol_table[i].first)
			{
				i++;
#ifdef PARSERDEBUG
				std::cout << "匹配" + symbol_table[i].second<<std::endl;

#endif
			
			}
			else throw std::invalid_argument("非法记号！"+symbol_table[i].second);
		
		

	}

	void match(const std::string &s){
		
			if (i<symbol_table.size() && s == symbol_table[i].second)
				i++;
			else throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		

	}

	void Query(){
		match(21);
		sellist();
		match(22);
			from();
			if (i < symbol_table.size() && 23 == symbol_table[i].first)
			{
				i++;
				conditions();
			}
#ifdef PARSERDEBUG
			std::cout << "匹配Query" + symbol_table[i].second << std::endl;

#endif
	}

	void sellist(){
		attribute();
		while (i<symbol_table.size() && symbol_table[i].first == 4)
		{
			i++;
			attribute();

		}
#ifdef PARSERDEBUG
		std::cout << "匹配sellist" + symbol_table[i].second << std::endl;

#endif
	}
	void from(){
		relation();
		while (i<symbol_table.size() && symbol_table[i].first == 4)
		{
			i++;
			relation();

		}
#ifdef PARSERDEBUG
		std::cout << "匹配from" + symbol_table[i].second << std::endl;

#endif
	}
	void conditions(){
		condition();
		while (i<symbol_table.size() && symbol_table[i].first == 27)
		{
			i++;
			condition();
		}
#ifdef PARSERDEBUG
		std::cout << "匹配conditions" + symbol_table[i].second << std::endl;

#endif
	}

	void condition(){
		attribute();
		if (i<symbol_table.size() && symbol_table[i].first == 3)
		{
		//	match(3);
			i++;
			attribute();
		}
		else if (i<symbol_table.size() && symbol_table[i].first == 28)
		{
		
			//match(28);
			i++;
			
			match(0);
			//此处可能造成无穷递归
			Query();
			match(1);
		
		}
		else {
			//这里的match未被注释，是因为上面的两个选择路径已有判断递增，这里没有
			match(29);
			match(5);
			pattern();
			match(5);
		
		}
#ifdef PARSERDEBUG
		std::cout << "匹配condition" + symbol_table[i].second << std::endl;

#endif


	}

	void attribute(){
		//匹配当前数据库的任意属性
		//尚未实现
		if(i>=symbol_table.size() )
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		i++;


	}
	void relation(){
		//必须是表名
		//尚未实现
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		i++;

	}
	void pattern(){
		//必须是单引号括起来的SQL字符串
		//尚未实现
		if (i >= symbol_table.size())
			throw std::invalid_argument("非法记号！" + symbol_table[i].second);
		i++;

	}

















	
	std::vector<token>  symbol_table ;
	//(decltype (std::vector<token>.size())) i = 0;
	std::vector<token>::size_type i = 0;


};












int main()
{



	lexer l;
	//右值引用：测试
	std::vector<token>  symbol_table;
	

	//右值引用：测试
	symbol_table = move(l("INSERT INTO SPJ( SNO, JNO, PNO, QTY) VALUES(北京, J6, P4); "));
	for (auto a : symbol_table)
	{
		std::cout << a.first << ":" << a.second << std::endl;
	}
	decltype(symbol_table.size()) n = 0;
	std::cout <<  "DECLTYPEtest  "<< n<<std::endl;
	symbol_table = move(l("select t from 产品 where 单价=6000 and 产品名称 in (select * from it )"));
	std::cout << "sad";
	std::cout <<symbol_table.size() << std::endl;

	//若输入非法，Lexer抛出异常，symbol_table清空
	if (symbol_table.size() > 0)
	{
		for (auto a : symbol_table)
		{
			std::cout << a.first << ":" << a.second << "  ";
		}
		std::cout << std::endl;

		parser ps(symbol_table);
		ps.lanch();
	}
	return 0;
}