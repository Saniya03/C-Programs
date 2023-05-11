#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    char *source, *destination;
    DIR *dir;
    struct dirent *entry;
    struct stat filestat;
    int choice;

    if(argc != 3) {
        printf("Usage: %s source destination\n", argv[0]);
        exit(1);
    }

    source = argv[1];
    destination = argv[2];

    printf("Please select an option:\n");
    printf("1. Copy a file\n");
    printf("2. Move a file\n");
    printf("3. List directory contents\n");
    printf("4. Display file permissions\n");
    printf("5. Change file permissions\n");

    scanf("%d", &choice);

    switch(choice) {

        case 1:
            // Copy a file
            printf("Copying %s to %s...\n", source, destination);
            FILE *fptr1, *fptr2;
            char c;
            fptr1 = fopen(source, "r");
            fptr2 = fopen(destination, "w");
            while ((c = fgetc(fptr1)) != EOF) {
                fputc(c, fptr2);
            }
            printf("File copied successfully.\n");
            fclose(fptr1);
            fclose(fptr2);
            break;

        case 2:
            // Move a file
            printf("Moving %s to %s...\n", source, destination);
            if(rename(source, destination) == 0) {
                printf("File moved successfully.\n");
            } else {
                printf("Error moving file.\n");
            }
            break;

        case 3:
            // List directory contents
            printf("Listing contents of directory %s:\n", source);
            dir = opendir(source);
            while((entry = readdir(dir)) != NULL) {
                printf("%s\n", entry->d_name);
            }
            closedir(dir);
            break;

        case 4:
            // Display file permissions
            if(stat(source, &filestat) < 0) {
                printf("Error getting file status.\n");
                exit(1);
            }
            printf("File %s permissions:\n", source);
            printf((S_ISDIR(filestat.st_mode)) ? "d" : "-");
            printf((filestat.st_mode & S_IRUSR) ? "r" : "-");
            printf((filestat.st_mode & S_IWUSR) ? "w" : "-");
            printf((filestat.st_mode & S_IXUSR) ? "x" : "-");
            printf((filestat.st_mode & S_IRGRP) ? "r" : "-");
            printf((filestat.st_mode & S_IWGRP) ? "w" : "-");
            printf((filestat.st_mode & S_IXGRP) ? "x" : "-");
            printf((filestat.st_mode & S_IROTH) ? "r" : "-");
            printf((filestat.st_mode & S_IWOTH) ? "w" : "-");
            printf((filestat.st_mode & S_IXOTH) ? "x" : "-");
            printf("\n");
            break;

        case 5:
            // Change file permissions
            printf("Changing file %s permissions...\n", source);
            if(chmod(source, S_IRUSR|S_IWUSR|S_IRGRP|S_I
