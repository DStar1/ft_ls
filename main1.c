// #include <sys/types.h>
// #include <sys/dir.h>
// #include <sys/param.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
 
// #define FALSE 0
// #define TRUE !FALSE
 
// extern  int alphasort(); //Inbuilt sorting function
 
// char pathname[MAXPATHLEN];
 
// void die(char *msg)
// {
//   perror(msg);
//   exit(0);
// }
 
// int file_select(struct direct *entry)
// {
//     if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
//         return (FALSE);
//     else
//         return (TRUE);
// }
 
// int main()
// {
//     int count,i;
//     struct direct **files;
 
//     if(!getcwd(pathname, sizeof(pathname)))
//         die("Error getting pathname\n");
 
//     printf("Current Working Directory = %s\n",pathname);
//     count = scandir(pathname, &files, file_select, alphasort);
 
//     /* If no files found, make a non-selectable menu item */
//     if(count <= 0)
//       die("No files in this directory\n");
     
//     printf("Number of files = %d\n",count);
//     for (i=1; i<count+1; ++i)
//         printf("%s  ",files[i-1]->d_name);
//     printf("\n"); /* flush buffer */
// }

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "include/ft_ls.h"

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

int main(void) {
    listdir(".", 0);
    return 0;
}