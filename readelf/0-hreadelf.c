#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void print_elf_header(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Elf64_Ehdr ehdr;
    if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr)) {
        perror("Error reading ELF header");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (ehdr.e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr.e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr.e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "Not an ELF file\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", ehdr.e_ident[i]);
    }
    printf("\n");
    printf("  Class:                             %s\n", ehdr.e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "ELF32");
    printf("  Data:                              %s\n", ehdr.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
    printf("  Version:                           %d (current)\n", ehdr.e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %d\n", ehdr.e_ident[EI_OSABI]);
    printf("  ABI Version:                       %d\n", ehdr.e_ident[EI_ABIVERSION]);
    printf("  Type:                              %d\n", ehdr.e_type);
    printf("  Machine:                           %d\n", ehdr.e_machine);
    printf("  Version:                           0x%x\n", ehdr.e_version);
    printf("  Entry point address:               0x%lx\n", ehdr.e_entry);
    printf("  Start of program headers:          %ld (bytes into file)\n", ehdr.e_phoff);
    printf("  Start of section headers:          %ld (bytes into file)\n", ehdr.e_shoff);
    printf("  Flags:                             0x%x\n", ehdr.e_flags);
    printf("  Size of this header:               %d (bytes)\n", ehdr.e_ehsize);
    printf("  Size of program headers:           %d (bytes)\n", ehdr.e_phentsize);
    printf("  Number of program headers:         %d\n", ehdr.e_phnum);
    printf("  Size of section headers:           %d (bytes)\n", ehdr.e_shentsize);
    printf("  Number of section headers:         %d\n", ehdr.e_shnum);
    printf("  Section header string table index: %d\n", ehdr.e_shstrndx);
    
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    print_elf_header(argv[1]);
    return EXIT_SUCCESS;
}