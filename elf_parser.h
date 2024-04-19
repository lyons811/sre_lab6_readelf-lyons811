///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  sre_lab6_readelf-lyons811 - EE 491F - Spr 2024
///
/// @file elf_parser.h
/// @version 1.0
///
/// @author Lyon Singleton <lyonws@hawaii.edu>
/// @date   19_Apr_2024
///////////////////////////////////////////////////////////////////////////////
#ifndef SRE_LAB6_READELF_LYONS811_ELF_PARSER_H
#define SRE_LAB6_READELF_LYONS811_ELF_PARSER_H
#include <stdint.h>
// ELF Header
typedef struct {
    unsigned char e_ident[16]; // ELF identification
    uint16_t e_type; // Object file type
    uint16_t e_machine; // Machine type
    uint32_t e_version; // Object file version
    uint64_t e_entry; // Entry point address
    uint64_t e_phoff; // Program header offset
    uint64_t e_shoff; // Section header offset
    uint32_t e_flags; // Processor-specific flags
    uint16_t e_ehsize; // ELF header size
    uint16_t e_phentsize; // Size of program header entry
    uint16_t e_phnum; // Number of program header entries
    uint16_t e_shentsize; // Size of section header entry
    uint16_t e_shnum; // Number of section header entries
    uint16_t e_shstrndx; // Section name string table index
} ElfHeader64;

// Section Header
typedef struct {
    uint32_t sec_name; // section name
    uint32_t sec_type; // section type
    uint64_t sec_flags; // section flags
    uint64_t sec_addr; // section virtual address
    uint64_t sec_offset; // section file offset
    uint64_t sec_size; // section size in bytes
    uint32_t sec_link; // link to another section
    uint32_t sec_info; //  section information
    uint64_t sec_addralign; // section alignment
    uint64_t sec_entsize; // entry size
} ElfSectionHeader64;

// Symbol Table
typedef struct {
    uint32_t sym_name; // symbol name
    uint8_t sym_info; // symbol info
    uint8_t sym_other; // symbol other
    uint16_t sym_shndx; // symbol section index
    uint64_t sym_value; // symbol value
    uint64_t sym_size; // symbol size
} ElfSymbol64;

// Functions
void elf_read_header(const char* filename, ElfHeader64* header);
void elf_read_section_header(const char* filename, uint64_t offset, ElfSectionHeader64* header);
void elf_print_header(const ElfHeader64* header);
void elf_print_section_header(const ElfSectionHeader64* header);
void elf_print_symbol(const ElfSymbol64* symbol);

#endif //SRE_LAB6_READELF_LYONS811_ELF_PARSER_H
