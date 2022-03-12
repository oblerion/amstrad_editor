#ifndef dirent2_hpp
#define dirent2_hpp
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <dirent.h>
struct dirent2
{
	dirent2(){}
	struct dir2
	{
		char type='o';
		std::string name="";
	};
	std::vector<struct dir2> lp;
	struct dirent* sdir=0;
	DIR* rep=0;
	int nb=0;
	void scan(std::string pstr);
	void print();
	std::string Name_at(int id);
	char Type_at(int id);
};
#endif
