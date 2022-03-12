  #include <cstdio>
  #include <cstdlib>
  #include <string>
  #include <vector>
  #include "dirent2.hpp"
  #include "cfile.hpp"
   using namespace std;
   const vector<string> vcom = {
	   "save","load","del","close","dir","copy",
	   "help","color","lang","quit","exit","ls"
	};

	#ifdef WIN32
	#include <windows.h>
		inline void delay( unsigned long ms )
		  {
		  Sleep( ms );
		  }
		const string C_clear="cls";
		const string C_copy="copy";
		const string C_move="move";
		const string C_del="del";
		const string C_dir="dir";
		const string C_del_dir="rmdir"; 
	#else  /* POSIX */
		#include <unistd.h>
		inline void delay( unsigned long ms )
		  {
		  usleep( ms * 1000 );
		  }
		const string C_clear="clear";
		const string C_copy="cp";
		const string C_move="mv";
		const string C_del="rm";
		const string C_dir="ls";
		const string C_del_dir="rmdir"; 
	#endif 
	int strfind(string a, string b)
	{
		// if(a.find(b,0) == string::npos) return -1;
		// if(a.find(b,0) >= 0) return a.find(b,0);
		const int sa = a.size();
		const int sb = b.size();
		int e=0,i,cnt=0,pos=-1;
		if(sb>sa) return -1;
		for(i=0;i<sa;i++)
		{
		  if(a[i] == b[e])
		  {
			if(pos==-1) pos=i;
			if(++cnt == sb) return pos;
			++e;
		  }
		  else
		  {
			cnt=0;
			pos=-1;
			e=0;
		  }
		}
		return -1;
	}
struct amstrad_editor
{ 
	int color = 2;
	int run = 1;
	string mem;
	vector<string> vtab;
	string lang = "en"; 
	struct Cfile cf;
	struct dirent2 d2;
	~amstrad_editor()
	{
		this->vtab.clear();
	}
	void ui_help()
	{
		if(this->lang=="fr")
		{
			puts("\nliste de commande :");
			puts("------gestion des projets -------");
			puts("save [nom de projet]   sauvegarde le fichier");
			puts("load [nom de projet]   charge le contenu du fichier");
			puts("del [nom de projet]    supprime le dossier et/ou le fichier source");
			puts("------commande editeur------------");
			puts("[numero de ligne] [code de la ligne]     cree une ligne de code en local");
			puts("[numero de ligne]                        efface la ligne en local");
			puts("dir                                      liste tout les dossiers fichier");
			puts("copy [A] to [B]                          copie la ligne A ver B");
			puts("quit                                     ferme le logiciel");
			#ifdef _WIN32
				puts("color [A]                                numero A de couleur");
			#endif
			puts("lang [fr ou en]                          change la langue (francais ou anglais)");
			puts("close                                    ferme le fichier locale");
			puts("");
	   } 
	   else if(this->lang=="en")
	   {
			puts ("\ncommand list:");
			puts ("------ project management -------");
			puts ("save [filename or full pass name]   saves the file");
			puts ("load [filename or full pass name]   loads the file locally");
			puts ("del [filename or directory]         delete the sourse folder and/or file");
			puts ("------ editor command ------------");
			puts ("[line number] [line code]                create a line of code locally");
			puts ("[line number]                            delete line locally");
			puts ("dir                                      lists all folders file");
			puts ("copy [A] to [B]                          copy line A to B");
			puts ("quit                                     close the software");
			#ifdef _WIN32
				puts ("color [A]                                color A 's number");
			#endif
			puts ("lang [fr or en]                          change language (french or english)");
			puts("close                                     close local file");
			puts("");
		}  
	}
	void ui_title()
	{
		printf("                                               ###                   ##    ##       ##\n");
		printf("   ####                                         ##                   ##    ##       ##\n");
		printf("  ##  ##                                        ##                   ##             ##\n");
		printf(" ##        #####   ## ###    #####    #####     ##      #####    ######  ####     ######\n");
		printf(" ##       ##   ##  ###  ##  ##       ##   ##    ##     ##   ##  ##   ##    ##       ##\n");
		printf(" ##       ##   ##  ##   ##   ####    ##   ##    ##     #######  ##   ##    ##       ##\n");
		printf("  ##  ##  ##   ##  ##   ##      ##   ##   ##    ##     ##       ##   ##    ##       ##\n");
		printf("   ####    #####   ##   ##  #####     #####    ####     #####    ######  ######      ###\n");
		printf("\nprototype 1980 naberon v1          by oblerion\n");
		if(this->lang=="fr") 
		{
			printf("langage: francais\n");
			printf("taper help pour plus d'aide\n");
		}
		else if(this->lang=="en")
		{
			printf("language: english\n");
			printf("type help for more help\n");
		}
	}

	void get_input()	
	{
		char cmem[100];
		fflush(stdin);
		fgets(cmem,100,stdin);
		this->mem = cmem;
		this->mem.pop_back();
	}
	string get_string_com(const vector<string> vcom)
	{
		int i;
		int cid=-1;
		// get id command
		for(i=0;i<(signed int)vcom.size();i++)
		{
			if(this->mem.size()>vcom[i].size())
			{
				if(this->mem.substr(0,vcom[i].size())==vcom[i])
				{
					this->mem = this->mem.substr(vcom[i].size()+1,this->mem.size()-vcom[i].size());
					cid=i;
					break;
				}
			}
			else if(this->mem.size()==vcom[i].size() &&
			this->mem==vcom[i])
			{
				cid=i;
				break;
			}
		}
		if(cid >-1) return vcom[cid];
		return "";
	}
	void print_file()
	{
		int i;
		if(this->lang=="en")
			printf("| file: %s|\n",this->cf.name.c_str());
		else if(this->lang=="fr")
			printf("| fichier: %s|\n",this->cf.name.c_str());
		for(i=0;i<(signed int)this->vtab.size();i++)
		{
			printf("%d %s\n",i,this->vtab[i].c_str());
		}
	}
	void loop()
	{
		int i;
		int num;
		string tstr;
		string idstr;
		this->ui_title();
		while(this->run)
		{
			this->get_input();
			if(!this->mem.empty())
			{
				system(C_clear.c_str());
				idstr=this->get_string_com(vcom);
				//save
				if(idstr=="save")
				{
					this->cf.data="";
					tstr="";
					for(i=0;i<(signed int)this->vtab.size();i++)
					{
						this->cf.data += this->vtab[i] + "\n";
					}
					if(this->mem=="save")
					{
						if(!this->cf.name.empty())
						this->cf.write(this->cf.name);
					}
					else
					{
						if(this->mem.find("/")==string::npos)
						{
							this->cf.write(this->mem);
							this->cf.name=this->mem;
						}
						else
						{
							//printf("f// %lu",this->mem.find("/",-1));
							for(i=this->mem.size();i>0;i--)
							{
								if(this->mem[i]=='/')
								{
									tstr=this->mem.substr(0,i);
									this->d2.scan(tstr);
									tstr=this->mem.substr(i+1,this->mem.size());
									break;
									puts(tstr.c_str());
								}
							}

							for(i=0;i<(signed int)this->d2.lp.size();i++)
							{
								if(this->d2.Name_at(i)==tstr)
								{
									this->cf.write(this->mem);
									this->cf.name=this->mem;
									tstr="";
									break;
								}
							}
							if(!tstr.empty())
							{
								tstr.clear();
								if(this->lang=="en") puts(("this directory not exist at "+this->mem).c_str());
								if(this->lang=="fr") puts(("le dossier "+this->mem+" n'existe pas").c_str());
								delay(1000);
								system(C_clear.c_str());
							}
						}
					}
					this->cf.data.clear();
					if(this->cf.name.empty())this->ui_title();
					else this->print_file();
				}
				// load
				else if(idstr=="load")
				{
					this->cf.read(mem);
					if(!this->cf.name.empty())
					{
						tstr="";
						for(i=0;i<(signed int)this->cf.data.size();i++)
						{
							if(cf.data[i]!='\n')
							{
								tstr += this->cf.data[i];
							}
							else
							{
								this->vtab.push_back(tstr);
								tstr.clear();
							}
						}
						this->cf.data.clear();
						if(this->lang=="en")puts("loading - ok");
						if(this->lang=="fr")puts("chargement - ok");
						delay(1000);
						system(C_clear.c_str());
						this->print_file();
					}
					else 
					{
						if(this->lang=="en")puts("loading - error");
						if(this->lang=="fr")puts("chargement - erreur");
						delay(1000);
						system(C_clear.c_str());
						this->ui_title();
					}
				}
				else if(idstr=="del")
				{
					char tc='b';
					while(tc!='y' && tc!='n')
					{
						system(C_clear.c_str());
						if(this->lang=="fr") puts(("Voulez-vous supprimer "+this->mem+" ? [y] oui [n] non").c_str());
						if(this->lang=="en") puts(("Do you want to delete "+this->mem+" ? [y] yes [n] no").c_str());
						tc = getchar();
					}
					if(tc=='y') 
					{
						system((C_del+" "+this->mem).c_str());
						if(this->lang=="en")puts("deleting - ok");
						if(this->lang=="fr")puts("suppression - ok");
	
					}
					else
					{
						if(this->lang=="en")puts("back ...");
						if(this->lang=="fr")puts("retour ...");
					}
					delay(1000);
					system(C_clear.c_str());
					this->ui_title();
				}
				// close
				else if(idstr=="close")
				{
					this->cf.name.clear();
					this->cf.data.clear();
					this->vtab.clear();
					this->ui_title();
				}
				// help
				else if(idstr=="help")
				{
					this->ui_help();
				}
				// lang
				else if(idstr=="lang")
				{
					if(this->mem=="fr") this->lang="fr";
					if(this->mem=="en") this->lang="en";
					if(this->cf.name.empty())this->ui_title();
					else this->print_file();
				}
				else if(idstr=="dir")
				{
					if(this->mem=="dir")this->mem=".";
					this->d2.scan(this->mem);
					puts(("in dir "+this->mem).c_str());
					for(i=0;i<this->d2.nb;i++)
					{
						if(this->d2.Type_at(i)=='f')
						{
							if(this->lang=="en")printf("id %d file : %s\n",i,this->d2.Name_at(i).c_str());
							if(this->lang=="fr")printf("id %d fichier : %s\n",i,this->d2.Name_at(i).c_str());
						}
						else if(this->d2.Type_at(i)=='d')
						{
							if(this->lang=="en")printf("id %d folder : %s\n",i,this->d2.Name_at(i).c_str());
							if(this->lang=="fr")printf("id %d dossier : %s\n",i,this->d2.Name_at(i).c_str());
						}
					}
				}
				else if(idstr=="ls")
				{
					if(this->cf.name.empty())this->ui_title();
					else this->print_file();
				}
				else if(idstr=="copy")
				{
					if(this->mem.find("to")!=string::npos)
					{
						int pos1 = atoi(this->mem.substr(0,this->mem.find("to")-1).c_str());
						int pos2 = atoi(this->mem.substr(this->mem.find("to")+2,this->mem.size()).c_str());
						if(pos1 < (signed int)this->vtab.size() && pos2 < (signed int)this->vtab.size())
						{
							this->vtab[pos2]=this->vtab[pos1];
						}
					}
					if(this->cf.name.empty())this->ui_title();
					else this->print_file();
				}
				else if(idstr=="color")
				{
					this->color = atoi(this->mem.c_str());
					if(this->color>-1 && this->color<10)
					{
					#ifdef _WIN32
						system(("color "+this->mem).c_str());
					#endif
					}
					if(this->cf.name.empty())this->ui_title();
					else this->print_file();
				}
				// exit
				else if(idstr=="exit" || idstr=="quit")
				{
					this->run=0;
				}
				else 
				{ 
					// edit ligne with void string
					num = atoi(mem.c_str());
					if(num >= 0 && 
						mem.find(" ")==string::npos)
					{
						if(num < (signed int)this->vtab.size())
						{
							this->vtab[num].clear();
							
						}
						// cleaning
						while(this->vtab[this->vtab.size()-1].empty())
						{
							this->vtab.pop_back();
							if(this->vtab.size()==0) break;
						}
						this->print_file();
					}
					else if(mem.find(" ")>=1)
					{
						num = atoi(mem.substr(0,mem.find(" ")).c_str());
						if(num < (signed int)this->vtab.size())
						{
							this->vtab[num] = mem.substr(mem.find(" "),mem.size()-mem.find(" "));
						}
						else
						{
							num = num - (signed int)this->vtab.size() ;
							for (i=0;i<num;i++)
							{
								this->vtab.push_back("");
							}
							this->vtab.push_back(mem.substr(mem.find(" "),mem.size()-mem.find(" ")));
							
						}
						this->print_file();
					}
				 else 
				 {
				   puts("syntax error");
				 }
				}
			}
		}
	}


};
int main()
{
	struct amstrad_editor aed;
	aed.loop();
	return 0;
}
