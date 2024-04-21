///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  sre_lab6_readelf-lyons811 - EE 491F - Spr 2024
///
/// @file main_readelf_h.c
/// @version 1.0
///
/// @author Lyon Singleton <lyonws@hawaii.edu>
/// @date   19_Apr_2024
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "elf_parser.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    ElfHeader64 header;

    // Read ELF header from file
    elf_read_header(argv[1], &header);

    // Print  ELF header information
    elf_print_header(&header);

    return EXIT_SUCCESS;
}