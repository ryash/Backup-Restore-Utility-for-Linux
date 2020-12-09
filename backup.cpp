#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include<unistd.h>
#include<sys/wait.h>

using namespace std;



int runcmd()
{
  char* argv[100];
  pid_t child_pid,tpid;
  int child_status;
  child_pid = fork();
  if(child_pid == 0) {
    execlp("python3", "python3", "backupclient.py", (char*) NULL);
    printf("Unknown command\n");
    exit(0);
  }
  else {
     do {
       tpid = wait(&child_status);
       if(tpid != child_pid) WIFEXITED(tpid);
     } while(tpid != child_pid);

     return child_status;
  }
}




string exec(string command,map<string,string> &m) {
   char buffer[128];
   string result = "";
   ofstream mapout;
   mapout.open("maplog.txt", std::ios_base::app);     
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   while (!feof(pipe)) {

      if (fgets(buffer, 128, pipe) != NULL)
      {
          string s(buffer);
          size_t found = s.find("\t"); 
          string temp=s.substr(found+1);
          if(m.find(s)==m.end()){
             mapout << s << temp;
              char stream[temp.length()+1];
              strcpy(stream, temp.c_str());
              m[s]=temp;
              result += temp;    
          }
      }
   }
   pclose(pipe);
   return result;
}

int main() {
    map<string,string> m;
    ifstream mapin, config;
    config.open("config");
    mapin.open("maplog.txt");
    string key,val,temp;
    while(getline(mapin, temp)){
       key=temp;
       key.append("\n");
       getline(mapin, temp);
       val=temp;
       m[key]=val;
    }
   vector<string> backupdir;
   
   while(getline(config,temp)){
      
      backupdir.push_back(temp);
   }   
   
   string ls;
   while(1){
      for(int i=0;i<backupdir.size();i++){
         temp="find "+backupdir[i]+" "+ "-name '*' -printf '%TY-%Tm-%Td %TT %Tz\t%p\t%k\n'"; 
         ls = exec(temp,m);
         cout << ls;
         ofstream fout;
         fout.open("out.txt");
         fout<<ls;
         fout.close();
         runcmd();
        
      }
      sleep(10);
      cout<<"Waiting for changes in file to send\n";
   }
   
}