#include "../../../inc/ft_nm.h"

// Searches for a section with a given name in the ELF64 section headers.
// Returns a pointer to the matching section, or NULL if not found.
Elf64_Shdr *find_section_by_name_64(t_section_ctx_64 *ctx, const char *name)
{
	if (!ctx->shstrtab)
		return NULL;

	for (int i = 0; i < ctx->ehdr->e_shnum; i++)
	{
		const char *sname = ctx->shstrtab + ctx->shdr[i].sh_name;
		if (ft_strcmp(sname, name) == 0)
			return (&ctx->shdr[i]);
	}
	return NULL;
}

// Tries to find the pair of symbol and string tables (.symtab/.strtab).
// Returns 1 if both are found, 0 otherwise.
int find_sym_and_str_tab_64(t_section_ctx_64 *ctx, Elf64_Shdr **symtab, Elf64_Shdr **strtab)
{
	*symtab = find_section_by_name_64(ctx, ".symtab");
	*strtab = find_section_by_name_64(ctx, ".strtab");

	return (*symtab && *strtab);
}
