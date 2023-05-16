#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main (int argc, char *argv[]) {
    // create pipe 
    int parenttochild[2]; 
    int childtoparent[2]; 
    pipe(parenttochild); 
    pipe(childtoparent); 

    int buf[1]; 

    if (fork() == 0) {
        int pid = getpid(); 

        // child process 
        close(childtoparent[0]); 
        int bytes = read(parenttochild[0], buf, sizeof(buf)); 
        if (bytes == 1) {

            printf("%d: received ping\n", pid); 
        }
        write(childtoparent[1], "1", 1); 
        close(childtoparent[1]); 
        exit(0); 


    } else {
        int pid = getpid(); 

        close(parenttochild[0]); 
        
        write(parenttochild[1], "1", 1); 
        wait(0); 
        int bytes = read(childtoparent[0], buf, sizeof(buf));
        if (bytes == 1) {
            printf("%d: received pong\n", pid); 


        } 
        close(parenttochild[1]); 


    }
    exit(0); 


    
}