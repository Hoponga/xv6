#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main (int argc, char *argv[]) {
    // create pipe 
    int a[2]; 

    int b[2]; 
    pipe(a);     
    uint mynum = 2; 
    uint buf[1]; 
    buf[0] = 2; 
    int hasChild = 0; 
    printf("prime %d\n", mynum); 
    uint limit = 35; 
    int notDone = 1; 


    while (notDone) {
        //printf("%d", mynum); 

        int attempt; 
        if (mynum != 2) {
            attempt = read(a[0], buf, sizeof(buf));
           // if (mynum == 31) {
                //printf("%d\n", attempt); 
            //}

            if (attempt <= 0) {
                close(a[0]); 
                close(b[0]); 
                close(a[1]); 
                close(b[1]); 
                if (hasChild) {
                    wait(0); 

                }
                notDone = 0; 
                exit(0); 
            }
            if (attempt <= 0) {
                continue; 
            } 
            //printf("%dto%d\n", buf[0], mynum); 

        } else if (mynum == 2 && buf[0] < limit) {
            buf[0]++; 

        }
        if (buf[0] >= limit) {
            //printf("%d\n", buf[0]); 
            close(a[0]); 
            close(a[1]); 
            close(b[0]); 
            close(b[1]); 
            notDone = 0; 
            wait(0); 
            exit(0); 
        }
        if (buf[0] % mynum == 0) {
            continue; 
        }

        if (hasChild) {

            write(b[1], buf, sizeof(buf)); 
        } else {
                
                pipe(b);

                int process = fork(); 
                if (process == 0) {
                    hasChild = 0; 
                    a[0] = dup(b[0]); 
                    a[1] = dup(b[1]); 
                    close(b[0]); 
                 
                    close(b[1]);
                    close(a[1]); 
                    mynum = read(a[0], buf, sizeof(buf)); 
                    mynum = buf[0]; 

                    printf("prime %d\n", buf[0]); 

                } else {
                    close(b[0]); 
                    write(b[1], buf, sizeof(buf)); 

                    hasChild = 1; 
                }
        }
    }
    exit(0); 

    
}