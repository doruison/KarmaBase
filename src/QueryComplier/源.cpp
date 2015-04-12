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
				std::cout << "ƥ��" + symbol_table[i].second<<std::endl;

#endif
			
			}
			else throw std::invalid_argument("�Ƿ��Ǻţ�"+symbol_table[i].second);
		
		

	}

	void match(const std::string &s){
		
			if (i<symbol_table.size() && s == symbol_table[i].second)
				i++;
			else throw std::invalid_argument("�Ƿ��Ǻţ�" + symbol_table[i].second);
		

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
			std::cout << "ƥ��Query" + symbol_table[i].second << std::endl;

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
		std::cout << "ƥ��sellist" + symbol_table[i].second << std::endl;

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
		std::cout << "ƥ��from" + symbol_table[i].second << std::endl;

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
		std::cout << "ƥ��conditions" + symbol_table[i].second << std::endl;

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
			//�˴������������ݹ�
			Query();
			match(1);
		
		}
		else {
			//�����matchδ��ע�ͣ�����Ϊ���������ѡ��·�������жϵ���������û��
			match(29);
			match(5);
			pattern();
			match(5);
		
		}
#ifdef PARSERDEBUG
		std::cout << "ƥ��condition" + symbol_table[i].second << std::endl;

#endif


	}

	void attribute(){
		//ƥ�䵱ǰ���ݿ����������
		//��δʵ��
		if(i>=symbol_table.size() )
			throw std::invalid_argument("�Ƿ��Ǻţ�" + symbol_table[i].second);
		i++;


	}
	void relation(){
		//�����Ǳ���
		//��δʵ��
		if (i >= symbol_table.size())
			throw std::invalid_argument("�Ƿ��Ǻţ�" + symbol_table[i].second);
		i++;

	}
	void pattern(){
		//�����ǵ�������������SQL�ַ���
		//��δʵ��
		if (i >= symbol_table.size())
			throw std::invalid_argument("�Ƿ��Ǻţ�" + symbol_table[i].second);
		i++;

	}

















	
	std::vector<token>  symbol_table ;
	//(decltype (std::vector<token>.size())) i = 0;
	std::vector<token>::size_type i = 0;


};












int main()
{



	lexer l;
	//��ֵ���ã�����
	std::vector<token>  symbol_table;
	

	//��ֵ���ã�����
	symbol_table = move(l("INSERT INTO SPJ( SNO, JNO, PNO, QTY) VALUES(����, J6, P4); "));
	for (auto a : symbol_table)
	{
		std::cout << a.first << ":" << a.second << std::endl;
	}
	decltype(symbol_table.size()) n = 0;
	std::cout <<  "DECLTYPEtest  "<< n<<std::endl;
	symbol_table = move(l("select t from ��Ʒ where ����=6000 and ��Ʒ���� in (select * from it )"));
	std::cout << "sad";
	std::cout <<symbol_table.size() << std::endl;

	//������Ƿ���Lexer�׳��쳣��symbol_table���
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