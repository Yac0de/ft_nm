#include "../../../inc/ft_nm.h"

// Prints a 64-bit value as zero-padded hexadecimal
// Always prints exactly `width` characters.
static void print_hex_padding(uint64_t value, int width)
{
	char buffer[17];
	const char *hex = "0123456789abcdef";
	int i = width - 1;

	buffer[width] = '\0';
	while (i >= 0)
	{
		buffer[i] = hex[value % 16];
		value /= 16;
		i--;
	}
	ft_putstr_fd(buffer, 1);
}

// Displays all 64-bit symbols in the standard nm output format.
// Format: [hex address] [symbol type] [symbol name]
// For undefined symbols (type 'U'), address is replaced by padding.
int display_symbols_64(t_symbol_64 *symbols, int count)
{
	if (!symbols || count <= 0)
		return 0;

	for (int i = 0; i < count; i++)
	{
		if (symbols[i].type != 'U')
			print_hex_padding(symbols[i].sym.st_value, 16);
		else
		{
			for (int j = 0; j < 16; j++)
				ft_putchar_fd(' ', 1);
		}

		ft_putchar_fd(' ', 1);
		ft_putchar_fd(symbols[i].type, 1);
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(symbols[i].name, 1);
		ft_putchar_fd('\n', 1);
	}
	return 1;
}
