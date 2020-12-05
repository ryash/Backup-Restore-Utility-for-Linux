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

  //parsecmd(cmd,argv);
  child_pid = fork();
  if(child_pid == 0) {
    /* This is done by the child process. */
    //char *args[]={"python3 client.py",NULL}; 
    execlp("python3", "python3", "backupclient.py", (char*) NULL);
    
    /* If execvp returns, it must have failed. */

    printf("Unknown command\n");
    exit(0);
  }
  else {
     /* This is run by the parent.  Wait for the child
        to terminate. */

     do {
       tpid = wait(&child_status);
       if(tpid != child_pid) WIFEXITED(tpid);
     } while(tpid != child_pid);

     return child_status;
  }
}




string exec(string command,map<string,string> &m) {
   //  for(auto x=m.begin();x!=m.end();x++){
   //       cout<<x->first<<" "<<x->second<<"\n";
   //  }
   char buffer[128];
   string result = "";
   ofstream mapout;
   mapout.open("/home/ryash/Downloads/maplog.txt", std::ios_base::app);     
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   while (!feof(pipe)) {

      if (fgets(buffer, 128, pipe) != NULL)
      {
          string s(buffer);
          //s=s.substr(0, s.length()-1);
          //cout<<s<<"aqwqwqwqwqww";
          size_t found = s.find("\t"); 
          string temp=s.substr(found+1);
          //cout<<temp<<endl;
          //cout<<buffer<<endl;
          if(m.find(s)==m.end()){
             mapout << s << temp;
              char stream[temp.length()+1];
              strcpy(stream, temp.c_str());
              m[s]=temp;
              //fprintf(output,"%s", stream);
              result += temp;    
          }
          
         //cout<< s.substr(found+1,s.length()-1);
          

      }
   }
    // for(auto x=m.begin();x!=m.end();x++){
    //     cout<<x->first<<"\n"<<x->second<<endl;
    // }
   pclose(pipe);
   return result;
}

int main() {
    map<string,string> m;
    ifstream mapin;
    mapin.open("/home/ryash/Downloads/maplog.txt");
    string key,val,temp;
    while(getline(mapin, temp)){
       //cout<<temp<<"\n";
       key=temp;
       key.append("\n");
       getline(mapin, temp);
      // cout<<temp<<"\n";
       val=temp;
       m[key]=val;
    }
   
    string ls;
    while(1){
        ls = exec("find /home/ryash/Desktop -name '*' -printf '%TY-%Tm-%Td %TT %Tz\t%p\n'",m);
        cout << ls;
        ofstream fout;
        fout.open("/home/ryash/Downloads/out.txt");
        fout<<ls;
        fout.close();
        runcmd();
        sleep(10);
        cout<<"Waiting for changes in file to send\n";
    }
   
}