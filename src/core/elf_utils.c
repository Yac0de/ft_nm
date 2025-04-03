#include "../../inc/ft_nm.h"

// Displays usage help when incorrect arguments are passed.
// Returns 1 for convenience in main().
int print_usage(void)
{
	return (ft_putstr_fd("Usage: ./ft_nm <elf_file>\n", 2), 1);
}

// Extracts the ELF class (32 or 64) from the file header.
// Returns 32 or 64 on success, -1 on invalid value.
int get_elf_class(void *map)
{
	unsigned char *ident = (unsigned char *)map;

	if (ident[EI_CLASS] == ELFCLASS64)
		return 64;
	if (ident[EI_CLASS] == ELFCLASS32)
		return 32;
	return -1;
}

// Verifies that the file starts with a valid ELF magic number.
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
