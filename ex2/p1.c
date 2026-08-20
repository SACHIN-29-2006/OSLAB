#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    int fd[2];
    pid_t pid;
    int num;

    // Create pipe
    if (pipe(fd) == -1)
    {
        printf("Pipe creation failed\n");
        return 1;
    }

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    // Child Process
    if (pid == 0)
    {
        close(fd[0]);   // Close read end

        printf("Child: Enter a number: ");
        scanf("%d", &num);

        // Write number into pipe
        write(fd[1], &num, sizeof(num));

        close(fd[1]);
    }

    // Parent Process
    else
    {
        close(fd[1]);   // Close write end

        // Read number from pipe
        read(fd[0], &num, sizeof(num));

        close(fd[0]);

        printf("Parent: Received number = %d\n", num);

        // Check whether power of 3
        if (num < 1)
        {
            printf("%d is NOT a power of 3.\n", num);
        }
        else
        {
            int temp = num;

            while (temp % 3 == 0)
            {
                temp = temp / 3;
            }

            if (temp == 1)
                printf("%d is a power of 3.\n", num);
            else
                printf("%d is NOT a power of 3.\n", num);
        }
    }

    return 0;
}
