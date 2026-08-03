#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static double elapsed_seconds(const struct timeval *start,
                              const struct timeval *end)
{
    return (double)(end->tv_sec - start->tv_sec) +
           (double)(end->tv_usec - start->tv_usec) / 1000000.0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char shared_name[64];
    snprintf(shared_name, sizeof(shared_name), "/os-coursework-timer-%ld",
             (long)getpid());

    int shared_fd = shm_open(shared_name, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (shared_fd == -1)
    {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    if (ftruncate(shared_fd, sizeof(struct timeval)) == -1)
    {
        perror("ftruncate");
        close(shared_fd);
        shm_unlink(shared_name);
        return EXIT_FAILURE;
    }

    struct timeval *start = mmap(NULL, sizeof(*start), PROT_READ | PROT_WRITE,
                                 MAP_SHARED, shared_fd, 0);
    close(shared_fd);

    if (start == MAP_FAILED)
    {
        perror("mmap");
        shm_unlink(shared_name);
        return EXIT_FAILURE;
    }

    /* The mapping survives unlinking, but no stale shared-memory name remains. */
    shm_unlink(shared_name);

    pid_t child = fork();
    if (child == -1)
    {
        perror("fork");
        munmap(start, sizeof(*start));
        return EXIT_FAILURE;
    }

    if (child == 0)
    {
        gettimeofday(start, NULL);
        execvp(argv[1], &argv[1]);
        perror("execvp");
        _exit(127);
    }

    int status;
    if (waitpid(child, &status, 0) == -1)
    {
        perror("waitpid");
        munmap(start, sizeof(*start));
        return EXIT_FAILURE;
    }

    struct timeval end;
    gettimeofday(&end, NULL);
    printf("Elapsed time: %.6f seconds\n", elapsed_seconds(start, &end));

    munmap(start, sizeof(*start));

    if (!WIFEXITED(status))
    {
        fprintf(stderr, "Command terminated abnormally\n");
        return EXIT_FAILURE;
    }

    return WEXITSTATUS(status);
}
