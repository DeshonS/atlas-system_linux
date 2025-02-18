#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int main()
{
    DIR *dir;
    struct dirent* dirent;
    dir = opendir("./");
    while ((dirent = readdir(dir)) != NULL)
    {
        if (((strcmp(dirent->d_name, "..") != 0) && (strcmp(dirent->d_name, ".") != 0)))
        {
            printf("%s\n", dirent->d_name);
        }
    }
    closedir(dir);
    return 0;
}