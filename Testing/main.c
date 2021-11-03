#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void extracredit(){
    /* param: nothing
     *  This is for Extra credit 2.8
     *  did not get to fully implement it
     *  Check report for synopsis of this
     * return: nothing
     */
    for(int k =0; k<3;k++){
        //Fork
        int pid = fork();
        if(pid==0){
            //Argument list for exevp
            char* argument_list[] = {"ls","-la", NULL};
            //We set filename = to du_1.out,du_2.out as needed
            //Here islog.out for testing purposes
            const char* filename = "log.out";
            //Make sure filename not null
            if(filename) {
                //opens file for writing only
                int fd = open(filename, O_WRONLY, 0666);
                //This is the magic

                dup2(fd, STDOUT_FILENO);
                dup2(fd,STDERR_FILENO);
                printf("My Command Output\n");
                execvp(argument_list[0],argument_list);
                close(fd);
                printf("ONLY IF ERROR\n");
                printf("CHECK EXEC PARAMATERS\n");
                exit(-23);
            }else{
                printf("ERROR OPENING LOG FILE\n");
                exit(-23);
            }
        }else{
            wait(NULL);
            printf("Done\n");
        }

    }
}
int main() {
    exec();
    return 0;
}
