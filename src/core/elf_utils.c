#include "../../inc/ft_nm.h"

// Prints usage message to stderr when arguments are invalid.
// Always returns 1 for convenience.
int print_usage(void)
{
	return (ft_putstr_fd("Usage: ./ft_nm <elf_file>\n", 2), 1);
}

// Returns ELF class (32 or 64) based on the ELF header.
// Returns -1 if the class is invalid or unrecognized.
int get_elf_class(void *map)
{
	unsigned char *ident = (unsigned char *)map;

	if (ident[EI_CLASS] == ELFCLASS64)
		return 64;
	if (ident[EI_CLASS] == ELFCLASS32)
		return 32;
	return -1;
}

// Checks if the file begins with a valid ELF magic number.
// Returns 1 if valid, 0 otherwise.
int is_valid_elf(void *map)
{
	if (!map)
		return 0;

	unsigned char *ident = (unsigned char *)map;
	return (ident[0] == 0x7f &&
			ident[1] == 'E' &&
			ident[2] == 'L' &&
			ident[3] == 'F');
}
