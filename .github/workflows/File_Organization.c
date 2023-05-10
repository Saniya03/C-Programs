#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file1, *file2, *file3;
    char ch;

    // Open file1 in read mode
    file1 = fopen("file1.txt", "r");
    if (file1 == NULL) {
        printf("Error opening file1.txt\n");
        exit(1);
    }

    // Open file2 in write mode
    file2 = fopen("file2.txt", "w");
    if (file2 == NULL) {
        printf("Error opening file2.txt\n");
        exit(1);
    }

    // Copy the contents of file1 to file2
    while ((ch = fgetc(file1)) != EOF) {
        fputc(ch, file2);
    }

    // Close file1 and file2
    fclose(file1);
    fclose(file2);

    // Open file2 in read mode
    file2 = fopen("file2.txt", "r");
    if (file2 == NULL) {
        printf("Error opening file2.txt\n");
        exit(1);
    }

    // Open file3 in write mode
    file3 = fopen("file3.txt", "w");
    if (file3 == NULL) {
        printf("Error opening file3.txt\n");
        exit(1);
    }

    // Copy the contents of file2 to file3, but in reverse order
    fseek(file2, -1, SEEK_END); // Move file pointer to the end of the file
    while (ftell(file2) > 0) { // Loop until file pointer is at the beginning of the file
        ch = fgetc(file2);
        fputc(ch, file3);
        fseek(file2, -2, SEEK_CUR); // Move file pointer to the previous character
    }
    ch = fgetc(file2); // Copy the first character
    fputc(ch, file3);

    // Close file2 and file3
    fclose(file2);
    fclose(file3);

    printf("File organization complete.\n");

    return 0;
}
