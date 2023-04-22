#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    int fd[2];
    /*
    file descriptor
    fd[0] -> read
    fd[1] -> write
    */

   if(pipe(fd) == -1){
        std::cout << "error when create pipe" << "\n";
        return -1;
   }

   pid_t pid = fork();
   if(pid < 0){
        std::cout << "error when create fork()" << "\n";
        return -1;
   }

   else{
    //parent process
    if(pid > 0){
        //close write process
        close(fd[1]);
        int resp;
        if(read(fd[0], &resp, sizeof(int)) == -1){
            std::cout << "error while read process in pipe\n";
            return -1;
        }
        std::cout << "i'm parent process" << "\n";
        std::cout << "message for child process: " << resp << "\n";
        //close read process
        waitpid(pid, NULL, 0);
        close(fd[0]);
        std::cout << "finishing parent process";
    }
    //child process
    if(pid == 0){
        int message;
        //close for read process
        close(fd[0]);
        std::cout << "i'm child process" << "\n";
        std::cout << "input for parent process: ";
        std::cin >> message;
        if(write(fd[1], &message, sizeof(int)) == -1){
            std::cout << "error while write process in pipe\n";
            return -1;
        }
        //close write process
        close(fd[1]);
        std::cout << "finishing child process" << "\n";
    }
   }
}