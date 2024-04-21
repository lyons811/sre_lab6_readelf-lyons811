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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "elf_parser.h"

/**
 * Reads the ELF header from the specified file into the provided header structure.
 *
 * @param filename The name of the ELF file to read from.
 * @param header Pointer to the ElfHeader64 structure to store the header data.
 */
void elf_read_header(const char* filename, ElfHeader64* header) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    if (fread(header, sizeof(ElfHeader64), 1, file) != 1) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

/**
 * Reads a section header from the specified file at the given offset into the provided header structure.
 *
 * @param filename The name of the ELF file to read from.
 * @param offset The offset in the file where the section header is located.
 * @param header Pointer to the ElfSectionHeader64 structure to store the section header data.
 */
void elf_read_section_header(const char* filename, uint64_t offset, ElfSectionHeader64* header) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    if (fseek(file, offset, SEEK_SET) != 0) {
        perror("Error seeking file");
        exit(EXIT_FAILURE);
    }
    if (fread(header, sizeof(ElfSectionHeader64), 1, file) != 1) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

/**
 * Prints the contents of the ELF header.
 *
 * @param header Pointer to the ElfHeader64 structure containing the header data.
 */
void elf_print_header(const ElfHeader64* header) {
    printf("ELF Header:\n");
    printf("  Type: %d\n", header->e_type);
    printf("  Machine: %d\n", header->e_machine);
    printf("  Version: %d\n", header->e_version);
    printf("  Entry point address: 0x%llx\n", header->e_entry);
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

/**
 * Prints the contents of a section header.
 *
 * @param header Pointer to the ElfSectionHeader64 structure containing the section header data.
 */
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

/**
 * Prints the contents of a symbol.
 *
 * @param symbol Pointer to the ElfSymbol64 structure containing the symbol data.
 * @param name The name of the symbol.
 */
void elf_print_symbol(const ElfSymbol64* symbol, const char* name) {
    printf("%016lx %5ld %-7s %-6s %4d %s\n",
           symbol->sym_value,
           symbol->sym_size,
           get_symbol_type(symbol->sym_info),
           get_symbol_bind(symbol->sym_info),
           symbol->sym_shndx,
           name);
}

/**
 * Finds the offset of the string table section in the ELF file.
 *
 * @param filename The name of the ELF file.
 * @param strtab_index The index of the string table section.
 * @return The offset of the string table section, or -1 if an error occurred.
 */
long find_strtab_offset(const char* filename, int strtab_index) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    ElfHeader64 header;
    if (fread(&header, sizeof(ElfHeader64), 1, file) != 1) {
        perror("Failed to read ELF header");
        fclose(file);
        return -1;
    }

    ElfSectionHeader64 sheader;
    if (fseek(file, header.e_shoff + strtab_index * sizeof(ElfSectionHeader64), SEEK_SET) != 0) {
        perror("Failed to seek to string table section header");
        fclose(file);
        return -1;
    }
    if (fread(&sheader, sizeof(ElfSectionHeader64), 1, file) != 1) {
        perror("Failed to read string table section header");
        fclose(file);
        return -1;
    }

    fclose(file);
    return sheader.sec_offset;
}

/**
 * Reads a symbol from the specified file at the given offset into the provided symbol structure.
 *
 * @param filename The name of the ELF file to read from.
 * @param offset The offset in the file where the symbol is located.
 * @param symbol Pointer to the ElfSymbol64 structure to store the symbol data.
 */
void elf_read_symbol(const char* filename, uint64_t offset, ElfSymbol64* symbol) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    if (fseek(file, offset, SEEK_SET) != 0) {
        perror("Failed to seek to symbol");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    if (fread(symbol, sizeof(ElfSymbol64), 1, file) != 1) {
        perror("Failed to read symbol");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

/**
 * Retrieves the name of a symbol from the string table in the ELF file.
 *
 * @param filename The name of the ELF file.
 * @param strtab_offset The offset of the string table section in the file.
 * @param name_offset The offset of the symbol name within the string table.
 * @return Pointer to a static buffer containing the symbol name, or NULL if an error occurred.
 */
const char* get_symbol_name(const char* filename, uint64_t strtab_offset, uint32_t name_offset) {
    static char name[256];  // Buffer to hold the name
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    if (fseek(file, strtab_offset + name_offset, SEEK_SET) != 0) {
        perror("Failed to seek to symbol name");
        fclose(file);
        return NULL;
    }
    if (fgets(name, sizeof(name), file) == NULL) {
        perror("Failed to read symbol name");
        fclose(file);
        return NULL;
    }

    fclose(file);
    return name;
}

/**
 * Retrieves the type of a symbol based on the symbol info.
 *
 * @param sym_info The symbol info containing the type.
 * @return The type of the symbol as a string.
 */
const char* get_symbol_type(uint8_t sym_info) {
    switch (ELF64_ST_TYPE(sym_info)) {
        case STT_NOTYPE:  return "NOTYPE";
        case STT_OBJECT:  return "OBJECT";
        case STT_FUNC:    return "FUNC";
        case STT_SECTION: return "SECTION";
        case STT_FILE:    return "FILE";
        case STT_COMMON:  return "COMMON";
        case STT_TLS:     return "TLS";
        default:          return "UNKNOWN";
    }
}

/**
 * Retrieves the binding of a symbol based on the symbol info.
 *
 * @param sym_info The symbol info containing the binding.
 * @return The binding of the symbol as a string.
 */
const char* get_symbol_bind(uint8_t sym_info) {
    switch (ELF64_ST_BIND(sym_info)) {
        case STB_LOCAL:  return "LOCAL";
        case STB_GLOBAL: return "GLOBAL";
        case STB_WEAK:   return "WEAK";
        default:         return "UNKNOWN";
    }
}