#include "dirent2.hpp"
void dirent2::scan(std::string pstr)
{
	struct dir2 td;
	if(this->nb>0) this->nb=0;
	if(this->lp.size()>0) this->lp.clear();
	this->rep = opendir(pstr.c_str());
	if(this->rep)
	{
		this->sdir=readdir(this->rep);
		while(this->sdir)
		{
			if(this->sdir->d_name[0]!='.' && 
				this->sdir->d_name[1]!='.')
			{ 
	
				td.name = this->sdir->d_name;
				this->nb=this->nb+1;
				switch(this->sdir->d_type)
				{
					case 4:
					case 10:
					case 16384:
						td.type='d';
					break;
					case 8:
					case 32768:
						td.type='f';
					break;
					default:
						printf("\n dir : %s ,unknow type : %d\n",sdir->d_name,sdir->d_type);

				}
				lp.push_back(td);
			}
			this->sdir=readdir(this->rep);
		}
		closedir(this->rep);
		free(this->sdir);
	}
}
void dirent2::print()
{
	printf("\n -- dirent2 print --\n");
	for(int i=0;i<this->nb;i++)
	{
		if(this->lp[i].type=='f')
			printf("id %d file : %s\n",i,this->lp[i].name.c_str());
		else if(this->lp[i].type=='d')
			printf("id %d folder : %s\n",i,this->lp[i].name.c_str());
	}
	printf("nb = %d",this->nb);
	printf("\n -- dirent2 print --\n");
}
std::string dirent2::Name_at(int id)
{
	if(id > -1 && id < this->nb)
		return this->lp[id].name;
	return "";
}
char dirent2::Type_at(int id)
{
	if(id > -1 && id < this->nb)
		return this->lp[id].type;
	return 'o';
}