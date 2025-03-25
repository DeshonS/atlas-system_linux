#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <gelf.h>
#include <libelf.h>
#include <errno.h>

void print_symbols(const char *filename) {
    int fd;
    Elf *elf;
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    Elf_Data *data;
    size_t shstrndx;

    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "ELF library initialization failed: %s\n", elf_errmsg(-1));
        exit(EXIT_FAILURE);
    }

    if ((fd = open(filename, O_RDONLY, 0)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
        fprintf(stderr, "elf_begin() failed: %s\n", elf_errmsg(-1));
        exit(EXIT_FAILURE);
    }

    if (elf_getshdrstrndx(elf, &shstrndx) != 0) {
        fprintf(stderr, "elf_getshdrstrndx() failed: %s\n", elf_errmsg(-1));
        exit(EXIT_FAILURE);
    }

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            fprintf(stderr, "gelf_getshdr() failed: %s\n", elf_errmsg(-1));
            exit(EXIT_FAILURE);
        }

        if (shdr.sh_type == SHT_SYMTAB || shdr.sh_type == SHT_DYNSYM) {
            data = elf_getdata(scn, NULL);
            int count = shdr.sh_size / shdr.sh_entsize;

            for (int i = 0; i < count; i++) {
                GElf_Sym sym;
                if (gelf_getsym(data, i, &sym) != &sym) {
                    fprintf(stderr, "gelf_getsym() failed: %s\n", elf_errmsg(-1));
                    exit(EXIT_FAILURE);
                }

                printf("%016lx %c %s\n", sym.st_value,
                       GELF_ST_BIND(sym.st_info) == STB_GLOBAL ? 'T' : 't',
                       elf_strptr(elf, shdr.sh_link, sym.st_name));
            }
        }
    }

    elf_end(elf);
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