#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;
    char str[100];
    char status[20];

    // Create both pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        printf("Pipe creation failed.\n");
        return 1;
    }

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed.\n");
        return 1;
    }

    // Parent Process
    if (pid > 0)
    {
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        printf("Parent: Enter a string: ");
        scanf("%s", str);

        // Send string to child
        write(pipe1[1], str, sizeof(str));

        close(pipe1[1]);

        // Read validation status from child
        read(pipe2[0], status, sizeof(status));

        printf("\nParent: The entered string is %s.\n", status);

        if (strcmp(status, "VALID") == 0)
            printf("Password satisfies all conditions.\n");
        else
            printf("Password does NOT satisfy all conditions.\n");

        close(pipe2[0]);
    }

    // Child Process
    else
    {
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2

        read(pipe1[0], str, sizeof(str));

        int hasDigit = 0;
        int hasSpecial = 0;
        int len = strlen(str);
	int i;
        for ( i = 0; str[i] != '\0'; i++)
        {
            if (isdigit(str[i]))
                hasDigit = 1;

            if (!isalnum(str[i]))
                hasSpecial = 1;
        }

        if (len > 7 && hasDigit && hasSpecial)
            strcpy(status, "VALID");
        else
            strcpy(status, "INVALID");

        // Send result to parent
        write(pipe2[1], status, sizeof(status));

        close(pipe1[0]);
        close(pipe2[1]);
    }

    return 0;
}
