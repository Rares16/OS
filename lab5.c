#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
void gotoformat(struct stat file){
    printf("USER:\n");
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
                if(file.st_mode & S_IWUSR )
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
                if(file.st_mode & S_IWGRP )
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
                if(file.st_mode &   S_IWOTH )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode & S_IXOTH )
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

void getLinksize(char* file){
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
bool check_c_files_regularfile(char* file_name){
    int len = strlen(file_name);
   
            if(strcmp(file_name+len -2,".c") == 0)
                return true;
    return false;

}


int main(int argc, char *argv[]){
    struct stat file_stat;
    pid_t pid_switch, process_forcfile;
    if(argc < 2 ){
        printf("Not enough arguments");
        return EXIT_FAILURE;
    }else{
    for( int  i = 1; i < argc ;i++){
    lstat(argv[i],&file_stat);
    if(S_ISREG(file_stat.st_mode))
    {
        char c;
        printf("The file  ' %s ' is a regular file\n",argv[i]);
        printf("\nA) Regular file\n -n (file name) \n -d (dim/size) \n -h (number of hard links \n -m (time of last modif) \n -a (acces rights) \n -l (create a symbolic link)\n");
        
        if(check_c_files_regularfile(argv[i]) == 1){
        process_forcfile = fork();
        if(process_forcfile< 0 ){
            perror("Process for regular file didn t start");
        }else if( process_forcfile== 0){
            execlp("./script.sh","./script.sh",argv[i],NULL);
             exit(EXIT_FAILURE);
        }
        }
       
        scanf(" %c",&c);
        pid_switch = fork();
        if(pid_switch < 0){
            perror("Didn t start");
        }else if(pid_switch == 0){
        switch (c)
        {
        case 'n':printf("File name:%s\n",argv[i]);break;
        case 'd':printf("The size of the file is %ld\n",file_stat.st_size);break;
        case 'h':printf("The number of hard links is %ld\n",file_stat.st_nlink);break;
        case 'm':printf("The time of the last modification is %lld\n",file_stat.st_mtim);break;
        case 'a':gotoformat(file_stat);break;
        case 'l':defineLink(argv[i]);break;
        default:fflush(stdin);
            printf("Not a case for a regular file");
            break;
        }
        exit(EXIT_FAILURE);
        }
    }
    else if(S_ISLNK(file_stat.st_mode)){
        printf("The file ' %s ' a symbolic link\n",argv[i]);
        char c1;
        printf("\nB)Link\n-n Link name \n-l delete link \n-d Size of link \n-z size of target \n-a acces rights \n");
        scanf(" %c",&c1);
        switch(c1)
        {
            case 'n':printf("Link name:%s\n",argv[i]);break;
            case 'l':unlink(argv[i]);
                    printf("The link was deleted\n");break;
            case 'd':printf("The size of the link is %ld\n", file_stat.st_size);break;
            case 'z':getLinksize(argv[i]);break;
            case 'a':gotoformat(file_stat);break;
            default: break;
        }
    }
    else if(S_ISDIR(file_stat.st_mode)){
        printf("The file ' %s ' a directory\n",argv[i]);
        char c2;
        printf("\nC)Directory\n-n(file name)\n-d(dim/size)\n-a (acces rights) \n-c (total number of files with the .c extension)\n");
        scanf(" %c",&c2);
        switch(c2)
        {
            case 'n':printf("Directory name:%s\n",argv[i]);break;
            case 'd':printf("The size of the directory is %ld\n", file_stat.st_size);break;
            case 'a':gotoformat(file_stat);break;
            case 'c':check_c_files(argv[i]);break;
            default:break;
        }
    }
    else{
        printf("The %s is not a regular/symbolic file",argv[i]);
    }
    }
    }



    return 0;
}
