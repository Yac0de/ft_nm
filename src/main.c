#include "../inc/ft_nm.h"

// Load an ELF file into memory using mmap.
// On success, stores the mapped address in `*map` and the file size in `*size`.
static int	load_elf_file(const char *filename, void **map, size_t *size)
{
	int fd = open_file(filename);
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
		ft_putstr_fd((char *)filename, 2);
		ft_putstr_fd(": file format not recognized\n", 2);
		return (1);
	}

	*map = map_file(fd, st.st_size);
	close(fd);
	if (*map == MAP_FAILED)
		return (1);

	*size = st.st_size;
	return (0);
}

int	main(int argc, char **argv)
{
	// Expect exactly one argument: the ELF file to process
	if (argc != 2)
		return (print_usage());

	void *map;
	size_t size;

	// Load the file and map it into memory
	if (load_elf_file(argv[1], &map, &size) != 0)
		return (1);

	// Check that the file starts with a valid ELF header
	if (!is_valid_elf(map))
		return (unmap_file(map, size), ft_putstr_fd("Not an ELF file\n", 2), 1);

	// Parse and display symbols depending on ELF class (32/64)
	int status = handle_elf_file(map, argv[1]);

	// Always unmap the file before exiting
	unmap_file(map, size);
	return (status);
}
