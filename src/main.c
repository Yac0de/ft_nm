#include "../inc/ft_nm.h"

// Loads the given ELF file into memory using mmap.
// On success, updates the file's `map` and `size` fields.
static int	load_elf_file(t_file *file)
{
	int fd = open_file(file->name);
	if (fd < 0)
		return (1);

	struct stat st;
	if (get_file_stat(fd, &st) < 0)
		return (close(fd), 1);

	// Check: file too small to contain a complete ELF header
	if ((size_t)st.st_size < sizeof(Elf64_Ehdr))
	{
		close(fd);
		ft_putstr_fd("nm: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		ft_putstr_fd(": file format not recognized\n", 2);
		return (1);
	}

	file->map = map_file(fd, st.st_size);
	close(fd);
	if (file->map == MAP_FAILED)
		return (1);

	file->size = st.st_size;
	return (0);
}

int	main(int argc, char **argv)
{
	// Expect exactly one argument: the path to the ELF file
	if (argc != 2)
		return (print_usage());

	t_file file;
	file.name = argv[1];
	// Load the file and map it into memory
	if (load_elf_file(&file) != 0)
		return (1);

	// Check that the file starts with a valid ELF header
	if (!is_valid_elf(file.map))
		return (unmap_file(&file), ft_putstr_fd("Not an ELF file\n", 2), 1);

	// Handle ELF parsing and symbol display (32/64-bit)
	int status = handle_elf_file(&file);

	// Clean up: unmap the file before exiting
	unmap_file(&file);
	return (status);
}
