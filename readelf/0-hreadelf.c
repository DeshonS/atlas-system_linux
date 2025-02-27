#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <arpa/inet.h>

const char* get_os_abi(unsigned char osabi) {
    static char unknown[20];
    switch (osabi) {
        case ELFOSABI_SYSV: return "UNIX - System V";
        case ELFOSABI_HPUX: return "HP-UX";
        case ELFOSABI_NETBSD: return "NetBSD";
        case ELFOSABI_LINUX: return "Linux";
        case ELFOSABI_SOLARIS: return "UNIX - Solaris";
        case ELFOSABI_IRIX: return "IRIX";
        case ELFOSABI_FREEBSD: return "FreeBSD";
        case ELFOSABI_TRU64: return "TRU64";
        case ELFOSABI_ARM: return "ARM architecture";
        case ELFOSABI_STANDALONE: return "Standalone (embedded)";
        default: 
            snprintf(unknown, sizeof(unknown), "<unknown: %x>", osabi);
            return unknown;
    }
}

const char* get_elf_type(uint16_t type) {
    switch (type) {
        case ET_NONE: return "NONE (No file type)";
        case ET_REL: return "REL (Relocatable file)";
        case ET_EXEC: return "EXEC (Executable file)";
        case ET_DYN: return "DYN (Shared object file)";
        case ET_CORE: return "CORE (Core file)";
        default: return "Unknown";
    }
}

const char* get_machine_type(uint16_t machine) {
    switch (machine) {
        case EM_386: return "Intel 80386";
        case EM_X86_64: return "AMD x86-64";
        case EM_ARM: return "ARM";
        case EM_AARCH64: return "ARM AArch64";
        case EM_MIPS: return "MIPS";
        case EM_PPC: return "PowerPC";
        case EM_SPARC: return "Sparc";
        case EM_RISCV: return "RISC-V";
        default: return "Unknown";
    }
}

void print_elf_header(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Elf32_Ehdr ehdr;
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

    printf("\n--- ELF HEADER DETAILS ---\n");
    printf("Type: %s\n", get_elf_type(ntohs(ehdr.e_type)));
    printf("Machine: %s\n", get_machine_type(ntohs(ehdr.e_machine)));
    printf("Entry point: 0x%x\n", ntohl(ehdr.e_entry));
    printf("Program header offset: %u\n", ntohl(ehdr.e_phoff));
    printf("Section header offset: %u\n", ntohl(ehdr.e_shoff));
    printf("Flags: 0x%x\n", ntohl(ehdr.e_flags));
    printf("Header size: %u bytes\n", ntohs(ehdr.e_ehsize));
    printf("Program header entry size: %u bytes\n", ntohs(ehdr.e_phentsize));
    printf("Number of program headers: %u\n", ntohs(ehdr.e_phnum));
    printf("Section header entry size: %u bytes\n", ntohs(ehdr.e_shentsize));
    printf("Number of section headers: %u\n", ntohs(ehdr.e_shnum));
    printf("Section header string table index: %u\n", ntohs(ehdr.e_shstrndx));
    printf("-----------------------------\n\n");
    
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
