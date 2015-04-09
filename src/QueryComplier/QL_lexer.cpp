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

#include <cstring>

using namespace std;

typedef pair<int, std::string> token;

const std::map<char, token> other_token = { { '(', { 0, "lquote" } }, { ')', { 1, "rquote" } },	  { ';', { 2, "semi" } }, { '=', { 3, "equal" } }, { ',', { 4, "comma" } }, { '\'', { 5, "squote" } }, { '*', { 6, "all" } } };

class lexer{
public:	lexer(){}




	vector<token> operator()(const string &s){
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
				throw invalid_argument("非法输入!");
			}

		}
		catch (invalid_argument ia){
		cout<<	ia.what()<<endl;


		}
		return symbol_table;

	}

private:
	token name(int &i){
		int cachei = i;
		while (!iswpunct(input[i]) && !iswspace(input[i]))
			i++;
		return *new token{ 20, *(new string(input, cachei, i - cachei)) };
	}



	vector<token> symbol_table;

	string input;
	string tc;





};






int main()
{
	
	

	lexer l;
	//右值引用：测试
	vector<token> && symbol_table = move(l("!#$&*( ^^%INSERT INTO SPJ( SNO, JNO, PNO, QTY) VALUES(北京, J6, P4); ")); 
	for (auto a : symbol_table)
	{
		cout <<a.first <<":"<<a.second<<endl;
	}
	
	//右值引用：测试
	symbol_table  =move( l("INSERT INTO SPJ( SNO, JNO, PNO, QTY) VALUES(北京, J6, P4); "));
	for (auto a : symbol_table)
	{
		cout << a.first << ":" << a.second << endl;
	}


	return 0;
}
