#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>

void process_elf(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return;
    }

    struct stat st;
    if (fstat(fd, &st) < 0)
    {
        perror("fstat");
        close(fd);
        return;
    }

    void *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return;
    }

    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
    if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr->e_ident[EI_MAG3] != ELFMAG3)
        {
        fprintf(stderr, "%s: Not a valid ELF file\n", filename);
        munmap(map, st.st_size);
        close(fd);
        return;
    }
    munmap(map, st.st_size);
    close(fd);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s [objfile ...]\n", argv[0]);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++)
    {
        process_elf(argv[i]);
    }
    return EXIT_SUCCESS;
}