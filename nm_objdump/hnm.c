#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <elf.h>

void print_symbols(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }

    Elf64_Ehdr ehdr;
    read(fd, &ehdr, sizeof(ehdr));

    lseek(fd, ehdr.e_shoff, SEEK_SET);
    Elf64_Shdr shdrs[ehdr.e_shnum];
    read(fd, shdrs, ehdr.e_shnum * sizeof(Elf64_Shdr));

    char *shstrtab;
    lseek(fd, shdrs[ehdr.e_shstrndx].sh_offset, SEEK_SET);
    shstrtab = malloc(shdrs[ehdr.e_shstrndx].sh_size);
    read(fd, shstrtab, shdrs[ehdr.e_shstrndx].sh_size);

    for (int i = 0; i < ehdr.e_shnum; i++) {
        if (shdrs[i].sh_type == SHT_SYMTAB || shdrs[i].sh_type == SHT_DYNSYM) {
            Elf64_Sym *symbols = malloc(shdrs[i].sh_size);
            lseek(fd, shdrs[i].sh_offset, SEEK_SET);
            read(fd, symbols, shdrs[i].sh_size);
            int num_symbols = shdrs[i].sh_size / sizeof(Elf64_Sym);

            char *strtab;
            lseek(fd, shdrs[shdrs[i].sh_link].sh_offset, SEEK_SET);
            strtab = malloc(shdrs[shdrs[i].sh_link].sh_size);
            read(fd, strtab, shdrs[shdrs[i].sh_link].sh_size);

            for (int j = 0; j < num_symbols; j++) {
                printf("%016lx %c %s\n", symbols[j].st_value,
                       (ELF64_ST_BIND(symbols[j].st_info) == STB_GLOBAL) ? 'T' : 't',
                       &strtab[symbols[j].st_name]);
            }
            free(symbols);
            free(strtab);
        }
    }

    free(shstrtab);
    close(fd);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [objfile ...]\n", argv[0]);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++) {
        print_symbols(argv[i]);
    }
    return EXIT_SUCCESS;
}
