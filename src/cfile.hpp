#ifndef cfile_hpp
#define cfile_hpp
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
struct Cfile
{
	std::string name="";
	std::string data="";
	Cfile(std::string file);
	Cfile(){}
	void write(std::string file);
	void read(std::string file);
};
#endif
