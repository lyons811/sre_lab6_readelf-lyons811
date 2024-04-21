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

// Macros for symbol binding and type
#define ELF64_ST_BIND(i) ((i) >> 4)
#define ELF64_ST_TYPE(i) ((i) & 0xf)

// Symbol binding constants
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2

// Symbol type constants
#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6

// Section type constants
#define SHT_NULL          0
#define SHT_PROGBITS      1
#define SHT_SYMTAB        2
#define SHT_STRTAB        3
#define SHT_RELA          4
#define SHT_HASH          5
#define SHT_DYNAMIC       6
#define SHT_NOTE          7
#define SHT_NOBITS        8
#define SHT_REL           9
#define SHT_SHLIB         10
#define SHT_DYNSYM        11
#define SHT_INIT_ARRAY    14
#define SHT_FINI_ARRAY    15
#define SHT_PREINIT_ARRAY 16
#define SHT_GROUP         17
#define SHT_SYMTAB_SHNDX  18
#define SHT_NUM           19
#define SHT_LOOS          0x60000000

// ELF Header structure
typedef struct {
    unsigned char e_ident[16];  // ELF identification
    uint16_t      e_type;       // Object file type
    uint16_t      e_machine;    // Machine type
    uint32_t      e_version;    // Object file version
    uint64_t      e_entry;      // Entry point address
    uint64_t      e_phoff;      // Program header offset
    uint64_t      e_shoff;      // Section header offset
    uint32_t      e_flags;      // Processor-specific flags
    uint16_t      e_ehsize;     // ELF header size
    uint16_t      e_phentsize;  // Size of program header entry
    uint16_t      e_phnum;      // Number of program header entries
    uint16_t      e_shentsize;  // Size of section header entry
    uint16_t      e_shnum;      // Number of section header entries
    uint16_t      e_shstrndx;   // Section name string table index
} ElfHeader64;

// Section Header structure
typedef struct {
    uint32_t sec_name;       // Section name
    uint32_t sec_type;       // Section type
    uint64_t sec_flags;      // Section flags
    uint64_t sec_addr;       // Section virtual address
    uint64_t sec_offset;     // Section file offset
    uint64_t sec_size;       // Section size in bytes
    uint32_t sec_link;       // Link to another section
    uint32_t sec_info;       // Additional section information
    uint64_t sec_addralign;  // Section alignment
    uint64_t sec_entsize;    // Entry size
} ElfSectionHeader64;

// Symbol Table Entry structure
typedef struct {
    uint32_t sym_name;   // Symbol name
    uint8_t  sym_info;   // Symbol type and binding
    uint8_t  sym_other;  // Symbol visibility
    uint16_t sym_shndx;  // Section index
    uint64_t sym_value;  // Symbol value
    uint64_t sym_size;   // Symbol size
} ElfSymbol64;

// Function prototypes
void elf_read_header(const char* filename, ElfHeader64* header);
void elf_read_section_header(const char* filename, uint64_t offset, ElfSectionHeader64* header);
void elf_read_symbol(const char* filename, uint64_t offset, ElfSymbol64* symbol);
void elf_print_header(const ElfHeader64* header);
void elf_print_section_header(const ElfSectionHeader64* header);
void elf_print_symbol(const ElfSymbol64* symbol, const char* name);
const char* get_symbol_name(const char* filename, uint64_t strtab_offset, uint32_t name_offset);
long find_strtab_offset(const char* filename, int strtab_index);
const char* get_symbol_type(uint8_t sym_info);
const char* get_symbol_bind(uint8_t sym_info);

#endif // SRE_LAB6_READELF_LYONS811_ELF_PARSER_H