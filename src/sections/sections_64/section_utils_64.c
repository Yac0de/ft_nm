#include "../../../inc/ft_nm.h"

// Searches for a section with a given name in the ELF64 section headers.
// Returns a pointer to the matching section, or NULL if not found.
Elf64_Shdr *find_section_by_name_64(t_section_ctx_64 *ctx, const char *name)
{
	if (!ctx->shstrtab)
		return NULL;

	for (int i = 0; i < ctx->ehdr->e_shnum; i++)
	{
		// Resolve section name from shstrtab using offset stored in sh_name
		const char *sname = ctx->shstrtab + ctx->shdr[i].sh_name;

		// Compare resolved name with requested name
		if (ft_strcmp(sname, name) == 0)
			return (&ctx->shdr[i]);
	}
	// Section not found
	return NULL;
}

// Tries to find the pair of symbol and string tables (.symtab/.strtab).
// Returns 1 if both are found, 0 otherwise.
int find_sym_and_str_tab_64(t_section_ctx_64 *ctx, Elf64_Shdr **symtab, Elf64_Shdr **strtab)
{
	// Search for symbol table section
	*symtab = find_section_by_name_64(ctx, ".symtab");

	// Search for associated string table
	*strtab = find_section_by_name_64(ctx, ".strtab");

	// Both must be present for valid symbol extraction
	return (*symtab && *strtab);
}
