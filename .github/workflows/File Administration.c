#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char filename[20], buffer[100];
    int choice;

    printf("File Administration Program\n");
    printf("1. Create a file\n");
    printf("2. Read a file\n");
    printf("3. Write to a file\n");
    printf("4. Delete a file\n");
    printf("5. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the name of the file: ");
                scanf("%s", filename);

                fp = fopen(filename, "w");
                if (fp == NULL) {
                    printf("File creation failed\n");
                } else {
                    printf("File created successfully\n");
                    fclose(fp);
                }
                break;

            case 2:
                printf("\nEnter the name of the file: ");
                scanf("%s", filename);

                fp = fopen(filename, "r");
                if (fp == NULL) {
                    printf("File does not exist\n");
                } else {
                    printf("Contents of the file:\n");

                    while (fgets(buffer, 100, fp)) {
                        printf("%s", buffer);
                    }

                    fclose(fp);
                }
                break;

            case 3:
                printf("\nEnter the name of the file: ");
                scanf("%s", filename);

                fp = fopen(filename, "a");
                if (fp == NULL) {
                    printf("File does not exist\n");
                } else {
                    printf("\nEnter the text to be written to the file:\n");
                    scanf(" %[^\n]", buffer);

                    fprintf(fp, "%s\n", buffer);
                    fclose(fp);
                    printf("Text written to the file successfully\n");
                }
                break;

            case 4:
                printf("\nEnter the name of the file: ");
                scanf("%s", filename);

                if (remove(filename) == 0) {
                    printf("File deleted successfully\n");
                } else {
                    printf("File deletion failed\n");
                }
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}
