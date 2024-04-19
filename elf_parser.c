///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  sre_lab6_readelf-lyons811 - EE 491F - Spr 2024
///
/// @file elf_parser.c
/// @version 1.0
///
/// @author Lyon Singleton <lyonws@hawaii.edu>
/// @date   19_Apr_2024
///////////////////////////////////////////////////////////////////////////////
#include "elf_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Read the ELF header from the file
void elf_read_header(const char* filename, ElfHeader64* header) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    if (fread(header, sizeof(ElfHeader64), 1, file) != 1) {
        perror("Error reading file");
        exit(1);
    }
    fclose(file);
}
// Read the section header from the file
void elf_read_section_header(const char* filename, uint64_t offset, ElfSectionHeader64* header) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    if (fseek(file, offset, SEEK_SET) != 0) {
        perror("Error seeking file");
        exit(1);
    }
    if (fread(header, sizeof(ElfSectionHeader64), 1, file) != 1) {
        perror("Error reading file");
        exit(1);
    }
    fclose(file);
}

// Print the ELF header
void elf_print_header(const ElfHeader64* header) {
    printf("ELF Header:\n");
    printf("  Type: %d\n", header->e_type);
    printf("  Machine: %d\n", header->e_machine);
    printf("  Version: %d\n", header->e_version);
    printf("  Entry point address: %llu\n", header->e_entry);
    printf("  Program header offset: %llu\n", header->e_phoff);
    printf("  Section header offset: %llu\n", header->e_shoff);
    printf("  Flags: %d\n", header->e_flags);
    printf("  ELF header size: %d\n", header->e_ehsize);
    printf("  Program header entry size: %d\n", header->e_phentsize);
    printf("  Number of program header entries: %d\n", header->e_phnum);
    printf("  Section header entry size: %d\n", header->e_shentsize);
    printf("  Number of section header entries: %d\n", header->e_shnum);
    printf("  Section string table index: %d\n", header->e_shstrndx);
}

// Print the section header
void elf_print_section_header(const ElfSectionHeader64* header) {
    printf("Section Header:\n");
    printf("  Name: %d\n", header->sec_name);
    printf("  Type: %d\n", header->sec_type);
    printf("  Flags: %llu\n", header->sec_flags);
    printf("  Address: %llu\n", header->sec_addr);
    printf("  Offset: %llu\n", header->sec_offset);
    printf("  Size: %llu\n", header->sec_size);
    printf("  Link: %d\n", header->sec_link);
    printf("  Info: %d\n", header->sec_info);
    printf("  Address alignment: %llu\n", header->sec_addralign);
    printf("  Entry size: %llu\n", header->sec_entsize);
}

// Print the symbol
void elf_print_symbol(const ElfSymbol64* symbol) {
    printf("Symbol:\n");
    printf("  Name: %d\n", symbol->sym_name);
    printf("  Info: %d\n", symbol->sym_info);
    printf("  Other: %d\n", symbol->sym_other);
    printf("  Section index: %d\n", symbol->sym_shndx);
    printf("  Value: %llu\n", symbol->sym_value);
    printf("  Size: %llu\n", symbol->sym_size);
}