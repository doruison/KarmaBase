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
std::cout << input;
	try{
		for (auto i = 0; i < (int)input.size(); i++)
		{
			std::cout << "1sda";
			if (iswspace(input[i]))
				continue;
			if (other_token.count(input[i]))
			{
				symbol_table.push_back((other_token.find(input[i]))->second);
				continue;
			}
			std::cout << " 2sda";
			if (!iswpunct(input[i]) && !iswspace(input[i]))
			{
				symbol_table.push_back(name(i));
				i--;
				continue;

			}		
			std::cout << " 3sda";
			throw std::invalid_argument("·Ç·¨ÊäÈë!");
		}

	}
	catch (std::invalid_argument ia){
		std::cout << ia.what() << std::endl;
		symbol_table.clear();


	}
	return symbol_table;

}

token lexer::name(int &i){
	int cachei = i;
	while (i<input.size()&&!iswpunct(input[i]) && !iswspace(input[i]))
	{
		i++;
		std::cout <<i<< input[i];
	}
	std::cout << " 4sda" << std::string(input, cachei, i - cachei);
	if (keyword.count(std::string(input, cachei, i - cachei)))
		return *new token{ keyword.find(std::string(input, cachei, i - cachei))->second, std::string(input, cachei, i - cachei) };
	else	return *new token{ NAMEORDER, *(new std::string(input, cachei, i - cachei)) };
}





