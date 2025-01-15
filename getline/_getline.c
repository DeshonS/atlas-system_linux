#include "_getline.h"
#include <string.h>

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
        // If buffer is empty, refill it
        if (buffer_pos >= buffer_end)
        {
            buffer_end = read(fd, buffer, READ_SIZE);
            buffer_pos = 0;

            // End of file or error
            if (buffer_end <= 0)
                return (line && line_length > 0) ? line : NULL;
        }

        // Process characters in the buffer
        for (; buffer_pos < buffer_end; buffer_pos++)
        {
            if (buffer[buffer_pos] == '\n') // End of a line
            {
                char *new_line = realloc(line, line_length + 1);
                if (!new_line)
                {
                    free(line);
                    return NULL;
                }
                line = new_line;
                memcpy(line + line_length, buffer, buffer_pos);
                line[line_length] = '\0';
                buffer_pos++; // Move past the newline character
                return line;
            }
        }

        // Add remaining data in buffer to the line
        char *new_line = realloc(line, line_length + (buffer_end - buffer_pos));
        if (!new_line)
        {
            free(line);
            return NULL;
        }
        line = new_line;
        memcpy(line + line_length, buffer + buffer_pos, buffer_end - buffer_pos);
        line_length += buffer_end - buffer_pos;
        buffer_pos = buffer_end;
    }
}
