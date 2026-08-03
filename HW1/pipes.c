#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // check if usr provided command as arg
    if (argc < 2)
    {
        fprintf(stderr, "Usage: ./time <command>\n");
        exit(1);
    }

    int pipefd[2];
    struct timeval start_time, end_time;
    // create pipe for IPC
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    // Fork child process to execvp specified command
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    { // Child process
        close(pipefd[0]);

        // record starting time using gettimeofday()
        gettimeofday(&start_time, NULL);
        // write starting time to write end of pipe
        if (write(pipefd[1], &start_time, sizeof(struct timeval)) == -1)
        {
            perror("write");
            exit(1);
        }

        close(pipefd[1]);

        // execvp command line arg provided
        if (execvp(argv[1], &argv[1]) == -1)
        {
            perror("execvp");
            exit(1);
        }
    }
    else
    { // Parent Process
        int status;
        close(pipefd[1]);

        // receive the child's start time
        if (read(pipefd[0], &start_time, sizeof(start_time)) != sizeof(start_time))
        {
            perror("read");
            exit(1);
        }
        close(pipefd[0]);

        // wait for child process to terminate and record the end time
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            exit(1);
        }
        gettimeofday(&end_time, NULL);

        if (WIFEXITED(status))
        {
            // calculate elapsed time and print it
            double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
            printf("Elapsed time: %f\n", elapsed_time);
        }
        else
        {
            // print error message if child process terminated abnormally
            fprintf(stderr, "Child process terminated abnormally\n");
            exit(1);
        }
    }

    return 0;
}
