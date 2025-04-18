#include "../inc/ft_nm.h"

// Determines the ELF class (32 or 64-bit) and delegates to the appropriate parser.
// Returns 0 on success, 1 on error or if the ELF class is invalid.
int	handle_elf_file(t_file *file)
{
	if (!file->map)
		return (ft_putstr_fd("Error: NULL ELF map\n", 2), 1);

	// Treat the beginning of the mapped file as an ELF header
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)file->map;
	unsigned char class = ehdr->e_ident[EI_CLASS];

	// Dispatch to the correct handler based on ELF class
	if (class == ELFCLASS64)
		return parse_and_display_elf64_symbols(file);
	else if (class == ELFCLASS32)
		return parse_and_display_elf32_symbols(file);
	else
	{
		// Unknown or unsupported ELF class: fallback to nm-compatible error
		ft_putstr_fd("nm: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		return (ft_putstr_fd(": file format not recognized\n", 2), 1);
	}
}
