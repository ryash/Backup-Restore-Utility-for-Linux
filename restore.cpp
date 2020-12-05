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
    execlp("python3", "python3", "restoreclient.py", (char*) NULL);
    
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




int main() {
   
    string ls;
    while(1){
        cout<<"Enter complete file path to restore\n";
        runcmd();
        sleep(2);
        break;
    }
   
}