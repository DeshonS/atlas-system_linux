#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>

size_t asm_strlen(const char *str);
int asm_strcmp(const char *s1, const char *s2);
char *asm_strchr(const char *s, int c);
char *asm_strstr(const char *haystack, const char *needle);

#endif /* LIBASM_H */
