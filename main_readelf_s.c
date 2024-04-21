///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  sre_lab6_readelf-lyons811 - EE 491F - Spr 2024
///
/// @file main_readelf_s.c
/// @version 1.0
///
/// @author Lyon Singleton <lyonws@hawaii.edu>
/// @date   19_Apr_2024
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "elf_parser.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ELF file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    ElfHeader64 header;
    ElfSectionHeader64 sheader;
    ElfSymbol64 symbol;

    // Read ELF header
    elf_read_header(filename, &header);

    // Iterate each section header
    for (int i = 0; i < header.e_shnum; i++) {
        // Read current section header
        elf_read_section_header(filename, header.e_shoff + i * sizeof(ElfSectionHeader64), &sheader);

        // Check if section is a symbol table (SHT_SYMTAB or SHT_DYNSYM)
        if (sheader.sec_type == SHT_SYMTAB || sheader.sec_type == SHT_DYNSYM) {
            // Find offset of string table associated with symbol table
            long strtab_offset = find_strtab_offset(filename, sheader.sec_link);

            // Iterate each symbol in symbol table
            for (int j = 0; j < sheader.sec_size / sizeof(ElfSymbol64); j++) {
                // Read current symbol
                elf_read_symbol(filename, sheader.sec_offset + j * sizeof(ElfSymbol64), &symbol);

                // Get name of symbol from string table
                const char* sym_name = get_symbol_name(filename, strtab_offset, symbol.sym_name);

                // Print  symbol information
                elf_print_symbol(&symbol, sym_name);
            }
        }
    }

    return EXIT_SUCCESS;
}