#include "../headers/main.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		return 1;
	}

	char *format = argv[1];
	char *number = argv[2];

	if (strlen(format) == 0 || strlen(number) == 0)
	{
		fprintf(stderr, "Empty input arguments!");
		return 1;
	}

	if (format[0] != '%')
	{
		fprintf(stderr, "No format specifier in format string!");
		return 1;
	}

	char *out_buf = (char *)malloc(150 * sizeof(char));

	if (!print(out_buf, format, number))
	{
		free(out_buf);
		return 1;
	}
	else
	{
		puts(out_buf);
		free(out_buf);
	}

	return 0;
}
