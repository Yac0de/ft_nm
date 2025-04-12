#include "../inc/ft_nm.h"

// Determine ELF class (32 or 64 bit) and delegate to the appropriate handler.
// Returns 0 on success, 1 on error.
int	handle_elf_file(t_file *file)
{
	if (!file->map)
		return (ft_putstr_fd("Error: NULL ELF map\n", 2), 1);

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)file->map;
	unsigned char class = ehdr->e_ident[EI_CLASS];

	// Dispatch to the correct handler based on ELF class
	if (class == ELFCLASS64)
		return parse_and_display_elf64_symbols(file);
	else if (class == ELFCLASS32)
		return parse_and_display_elf32_symbols(file);
	else
		return (ft_putstr_fd("Error: Unknown ELF class\n", 2), 1);
}
