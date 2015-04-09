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