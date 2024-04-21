###############################################################################
#   University of Hawaii, College of Engineering
#   @brief  sre_lab6_readelf-lyons811 - EE 491F - Spr 2024
#
### Build and test an ELF parser
###
### @see     https://www.gnu.org/software/make/manual/make.html
###
### @file    Makefile
### @author  Lyon Singleton <lyonws@hawaii.edu>
###############################################################################


CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g


all: readelf_h readelf_s


readelf_h: main_readelf_h.o elf_parser.o
	$(CC) $(CFLAGS) -o readelf_h main_readelf_h.o elf_parser.o


readelf_s: main_readelf_s.o elf_parser.o
	$(CC) $(CFLAGS) -o readelf_s main_readelf_s.o elf_parser.o


%.o: %.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f *.o readelf_h readelf_s


.PHONY: all clean test


test: all
	./readelf_h /bin/ls
	./readelf_s /bin/ls