/* 
 * File:   main.cpp
 * Author: sharma
 *
 * Created on 15 March, 2016, 11:16 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;
std::vector<std::string> listpath;
void recursive_listing(char *ptr)
{

        DIR *dp;
        dirent *d;

	if((dp = opendir(ptr)) == NULL)
		perror("opendir");
 int loop=0;
	while((d = readdir(dp)) != NULL)
	{
            
		if(!strcmp(d->d_name,".") || !strcmp(d->d_name,".."))
                {
			continue;
                }
                 string dirpath=string(ptr)+"/"+d->d_name;
		struct stat sb;
               
                if (stat(dirpath.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
                {
//			cout << d->d_name << ":" << endl;
//                        string dirpath=string(ptr)+"/"+d->d_name;
                       // cout<<"dirpath :"<<dirpath<<endl;
			recursive_listing(dirpath.c_str());	
		}
		else
                {
                    if(loop<=11)
                    {
                     string dirpath1=string(ptr)+"/"+d->d_name;
                     listpath.push_back(dirpath1);
                     loop++;
                    }
                    // cout << "File :"<< dirpath1 << endl;
                }
                
	}
       // closedir(ptr);
	return;
}

int main(int argc, char** argv) {

              recursive_listing(argv[1]);
              cout<<"total file siz"<<listpath.size()<<endl;
              for(int i=0;i<listpath.size();i++)
             {
                 int len2=listpath[i].find_last_of("\\/");
                  string dirpath2= listpath[i].substr(0,len2);
                   int len1=listpath[i].find_last_of("\\/");
                  string dirpath= listpath[i].substr(len1+1);
                    int len=dirpath.find_first_of("d");
                  string firstname=dirpath.substr(0,len);
                  string dirpathnew= string("/media/hubcvdev/6646349D46347043/FRGC/FRGC-2.0-dist/faces_12")+"/"+firstname+"/"+dirpath;
                   string dirpathcreate=string("/media/hubcvdev/6646349D46347043/FRGC/FRGC-2.0-dist/faces_12")+"/"+firstname;
                   cout<<"dirpath :"<<dirpath2<<endl;
                           cout<<"firstname :"<<firstname<<endl;
                    cout<<"dirpathcreate :"<<dirpathcreate<<endl;
                   cout<<"dirpathnew :"<<dirpathnew<<endl;
                    cout<<"listpath[i].c_str() :"<<listpath[i].c_str()<<endl;
                  DIR *dp;
                  dirent *d;
                  
	          if((dp = opendir(dirpathcreate.c_str())) == NULL) 
                  {
                   mkdir(dirpathcreate.c_str(),0777); 
                    rename(listpath[i].c_str(),dirpathnew.c_str());
                    cout<<"creating to :"<<dirpathcreate<<endl;
                  }
                  else
                  {
                      rename(listpath[i].c_str(),dirpathnew.c_str());
                       cout<<"copying from"<<listpath[i].c_str()<<" to : "<<dirpathnew<<endl;
                      
                  }
 
                  closedir(dp);
                  
 
//                  cout<<"checking :"<<firstname<<endl;
              }
     
    return 0;
}

