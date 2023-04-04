#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

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

int main(int argc, char *argv[]){
    struct stat file_stat;
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
        scanf(" %c",&c);
        switch (c)
        {
        case 'n':printf("File name:%s\n",argv[i]);break;
        case 'd':printf("The size of the file is %ld\n",file_stat.st_size);break;
        case 'h':printf("The number of hard links is %ld\n",file_stat.st_nlink);break;
        case 'm':printf("The time of the last modification is %d\n",file_stat.st_mtim);break;
        case 'a':gotoformat(file_stat);break;
        case 'l':defineLink(argv[i]);break;
        default:break;
        }
    }
    else if(S_ISLNK(file_stat.st_mode)){
        printf("The file ' %s ' a symbolic link\n",argv[i]);
        char c1;
        printf("\nB)Symbolic link\n-n(file name)\n-d(dim/size)\n -a (acces rights) \n");
        scanf(" %c",&c1);
        switch(c1)
        {
            case 'n':printf("Link name:%s\n",argv[i]);break;
            case 'd':printf("The size of the link is %ld\n", file_stat.st_size);break;
            case 'a':gotoformat(file_stat);break;
            default: break;
        }
    }
    else{
        printf("The %s is not a regular/symbolic file",argv[i]);
    }
    }
    }



    return 0;
}
