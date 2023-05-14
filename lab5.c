#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h> 
#include <sys/wait.h>

int counter =0;
void getAccessRights(struct stat file){
    printf("USER:\n");				//updated the access function
                if(file.st_mode & S_IRUSR )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode & S_IWUSR )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode & S_IXUSR )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
    printf("\nGROUP:\n");
                if(file.st_mode & S_IRGRP )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode & S_IWGRP )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode & S_IXGRP )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
    printf("\nOTHERS:\n");
                if(file.st_mode &  S_IROTH)
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode &   S_IWOTH)
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode & S_IXOTH)
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
}

void defineLink(char a[])
{
    printf("Name of the link you want to create:");
    char str[20];
    scanf(" %s", str);
    symlink(a,str);
}

void getLinkSize(char* file){
    char buffer[1024];
    readlink(file,buffer,sizeof(buffer)-1);
    struct stat Target;
    lstat(buffer,&Target);
    printf("The link size of %s is %ld\n ",file,Target.st_size);
}

void check_c_files(char* dir_name){
    DIR *dir;
    struct dirent *ent;
    int count = 0;
    int len;
    dir = opendir(dir_name);
    if(dir!=NULL )
    {
        while((ent = readdir(dir)) !=NULL){
            len = strlen(ent->d_name);
            if(strcmp(ent->d_name+len -2,".c") == 0)
                count++;

        }
        closedir(dir);
    }else{
        printf("Error opening dir\n");
    }
    printf("The number of c files is %d\n",count);

}
bool check_c_files_regular_file(char* file_name){
    int len = strlen(file_name);
   
    if(strcmp(file_name+len -2,".c") == 0)
    {
          return true;
    }
    return false;

}

void getScore(int erorrs,int warnings){
    
   if(erorrs == 0 && warnings == 0){
    	printf("The score for the file is 10\n");
   }
   else if(erorrs >= 1 && warnings!=0){
    	printf("The score for the file is 1\n");
   }
   if(erorrs == 0 && warnings >= 10){
    	printf("The score for the file is 2\n");
   }
   if(erorrs == 0 && warnings <=10)
   {
    	int score;
    	score = 2+8*((10-warnings)/10);
    	printf("The score for the file is %d\n",score);
   }
    
}

int main(int argc, char *argv[]){
    struct stat file_stat;
    
    if(argc < 2 ){
        printf("Not enough arguments\n");
        return EXIT_FAILURE;
    }else
    {
        for( int  i = 1; i < argc ;i++){
            
            lstat(argv[i],&file_stat);
            
            int pid = fork();
            counter++;
            
            if (pid == -1)
            { 
            	perror("Process not created");
            }
            else if(pid == 0)
            { 
            
            if(S_ISREG(file_stat.st_mode))
            {
            char c;
            struct tm *time = localtime(&file_stat.st_mtime);
            
            
            printf("The file  ' %s ' is a regular file\n",argv[i]);
            printf("\nA) Regular file\n -n (file name) \n -d (dim/size) \n -h (number of hard links \n -m (time of last modif) \n -a (acces rights) \n -l (create a symbolic link)\n");
        
            scanf(" %c",&c);
            
        
        switch (c)
        {
            case 'n':printf("File name:%s\n",argv[i]);break;
            case 'd':printf("The size of the file is %ld\n",file_stat.st_size);break;
            case 'h':printf("The number of hard links is %ld\n",file_stat.st_nlink);break;
            case 'm':printf("The file was modified %d minutes and %d seconds ago", time->tm_min,time->tm_sec);break;
            case 'a':getAccessRights(file_stat);break;
            case 'l':defineLink(argv[i]);break;
            default:fflush(stdin);
                printf("Invalid option");
                break;
        }
        exit(EXIT_FAILURE);
        }
    
        else if(S_ISLNK(file_stat.st_mode)){
            printf("The file ' %s ' a symbolic link\n",argv[i]);
            char c;
            printf("\nB)Link\n-n Link name \n-l delete link \n-d Size of link \n-z size of target \n-a acces rights \n");
            scanf(" %c",&c);
            switch(c)
            {
                case 'n':printf("The name of the link is %s\n",argv[i]);break;
                case 'l':unlink(argv[i]);
                        printf("The link was deleted\n");break;
                case 'd':printf("The size of the link is %ld\n", file_stat.st_size);break;
                case 'z':getLinkSize(argv[i]);break;
                case 'a':getAccessRights(file_stat);break;
                default:
                	printf("Invalid option");
                	break;
            }
        }
        else if(S_ISDIR(file_stat.st_mode))
        {
            printf("The file ' %s ' a directory\n",argv[i]);
            char c;
            printf("\nC)Directory\n-n(file name)\n-d(dim/size)\n-a (acces rights) \n-c (total number of files with the .c extension)\n");
            scanf(" %c",&c);
            switch(c)
            {
                case 'n':printf("Directory name:%s\n",argv[i]);break;
                case 'd':printf("The size of the directory is %ld\n", file_stat.st_size);break;
                case 'a':getAccessRights(file_stat);break;
                case 'c':check_c_files(argv[i]);break;
                default:
                	printf("Invalid option");
                	break;
            }
        }
        else
        {
            printf("The %s is not a regular/symbolic file",argv[i]);
        }
        
    
    exit(0);
    }
    
    
    
    
    int pipefd[2];
    
    if(S_ISREG(file_stat.st_mode)){
        if(pipe(pipefd) == -1){
            perror("Error with pipe\n");
            exit(EXIT_FAILURE);
        }
    
      int pid = fork();counter++;
      int warnings=0,erorrs=0;
      
               if(pid < 0){
                    perror("Didn t start\n");
               }else if(pid == 0){
               if(check_c_files_regular_file(argv[i] ) == 1){
                
                    close(pipefd[0]);

                    dup2(pipefd[1], STDOUT_FILENO);
                    execlp("./script.sh","./script.sh",argv[i],NULL);

                }else{  
                    
                        
                        execlp("wc","wc","-l",argv[i],NULL);
                        exit(0);

                    }
                exit(0);
            	}else{
                
                close(pipefd[1]);
                

                FILE * fin = fdopen(pipefd[0],"r");

                if(fin == NULL)
                {
                    perror("Couldn't open the file for the pipe");
                    exit(EXIT_FAILURE);
                }

                fscanf(fin,"%d",&warnings);
                fscanf(fin,"%d", &erorrs);

                fclose(fin);
                close(pipefd[0]);
                if(check_c_files_regular_file(argv[i] ) == 1){
                getScore(warnings,erorrs);
                
                }
           
                 
                }
    		}
   	       if(S_ISDIR(file_stat.st_mode)){
               printf("This is a directory\n");
               int pid =fork();counter++;
               if(pid<0)
               {
               	perror("Procces fail.");
               	
               }else if(pid==0){
	       execlp("./createFileInDirectory.sh","./createFileInDirectory.sh",argv[i],NULL);
	       exit(0);
	       }
	       
    
               }
               else if(S_ISLNK(file_stat.st_mode))
               {int pid =fork();counter++;
               if(pid<0)
               {
               	perror("Procces fail.");
               	
               }else if(pid==0){
	       		printf("This is a symbolic link\n");
               		if(execlp("chmod","chmod ","760",argv[i],NULL) == -1)
               		{
               			perror("Access rights modification didn't work\n");
               		}
	       exit(0);
	       }
               
               		
               }
               
               
               
               for(int i=0;i<counter;i++){
               int status;

                wait(&status);
                }
                }
                }
                

              	


    return 0;
}
