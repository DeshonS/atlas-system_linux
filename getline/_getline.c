#include "_getline.h"

char *_getline(const int fd)
{
    static char buffer[READ_SIZE];
    static size_t buffer_pos = 0, buffer_end = 0;
    char *line = NULL;
    size_t line_length = 0;

    if (fd < 0)
        return NULL;

    while (1)
    {
        if (buffer_pos >= buffer_end)
        {
            buffer_end = read(fd, buffer, READ_SIZE);
            buffer_pos = 0;
            if (buffer_end <= 0) // EOF or error
                return NULL;
        }

        for (; buffer_pos < buffer_end; buffer_pos++)
        {
            if (buffer[buffer_pos] == '\n')
            {
                char *new_line = realloc(line, line_length + buffer_pos + 1);
                if (!new_line)
                    return NULL;

                line = new_line;
                memcpy(line + line_length, buffer, buffer_pos);
                line[line_length + buffer_pos] = '\0';
                buffer_pos++;
                return line;
            }
        }

        char *new_line = realloc(line, line_length + buffer_end - buffer_pos);
        if (!new_line)
            return NULL;

        line = new_line;
        memcpy(line + line_length, buffer + buffer_pos, buffer_end - buffer_pos);
        line_length += buffer_end - buffer_pos;
        buffer_pos = buffer_end;
    }
}