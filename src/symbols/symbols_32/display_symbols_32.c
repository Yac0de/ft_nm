#include "../../../inc/ft_nm.h"

// Prints a 32-bit value as zero-padded hexadecimal
// Always prints exactly `width` characters.
static void print_hex_padding(uint32_t value, int width)
{
	char buffer[9];
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

// Displays all 32-bit symbols in the standard nm output format.
// Format: [hex address] [symbol type] [symbol name]
// Addresses are not shown for undefined or weak-undefined symbols.
int display_symbols_32(t_symbol_32 *symbols, int count)
{
	if (!symbols || count <= 0)
		return 0;

	for (int i = 0; i < count; i++)
	{
		if (symbols[i].type == 'U' || symbols[i].type == 'w')
		{
			for (int j = 0; j < 8; j++)
				ft_putchar_fd(' ', 1);
		}
		else
			print_hex_padding(symbols[i].sym.st_value, 8);

		ft_putchar_fd(' ', 1);
		ft_putchar_fd(symbols[i].type, 1);
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(symbols[i].name, 1);
		ft_putchar_fd('\n', 1);
	}
	return 1;
}
