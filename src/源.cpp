#include <iostream>
#include <string>
#include <fstream>
#include "PF.H"
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

#define PAGESIZE 4092
#define BUFFERSIZE 40
#define TERMSIZE 10
#define HEADERINFOSIZE 128



using namespace std;



class header{
public:
	



	long termsamo;
	int termsize[TERMSIZE];
	char s[HEADERINFOSIZE] ;

};

fstream & operator<<(fstream & of,const header &h){
	of.seekp(0);

	//必须在末尾加入空白符才能区分。也就是说同一类型，长度并不是固定的。int有可能是一或四。
	//to_string可自动添加空白符
	of<<to_string( h.termsamo);

	//while (of.tellp() < sizeof(int))
	//	of << '\0';
	of.seekp(sizeof(int));
	for (long i = 0; i < h.termsamo; i++)
	{
		of.seekp(sizeof(int)*(i+1));
		of <<to_string( h.termsize[i]);
		//auto t=of.tellp();
		//while (of.tellp() < sizeof(int)*(i + 2))
		//	of << '\0';

	
	
	}
	of.seekp((2+TERMSIZE)*sizeof(int));
	//c风格字符串输出中反而会丢弃空白符
	of << h.s;
	of << '\0';
	return of;

}

fstream &operator>>(fstream & inf, header &h){
	inf.seekg(0);

	inf >> h.termsamo;
	inf.seekg(sizeof(int));
	for (int i = 0; i < h.termsamo; i++)
	{
		inf.seekg(sizeof(int)*(i + 1));
		inf >> h.termsize[i];


	}
	inf.seekg((1 + TERMSIZE)*sizeof(int));
	inf >> h.s;
	return inf;







}






















	int main()
	{

		//文件若不存在，需要用纯out模式先打开（建立）
	//	std::ofstream ofile("pagefile");
		//ofile.closed();
		std::fstream file("pagefile");
		if (file.is_open())
			std::cout << "true";
		else cout << "false";
		header h;
		h.termsamo = 3;
		h.termsize[0] = 2;
		h.termsize[1] = 3;
		h.termsize[2] = 4;
		//string s;
	//	cin >> s;
		//*(h.s) = "adasdasf";
		//字面量初始化可自动追加空格
		char	s[] = "多年以后，奥雷连诺上校站在行刑队面前，准会想起父亲带他去参观冰块的那个遥远的下午。";
			cout <<"lens"<< strlen(s);

		
		
		cout <<"lens"<< strlen(s);


		strcpy(h.s, s);
		
		file << h;
		header h2;
		file >> h2;
		cout << h2.s;


		//file.seekg();
	//	file.write(h.termsnum);






		file.close();

		file.open("百年孤独.txt");
		void *p=malloc(PAGESIZE);
		char *ms =static_cast< char	 *>( p);
		//strncpy(s,"flags",5);
	//	file.write(reinterpwsret_cast< char *>(p), PAGESIZE);

	//	free(p);
	
		fstream of("0.txt");
		file.read(ms,PAGESIZE-1);
		of.write(ms, PAGESIZE - 1);



		return 0;
}