#include "../../inc/ft_nm.h"

// Opens the file at the given path in read-only mode.
// Returns the file descriptor, or -1 on error (with perror).
int open_file(const char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("open");
	return (fd);
}

// Retrieves file metadata (e.g., size) using fstat.
// Returns 0 on success, -1 on error (with perror).
int get_file_stat(int fd, struct stat *st)
{
	if (fstat(fd, st) < 0)
		return (perror("fstat"), -1);
	return 0;
}

// Maps the file into memory with read-only access.
// Returns a pointer to the mapped region, or MAP_FAILED on error (with perror).
void *map_file(int fd, size_t size)
{
	void *map = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
		perror("mmap");
	return map;
}

// Unmaps a previously mapped file region.
// Returns 0 on success, -1 on error.
int unmap_file(t_file *file)
{
	return munmap(file->map, file->size);
}
