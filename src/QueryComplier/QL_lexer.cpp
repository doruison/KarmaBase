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
	input = s;
	try{
		for (auto i = 0; i < (int)input.size(); i++)
		{

			if (iswspace(input[i]))
				continue;
			if (other_token.count(input[i]))
			{
				symbol_table.push_back((other_token.find(input[i]))->second);
				continue;
			}

			if (!iswpunct(input[i]) && !iswspace(input[i]))
			{
				symbol_table.push_back(name(i));
				i--;
				continue;

			}
			throw std::invalid_argument("�Ƿ�����!");
		}

	}
	catch (std::invalid_argument ia){
		std::cout << ia.what() << std::endl;


	}
	return symbol_table;

}

token lexer::name(int &i){
	int cachei = i;
	while (!iswpunct(input[i]) && !iswspace(input[i]))
		i++;
	if (keyword.count(std::string(input, cachei, i - cachei)))
		return *new token{ keyword.find(std::string(input, cachei, i - cachei))->second, std::string(input, cachei, i - cachei) };
	else	return *new token{ NAMEORDER, *(new std::string(input, cachei, i - cachei)) };
}





