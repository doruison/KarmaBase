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
























	int main()
	{



		lexer l;

		std::vector<token>	symbol_table;
		std::string s;

		std::getline(std::cin, s);
		symbol_table = l(s);
		std::cout << "adasasdasd";
		//�Ƿ����������ڷ��ű�������������Խ�磬ע����ǰ�ж�Ԥ����
		if (symbol_table.size() == 0)
			return 0;
		for (auto a : symbol_table)
		{
			std::cout << a.first << ":" << a.second << std::endl;
		}
		parser ps(symbol_table);
		ps.lanch(); 
	//	decltype(symbol_table.size()) n = 0;
	//	symbol_table = l("select t from ��Ʒ where ���� =60.900 and ��Ʒ���� in (select * from it )");
	//	std::cout << symbol_table.size() << std::endl;
		std::cout << " DECLTYPEtest  " << std::endl;



		return 0;
}