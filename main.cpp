  #include<cstdio>
  #include<cstdlib>
  #include<string>
  #include <iostream>
  #include <fstream>
  #include<string.h>

  #ifdef _WIN32
    #include <windows.h>
    inline void delay( unsigned long ms )
      {
      Sleep( ms );
      }
  #else  /* POSIX */
    #include <unistd.h>
    inline void delay( unsigned long ms )
      {
      usleep( ms * 1000 );
      }
  #endif 

  using namespace std;
  int strfind(string, string);
  string strsub(string,int,int);
  void printTxt(string,int pcolor);
  void Title(string);
  void textcolor(int);
  void List(string*);
  // fstream openfile(string file,char mode);

  const int lignelimit = 3000+1;
  const int Color = 2;

  int main()
  {

   int run = 1;
   char cmem[100];
   string mem;
   string tab[lignelimit];
   string tt; 
   string file;
   string lang = "en"; 
   // char* filename;
   for(int i=0;i<lignelimit;i++) tab[i]="";
   int num;
   //FILE* fic=NULL;
   fstream fic;
  textcolor(Color); 
  Title(lang);
   while(run == 1)
   {
  	 fflush(stdin);
  	 fgets(cmem,100,stdin);
  	 mem = cmem;
  	 //mem[length]='\0';

  	 // else if(strfind(mem,"save") == 0)
  	 // {
  		// fic.open("main.amd",ios::out);
  		 // for(int i=0;i<lignelimit-1;i++)
  		 // {
  			 // if(tab[i].empty() == false)
  				// fic << tab[i] + "\n"; //fprintf(fic,"%s",ct);
  			 // // else fic << "\n";
  		 // }
  		 // fic.close();
  		 // tt="ren main.amd " + strsub(mem,4,mem.size()) + "//main.amd";
  		 // system(tt.c_str());
  	 // }
  	 // else if(strfind(mem,"load") == 0)
  	 // {
  		  // // string mtab[lignelimit];
  		  // if(strsub(mem,5,mem.size()).empty() == false)
  		  // {
  			  // tt = "copy " + strsub(mem,4,mem.size()) + ".";
  			  // system(tt.c_str());
  			  // tt = "move " + strsub(mem,4,mem.size()) + " main.amd";
  			  // system(tt.c_str());
  		  // }
  			// string eee;
  			// int pt;
  			// fic.open("main.amd",ios::in);
  			// for(int i=0;i<lignelimit-1;i++)
  			// {
  				// getline(fic,eee);
  				// pt = atoi(strsub(eee,0,strfind(eee," ")).c_str());
  				
  				// if(eee.size() == 0)
  				// {
  					// tab[pt].clear();
  				// }
  				// else
  				// {
  					// if( pt < lignelimit && pt > 0) tab[pt] = strsub(eee,0,eee.size());
  				// }
  			// }
  			// fic.close();
  	 // }
  	 if(strfind(mem,"quit") == 0) run = 0;
  	 else if(strfind(mem,"new") == 0)
  	 {
  		 tt = "mkdir " + strsub(mem,4,mem.size());
  		 system(tt.c_str());
  		// fic.open("main.amd",ios::out);
  		// fic.close();
  		 // tt="move main.amd " + strsub(mem,4,mem.size()) + "//main.amd";
  		 // system(tt.c_str());
  		
  	 }
	 else if(strfind(mem,"close")==0)
	 {
		for(int i=0;i<lignelimit-1;i++)
		{
				tab[i].clear();
		}
		file = "";
		system("CLS");
	 }
  	 else if(strfind(mem,"del") == 0)
  	 {
  		tt="del " + strsub(mem,4,mem.size()) + "/.";
  		system(tt.c_str());
  		tt="rmdir " + strsub(mem,4,mem.size());
  		system(tt.c_str());
  	 }
  	 else if(strfind(mem,"copy") == 0)
  	 {
  		 int pos1 = stoi(strsub(mem,4,strfind(mem,"to")));
  		 int pos2 = stoi(strsub(mem,strfind(mem,"to")+2,mem.size()));
  		 string memo;
  		 memo = to_string(pos2);
  		 printf("%s",memo.c_str());
  		 memo += strsub(tab[pos1],strfind(tab[pos1]," "),tab[pos1].size());
  		 tab[pos2]=memo;
  	 }
	 
  	 // else if(strfind(mem,"edit")==0)
  	 // { // no work
  		 // char cc[100];
  		 // string st;
  		 // int pos1 = atoi(strsub(mem,5,mem.size()).c_str());
  		 // if(pos1 > -1 && pos1 < lignelimit)  
  		 // {
  			 // delay(100);
  			 // strcpy(cc,tab[pos1].c_str());
  			 // puts(cc);
  			 // fgets(cc,100,stdin);
  			 // tab[pos1] = to_string(pos1) + " ";
  			 // tab[pos1] += cc;
  		 // }
  	 // }
  	 else if(strfind(mem,"save") == 0)
  	 {
  		fic.open("export.amd",ios::out);
  		 for(int i=0;i<lignelimit-1;i++)
  		 {
  			 if(tab[i].empty() == false)
  				fic << strsub(tab[i],strfind(tab[i]," "),tab[i].size()) + "\n"; //fprintf(fic,"%s",ct);
  			 else fic << "\n";
  		 }
  		 fic.close();
		 if(mem.size() <= 5) {tt="move export.amd " + file;}
  		 else tt="move export.amd " + strsub(mem,5,mem.size());
  		 system(tt.c_str());
  	 }
  	 else if(strfind(mem,"load")==0)
  	 {
  		if(strfind(mem,"\n") != -1) 
			mem = strsub(mem,0,strfind(mem,"\n")) +  strsub(mem,strfind(mem,"\n")+1,mem.size());
  		if(strfind(mem,"/")!=-1) 
  		{
  			for(int i=mem.size();i>1;i--)
  			{
  			  if(mem[i] == '/') 
  			  {
  				   file = strsub(mem,i+1,mem.size());
  				   break;
  			  }
  			}
  			puts(("loading " + file).c_str());
  			tt = "copy " + strsub(mem,5,mem.size()-file.size()+2) + " .";// + file;
  			puts(tt.c_str());
  			system(tt.c_str());
  			tt = "move " + file + " main.amd";
  			system(tt.c_str());
  			tt = "copy main.amd main2.amd";
  			system(tt.c_str());
  			tt = "move main2.amd " + strsub(mem,4,mem.size()) ;
  			system(tt.c_str());   

  		}
  		else 
  		{
			file = strsub(mem,5,mem.size());
  			tt = "copy " + strsub(mem,5,mem.size()) + " main.amd";
  			system(tt.c_str());
  		}
  		string eee;
  		fic.open("main.amd",ios::in);
  		if(fic.is_open())
  		{
  			for(int i=0;i<lignelimit-1;i++)
  			{
  				getline(fic,eee);
  				if(eee.size() == 0)
  				{
  					tab[i].clear();
  				}
  				else
  				{
  					tab[i] = to_string(i) + " " + eee;
  				}
  			}
  			fic.close();
			system("del main.amd");
			printf("fichier : %s\n",file.c_str());
			List(tab);
  		}
  		else
  		{
  			if(lang == "fr") puts(("fichier "+ file + " est introuvable").c_str());
  			if(lang == "en") puts(("file "+ file + " can't be load").c_str());
  		}

  	 }
  	  else if(strfind(mem,"lang") == 0)
  	  {
  		  // if(strlen(strsub(mem,5,strlen(mem))) == 2)
  		  // {
  		string tempo;
  		tempo = strsub(mem,5,2);
  		if(strfind(tempo,"fr")==0 || strfind(tempo,"en")==0)
  		  lang = tempo;
  		if(strfind(lang,"fr")==0 || strfind(lang,"en")==0) 
  		{
  			//clrscr();
  			system("CLS");
  			Title(lang);
  		} 
  		  // }
  	  }
  	 else if(strfind(mem,"help") == 0)
  	 {
  		 if(strfind(lang,"fr") == 0)
  		 {
  			 puts("\nliste de commande :");
  			 puts("------gestion des projets -------");
  			 puts("new [nom de projet]    cree un nouveau dossier");
  			 puts("save [nom de projet]   sauvegarde le fichier");
  			 puts("load [nom de projet]   charge le contenu du fichier");
  			 puts("del [nom de projet]    supprime le dossier et/ou le fichier source");
  			 puts("------commande editeur------------");
  			 puts("[numero de ligne] [code de la ligne]     cree une ligne de code en local");
  			 puts("[numero de ligne]                        efface la ligne en local");
  			 puts("list                                     affiche toute les ligne en local");
  			 puts("dir                                      liste tout les dossiers fichier");
  			 puts("copy [A] to [B]                          copie la ligne A ver B");
  			 puts("quit                                     ferme le logiciel");
  			 puts("cls                                      efface l'ecrant");
  			 puts("color [A]                                numero A de couleur");
  			 puts("lang [fr ou en]                          change la langue (francais ou anglais)");
  			 puts("close                                    ferme le fichier locale");
			 puts("");
  		 } 
  		 if(strfind(lang,"en") == 0)
  		 {
  			puts ("\ncommand list:");
  			puts ("------ project management -------");
  			puts ("new [project name]                  creates a new folder");
  			puts ("save [filename or full pass name]   saves the file");
  			puts ("load [filename or full pass name]   loads the file locally");
  			puts ("del [filename or directory]         delete the sourse folder and/or file");
  			puts ("------ editor command ------------");
  			puts ("[line number] [line code]                create a line of code locally");
  			puts ("[line number]                            delete line locally");
  			puts ("list                                     displays all lines locally");
  			puts ("dir                                      lists all folders file");
  			puts ("copy [A] to [B]                          copy line A to B");
  			puts ("quit                                     close the software");
  			puts ("cls                                      clear the screen");
  			puts ("color [A]                                color A 's number");
  			puts ("lang [fr or en]                          change language (french or english)");
  			puts("close                                     close local file");
			puts("");
  		 }
  	 }
  	 else if(strfind(mem,"dir") == 0)
  	 {
  		 system("dir");
  	 }
  	 else if(strfind(mem,"list") == 0)
  	 {
  		List(tab);
  	 }
  	 else if(strfind(mem,"cls") == 0)
  	 {
  		 //clrscr();
  		 system("CLS");
		 printf("fichier : %s\n",file.c_str());
  	 }
  	 else if(strfind(mem,"color") == 0)
  	 {
  	  	int pos1 = atoi(strsub(mem,6,mem.size()).c_str());
  		if(pos1 <= 15 && pos1 > -1) 
  		{
  			textcolor(pos1);
  		}
  	 }
  	 // scanf("%d %s",&num,mem);
  	 else if(atoi(mem.c_str()) >= 0 && atoi(mem.c_str()) < lignelimit && strfind(mem," ")==-1)
  	 {
  		 num = atoi(strsub(mem,0,mem.size()).c_str()); 
  		 if(num < lignelimit) {tab[num].clear();system("CLS");printf("fichier : %s\n",file.c_str());List(tab); }
  	 }
  	 else if(mem[1] == ' ' && stoi(strsub(mem,0,1)) > -1) 
  	 {
  		 num = atoi(strsub(mem,0,1).c_str());
  		 if(strfind(mem,"\n") != -1) mem = strsub(mem,0,strfind(mem,"\n"));
  		 if(num < lignelimit) {tab[num]= mem;system("CLS");printf("fichier : %s\n",file.c_str());List(tab);}
  	 }
  	 else if(mem[2] == ' ' && atoi(strsub(mem,0,2).c_str()) > -1)
  	 {
  		 printf("%s",strsub(mem,0,2).c_str());
  		 num = atoi(strsub(mem,0,2).c_str());
  		 if(strfind(mem,"\n") != -1) mem = strsub(mem,0,strfind(mem,"\n"));
  		 if(num < lignelimit) {tab[num]= mem;system("CLS");printf("fichier : %s\n",file.c_str());List(tab);}
  	 }
 	 else if(mem[3] == ' ' && atoi(strsub(mem,0,3).c_str()) > -1)
  	 {
  		 printf("%s",strsub(mem,0,3).c_str());
  		 num = atoi(strsub(mem,0,3).c_str());
  		 if(strfind(mem,"\n") != -1) mem = strsub(mem,0,strfind(mem,"\n"));
  		 if(num < lignelimit) {tab[num]= mem;system("CLS");printf("fichier : %s\n",file.c_str());List(tab);}
  	 }
  	 else 
  	 {
  		 puts("\nsyntax error\n");
  	 }
  	 // printf("%d %s",num,mem);
  	
  	 delay(500);
   }
   // char* a = "0i123456";
   // // char* b = "i1234";
   // // printf("%s",b);
   // // strcat(b,"ee");
   // printf("%d",strfind(a,"14"));
   return 0;
  }
  void List(string* tab)
  {
  	 for(int i=0;i<lignelimit-1;i++)
  	 {
  		 if(tab[i].empty() == false ) 
  		 {
  			 puts(tab[i].c_str());
  		 }
  	 }
  }
  void Title(string lang)
  {
  	printf("                                               ###                   ##    ##       ##\n");
  	printf("   ####                                         ##                   ##    ##       ##\n");
  	printf("  ##  ##                                        ##                   ##             ##\n");
  	printf(" ##        #####   ## ###    #####    #####     ##      #####    ######  ####     ######\n");
  	printf(" ##       ##   ##  ###  ##  ##       ##   ##    ##     ##   ##  ##   ##    ##       ##\n");
  	printf(" ##       ##   ##  ##   ##   ####    ##   ##    ##     #######  ##   ##    ##       ##\n");
  	printf("  ##  ##  ##   ##  ##   ##      ##   ##   ##    ##     ##       ##   ##    ##       ##\n");
  	printf("   ####    #####   ##   ##  #####     #####    ####     #####    ######  ######      ###\n");
  	printf("\nprototype 1980 naberon v0.0.3          by desnot4000\n");
  	if(strfind(lang,"fr")==0) printf("langage: francais\n");
  	if(strfind(lang,"en")==0) printf("language: english\n");
  	if(strfind(lang,"fr")==0) printf("taper help pour plus d'aide\n");
  	if(strfind(lang,"en")==0) printf("type help for more help\n");
  }
  // fstream openfile(string file,char mode)
  // {
  	// fstream fic;
  	// char* filename;
  	// strcpy(filename,file.c_str());
  	// string tt="";
    // OPENFILENAME ofn;
      // ZeroMemory( &filename, sizeof( filename ) );
      // ZeroMemory( &ofn,      sizeof( ofn ) );
      // ofn.lStructSize  = sizeof( ofn );
      // ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
      // ofn.lpstrFilter  = "Text Files\0*.txt\0Any File\0*.*\0";
      // ofn.lpstrFile    = filename;
      // ofn.nMaxFile     = MAX_PATH;
      // ofn.lpstrTitle   = "Select a File, yo!";
      // ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
    
    // if (GetOpenFileNameA( &ofn ))
    // {
      // tt = filename;
  	// if(mode == 'w')
  		// fic.open(filename,ios::out);
  	// if(mode == 'r')
  		// fic.open(filename,ios::in);
    // }
    
    // return fic;
    
  // }
  void textcolor(int color)
  {
  	string ght;
  	ght = "color " + to_string(color);
  	system(ght.c_str());
  }
  void printTxt(char* txt,int pcolor)
  {
  	textcolor(pcolor);
      puts (txt);
  	textcolor(Color);
  }
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

  string strsub(string a,int debut,int width)
  {
  	return a.substr(debut,width);
  }













































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































