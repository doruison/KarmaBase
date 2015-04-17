#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<cctype>
#include<numeric>
#include <memory>
#include <gtest/gtest.h>
#include <map>
#include<unordered_map>
#include<cwctype>
#include"QC.h"
#include <cstring>



std::vector<token> lexer::operator()(const std::string &s){
	symbol_table.clear();
	input = s;
	std::cout <<"flags" ;
	try{
		for (unsigned int i = 0; i < input.size(); i++)
		{

			std::cout << input[i];
			if (iswspace(input[i]))
				continue;
			if (input[i] == '\'')
			{
				
				symbol_table.push_back(sqlstring(i));
				
				continue;
			
			}
			if (other_token.count(input[i]))
			{
				symbol_table.push_back((other_token.find(input[i]))->second);
				
				continue;
			}
			if (!iswpunct(input[i]) && !iswspace(input[i]))
			{
				if (iswdigit(input[i]))
				{
					symbol_table.push_back(digit(i));
					i--;
				
				}
				else
				{
					symbol_table.push_back(name(i));
					i--;
				}
				continue;

			}		
			throw std::invalid_argument("非法输入1!");
		}

	}
	catch (std::invalid_argument ia){
		std::cout << ia.what() << std::endl;
		symbol_table.clear();


	}
	return symbol_table;

}

token lexer::name(unsigned int &i){
	unsigned cachei = i;
	while (i<input.size()&&!iswpunct(input[i]) && !iswspace(input[i]))
	{
		i++;
	//	std::cout <<i<< input[i];
	}
	if (keyword.count(std::string(input, cachei, i - cachei)))
		return *new token{ keyword.find(std::string(input, cachei, i - cachei))->second, std::string(input, cachei, i - cachei) };
	else	return *new token{ NAMEORDER, *(new std::string(input, cachei, i - cachei)) };
}

token lexer::sqlstring(unsigned int &i){
	unsigned cachei = i;
	if (i>=input.size())
		throw std::invalid_argument("非法输入2");
	i++;
	while (i<input.size() && input[i]!='\'')
	{
		i++;
		//	std::cout <<i<< input[i];
	}
	if (input[i] != '\'')
		throw std::invalid_argument("非法输入2!");
	std::cout << "string" << cachei  <<"  "<< i  << * (new std::string(input, cachei + 1, i - cachei +3));
			return *new token{ NAMEORDER+2, *(new std::string(input, cachei+1, i - cachei-1)) };
}

token lexer::digit(unsigned int &i){
	unsigned cachei = i;
	while (i<input.size() && !iswpunct(input[i]) && iswdigit(input[i]))
	{
		i++;
		//	std::cout <<i<< input[i];
	}
	if (i<input.size() && input[i] == '.')
	{
		i++;
		while (i < input.size() && !iswpunct(input[i]) && iswdigit(input[i]))
		{
			i++;
			//	std::cout <<i<< input[i];
		}
		//real型（小数）
		return *new token{ NAMEORDER+3 , *(new std::string(input, cachei, i - cachei)) };

	}
	//int整数
		return *new token{ NAMEORDER+4, *(new std::string(input, cachei, i - cachei)) };
}





