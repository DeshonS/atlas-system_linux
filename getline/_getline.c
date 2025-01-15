#include "_getline.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int fd = fileno(file);
    char *line;
    size_t line_count = 0;

    while ((line = _getline(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
        line_count++;
    }

    printf("Total: %zu lines\n", line_count);

    fclose(file);
    return EXIT_SUCCESS;
}