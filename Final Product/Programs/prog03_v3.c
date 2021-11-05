//John Parkhurst
//10.27.21
//Process creation with fork but improved output for neatness
//Was supposed to have execvp call but stuff changes
//Version 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include <fcntl.h>
char **readP(char *commands){
    /*param: commands is a pointer to a string
     * return: an array of strings(the file paths)
     */
    //Array of strings and the space
    char **indFil= calloc(strlen(commands),sizeof(char*));
    char delim[] = " ";
    //Temporary string to hold the phrase
    char *temp = strtok(commands,delim);
    //a
    int count = 0;
    //While the temporary string isnt Null
    //Append to our file list
    while (temp != NULL){
        indFil[count]=temp;
        count++;
        temp = strtok(NULL,delim);
    }
    return indFil;
}
FILE *openF(char* arr){
    //@param: pointer to char array
    //Opens the file
    //return: none
    FILE *fptr;
    //REMEMBER TO USE DOUBLE QUOTES
    fptr = fopen(arr,"r");
    if(fptr ==NULL){
        //Use put to not include null character
        puts("Error While Opening the File");
        fclose(fptr);
        exit(69);
    }else{
        return fptr;
    }
}
void extraCredit(char *comm){
    /* param: nothing
     *  This is for Extra credit 2.8
     *  did not get to fully implement it
     *  Check report for synopsis of this
     * return: nothing
     */
        int pid = fork();
        if(pid==0){
            //Argument list for exevp
            //Fill in Comm to argument list with
            //arglist[i]= strtok(comm,"")
            char* argument_list[] = {"ls","-la", NULL};
            //We set filename = to du_1.out,du_2.out as needed
            //Here is eclog.out for testing purposes

            const char* filename = "eclog.out";
            //Make sure filename not null
            if(filename) {
                //opens file for writing only
                int fd = open(filename, O_WRONLY, 0666);
                //WE open up Pipe with dup2
                //Redirecting all output//errors
                //To the File fd
                dup2(fd, STDOUT_FILENO);
                dup2(fd,STDERR_FILENO);
                //Right here we exec
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
            waitpid(pid,&pid, 1);
            printf("Extra Credit is Done\n");
        }
}
void logFile(char *logName, char *command){
    /* @param: logName is where you what name would you like the log, command is char array of the command
     *
     */
    //I could not figure this part out unfortunately
    FILE *logF;
    logF = fopen(logName, "a");
    if(logF){
        fprintf(logF,"%s\n",command);
    }
    fclose(logF);
}
void execFil(FILE *fptr, char* outP){
    /*@param: Requires a file pointer, string to output path
     * Going to iterate through said file and fork each command to a
     * Separate Process
     * return: Nothing
     */
    char original[255];
    strcpy(original,outP);
    if(fptr ==NULL){
        puts("Error While Opening the File");
        exit(69);
    }else{
        char line[255];
        while(fgets(line,sizeof(line),fptr)){
            //Fork the program child process will execute what we want
            //Then exit and continue along the process
            int id =fork();
            if(id==0){
                FILE *outF;
                //NExt 30 Lines is a mess of string concaction
                strtok(line,"\n");
                //Temporary output file
                char tempL[255];
                //Save the command itself
                char comL[255];
                strcpy(tempL,line);
                strcat(outP,"/");
                //FILE NAME FOR LOG FILE
                char logName[255];
                strcpy(logName,outP);
                strcat(logName,"log.out");
                //putting the command seperate
                strcpy(comL,line);
                strcat(outP,strtok(line," "));
                //Temp file path to set as n+1 if found
                char tempP[255];
                strcpy(tempP,outP);
                strcat(outP,"_1.out");
                //Temporary counters
                int count =1;
                char tempCounter;
                while( access(outP,F_OK) != -1){
                    count++;
                    strcpy(outP,tempP);
                    strcat(outP,"_");
                    tempCounter=count+'0';
                    strcat(outP,&tempCounter);
                    strcat(outP,".out");
                }
                outF = fopen(outP, "w+");
                //If file created Fine then print the command to
                if(outF){
                    //String Concoction to create command >> file
                    strcat(tempL," >> ");
                    strcat(tempL, outP);
                    //output folder
                    system(tempL);
                }
                //log all the Calls
                logFile(logName,comL);
                //Resets the output Path to original
                strcpy(outP,original);
                fclose(outF);
                exit(1);
            }else{
                //Waits for child process
                waitpid(id,&id, 1);
            }
        }
    }
    return;
}
int main(int argc, char *argv[]) {
    //Iterate all commands
    for(int i =2; i <argc; i++){
        char **filPath;
        //readP is excessive; however it was designed for buildandexecute script
        filPath = readP(argv[i]);
        int count=0;
        while(filPath[count] != NULL){
            //temp file and open
            FILE *tFil;
            //Open Said file
            tFil=openF(filPath[count]);
            //Gives this a command File
            execFil(tFil,argv[1]);
            fclose(tFil);
            count++;
        }
        //Free up the string array filpath
        free(filPath);
    }
    //IF YOU WANT TO SEE EXTRA CREDIT RUN
    //UNCOMMENT NEXT LINE
    //extraCredit("ls -la");

    return 0;
}
