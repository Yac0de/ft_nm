#pragma once

/* ========== External Libs ========== */

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <elf.h>

/* ========== Libft perso ========== */

# include "../libft/inc/libft.h"

/* ========== Symbol parsing status codes ========== */

#define SYMBOLS_OK     1
#define NO_SYMBOLS     0
#define INVALID_ELF   -1

/* ========== Structures ========== */

typedef struct s_file {
	void		*map;
	size_t		size;
	const char	*name;
}	t_file;

// ELF64
typedef struct s_section_ctx_64 {
	Elf64_Ehdr *ehdr;
	Elf64_Shdr *shdr;
	char *shstrtab;
} t_section_ctx_64;

typedef struct s_symbol_64 {
	Elf64_Sym	sym;
	char		*name;
	char		type;
}	t_symbol_64;

typedef struct s_symbol_info_64 {
	Elf64_Sym *sym;
	char *strtab;
	Elf64_Shdr *sections;
} t_symbol_info_64;

typedef struct s_symbol_ctx_64 {
	void        *map;
	size_t      file_size;
	Elf64_Shdr  *symtab;
	Elf64_Shdr  *strtab;
} t_symbol_ctx_64;

typedef struct s_symbol_build_ctx_64
{
	Elf64_Sym *symbols;
	int symbol_count;
	char *strtab_data;
	Elf64_Shdr *sections;
} t_symbol_build_ctx_64;

// ELF32
typedef struct s_section_ctx_32 {
	Elf32_Ehdr *ehdr;
	Elf32_Shdr *shdr;
	char *shstrtab;
} t_section_ctx_32;


typedef struct s_symbol_32 {
	Elf32_Sym	sym;
	char		*name;
	char		type;
}	t_symbol_32;

typedef struct s_symbol_info_32 {
	Elf32_Sym *sym;
	char *strtab;
	Elf32_Shdr *sections;
} t_symbol_info_32;

typedef struct s_symbol_ctx_32 {
	void		*map;
	size_t      file_size;
	Elf32_Shdr	*symtab;
	Elf32_Shdr	*strtab;
}	t_symbol_ctx_32;

typedef struct s_symbol_build_ctx_32
{
	Elf32_Sym *symbols;
	int symbol_count;
	char *strtab_data;
	Elf32_Shdr *sections;
} t_symbol_build_ctx_32;


/* ========== Core ========== */

// elf_utils.c
int		print_usage(void);
int		get_elf_class(void *map);
int		is_valid_elf(void *map);

// file_utils.c
int		open_file(const char *path);
int		get_file_stat(int fd, struct stat *st);
void	*map_file(int fd, size_t size);
int		unmap_file(t_file *file);

// handle_elf_file.c
int		handle_elf_file(t_file *file);
int		parse_and_display_elf64_symbols(t_file *file);
int		parse_and_display_elf32_symbols(t_file *file);


/* ========== Section parsing ========== */

// read_sections_64.c
void		read_sections_64(void *map);

// read_sections_32.c
void		read_sections_32(void *map);

// section_utils_64.c
Elf64_Shdr *find_section_by_name_64(t_section_ctx_64 *ctx, const char *name);
int find_sym_and_str_tab_64(t_section_ctx_64 *ctx, Elf64_Shdr **symtab, Elf64_Shdr **strtab);

// section_utils_32.c
Elf32_Shdr *find_section_by_name_32(t_section_ctx_32 *ctx, const char *name);
int find_sym_and_str_tab_32(t_section_ctx_32 *ctx, Elf32_Shdr **symtab, Elf32_Shdr **strtab);


/* ========== Symbol handling 64 ========== */

// read_symbols_64.c
int		read_symbols_64(t_symbol_ctx_64 *ctx);

// collect_symbols_64.c
t_symbol_64	*collect_symbols_64(t_symbol_ctx_64 *ctx , int *out_count);

// symbol_builder_64.c
t_symbol_64	build_symbol_64(t_symbol_info_64 *info);

// sort_symbols_64.c
int		sort_symbols_64(t_symbol_64 *symbols, int count);

// skip_symbol_64.c
int			skip_symbol_64(t_symbol_info_64 *info);

// get_symbol_letter_64.c
char		get_symbol_letter_64(t_symbol_info_64 *info);

// display_symbols_64.c
int		display_symbols_64(t_symbol_64 *symbols, int count);


/* ========== Symbol handling 32 ========== */

// read_symbols_32.c
int		read_symbols_32(t_symbol_ctx_32 *ctx);

// collect_symbols_32.c
t_symbol_32	*collect_symbols_32(t_symbol_ctx_32 *ctx, int *out_count);

// symbol_builder_32.c
t_symbol_32	build_symbol_32(t_symbol_info_32 *info);

// sort_symbols_32.c
int		sort_symbols_32(t_symbol_32 *symbols, int count);

// skip_symbol_32.c
int			skip_symbol_32(t_symbol_info_32 *info);

// get_symbol_letter_32.c
char		get_symbol_letter_32(t_symbol_info_32 *info);

// display_symbols_32.c
int		display_symbols_32(t_symbol_32 *symbols, int count);
