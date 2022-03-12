#include "cfile.hpp"

Cfile::Cfile(std::string file)
{
	this->read(file);
}
void Cfile::write(std::string file)
{
	FILE* fic = 0;
	//char* tstr=0;
	fic = fopen(file.c_str(),"w");
	if(fic != 0)
	{
		fprintf(fic,"%s",this->data.c_str());
		fclose(fic);
	}
}

void Cfile::read(std::string file)
{
	FILE* fic = 0;
	char* tstr=0;
	long int res=0;
	fic = fopen(file.c_str(),"r");
	if(fic != 0)
	{
		fseek(fic,0,SEEK_END);
		res=ftell(fic);
		//printf("%ld",res);
		tstr = (char*)malloc(res);
		fseek(fic,0,SEEK_SET);
		while(fgets(tstr,res,fic)!=NULL)
		{
			this->data+=tstr;
		}
		fclose(fic);
		this->name=file;
		free(tstr);
	}else 
	{
		this->data.clear();
		this->name.clear();
		puts("no file");
	}
} 

