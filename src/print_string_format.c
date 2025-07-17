#include "../headers/print_string_format.h"

void count_digits_in_different_format(int *counter, unsigned long long number, char format)
{
	int x = 0;
	switch (format)
	{
	case 'd':
		x = 10;
		break;
	case 'b':
		x = 2;
		break;
	case 'o':
		x = 8;
		break;
	case 'x':
		x = 16;
		break;
	case 'X':
		x = 16;
		break;
	default:
		break;
	}

	while (number > 0)
	{
		number /= x;
		++(*counter);
	}
}
unsigned long long converte_to_dec(const char *number, int minus_offset, char format)
{
	unsigned long long decimal_number = 0;

	bool is_wrong_symbols = false;

	int power_value = 0;
	if (format == 'b')
	{
		for (int i = strlen(number) - 1; i > 1 + minus_offset; --i)
		{
			if (number[i] >= '0' && number[i] <= '1')
			{
				decimal_number += (number[i] - '0') * power(2, power_value);
				++power_value;
			}
			else
			{
				is_wrong_symbols = true;
				break;
			}
		}
	}

	else if (format == 'x')
	{
		for (int i = strlen(number) - 1; i > 1 + minus_offset; --i)
		{
			if (tolower(number[i]) >= 'a' && tolower(number[i]) <= 'f')
			{
				decimal_number += (tolower(number[i]) - 'a' + 10) * power(16, power_value);
			}
			else if (number[i] >= '0' && number[i] <= '9')
			{
				decimal_number += (number[i] - '0') * power(16, power_value);
			}
			else
			{
				is_wrong_symbols = true;
				break;
			}
			++power_value;
		}
	}

	else if (format == 'd')
	{
		for (int i = strlen(number) - 1; i >= 0 + minus_offset; --i)
		{
			if (number[i] >= '0' && number[i] <= '9')
			{
				decimal_number += (number[i] - '0') * power(10, power_value);
				++power_value;
			}
			else
			{
				is_wrong_symbols = true;
				break;
			}
		}
	}

	else if (format == 'o')
	{
		for (int i = strlen(number) - 1; i > 0 + minus_offset; --i)
		{
			if (number[i] >= '0' && number[i] <= '7')
			{
				decimal_number += (number[i] - '0') * power(8, power_value);
				++power_value;
			}
			else
			{
				is_wrong_symbols = true;
				break;
			}
		}
	}

	if (is_wrong_symbols == true)
	{
		return -128;
	}
	else
	{
		return decimal_number;
	}
}

void converte_to_format(unsigned long long *decimal_number, char format, char *out_buf, int *i)
{
	switch (format)
	{
	case 'd':
		while (*decimal_number > 0)
		{
			out_buf[*i] = *decimal_number % 10 + '0';
			*decimal_number /= 10;
			--(*i);
		}
		break;
	case 'b':
		while (*decimal_number > 0)
		{
			out_buf[*i] = *decimal_number % 2 + '0';
			*decimal_number >>= 1;
			--(*i);
		}
		break;
	case 'o':
		while (*decimal_number > 0)
		{
			out_buf[*i] = *decimal_number % 8 + '0';
			*decimal_number /= 8;
			--(*i);
		}
		break;
	case 'x':
		while (*decimal_number > 0)
		{
			if (*decimal_number % 16 >= 10)
			{
				out_buf[*i] = *decimal_number % 16 + 'a' - 10;
			}
			else
			{
				out_buf[*i] = *decimal_number % 16 + '0';
			}

			*decimal_number /= 16;
			--(*i);
		}
		break;
	case 'X':
		while (*decimal_number > 0)
		{
			if (*decimal_number % 16 >= 10)
			{
				out_buf[*i] = *decimal_number % 16 + 'A' - 10;
			}
			else
			{
				out_buf[*i] = *decimal_number % 16 + '0';
			}

			*decimal_number /= 16;
			--(*i);
		}
		break;

	default:
		break;
	}
}

int print(char *out_buf, const char *format, const char *number)
{
	int digit_counter = 0;
	char *flags = malloc(sizeof(char) * 5);
	memset(flags, '.', sizeof(char) * 5);

	bool is_first_zero = true;

	for (int i = 1; i < strlen(format); ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (format[i] == j + '0')
			{
				if (is_first_zero && format[i] != '0')
				{
					is_first_zero = false;
				}

				else if (is_first_zero && format[i] == '0')
				{
					flags[4] = '0';
					is_first_zero = false;
				}

				++digit_counter;
			}
		}

		switch (format[i])
		{
		case 'b':
			flags[0] = 'b';
			break;
		case 'o':
			flags[0] = 'o';
			break;
		case 'd':
			flags[0] = 'd';
			break;
		case 'x':
			flags[0] = 'x';
			break;
		case 'X':
			flags[0] = 'X';
			break;
		case ' ':
			flags[1] = ' ';
			break;
		case '#':
			flags[1] = '#';
			break;
		case '+':
			flags[2] = '+';
			break;
		case '-':
			flags[3] = '-';
			break;

		default:
			break;
		}
	}

	if (flags[0] == '.')
	{
		fprintf(stderr, "No format in format string or incorrect format!");
		free(flags);
		return 0;
	}

	int out_buf_str_len = 0;

	if (digit_counter != 0)
	{
		--digit_counter;
		for (int i = 1; i < strlen(format); ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (format[i] == j + '0')
				{
					out_buf_str_len += j * power(10, digit_counter);
					--digit_counter;
				}
			}
		}
	}

	bool can_contain_format_specifiers = false;

	if (strlen(number) > 2)
	{
		can_contain_format_specifiers = true;
	}

	bool minus_flag = false;

	int minus_offset = 0;

	if (number[0] == '-')
	{
		minus_flag = true;
		minus_offset = 1;
	}

	unsigned long long decimal_number = 0;

	if (can_contain_format_specifiers)
	{
		if (number[0 + minus_offset] == '0' && number[1 + minus_offset] == 'b')
		{
			decimal_number = converte_to_dec(number, minus_offset, 'b');
		}

		else if (number[0 + minus_offset] == '0' && tolower(number[1 + minus_offset]) == 'x')
		{
			decimal_number = converte_to_dec(number, minus_offset, 'x');
		}

		else
		{
			can_contain_format_specifiers = false;
		}
	}

	if (strlen(number) > 0 && can_contain_format_specifiers == false)
	{
		if (number[0 + minus_offset] != '0')
		{
			decimal_number = converte_to_dec(number, minus_offset, 'd');
		}

		else if (number[0 + minus_offset] == '0')
		{
			decimal_number = converte_to_dec(number, minus_offset, 'o');
		}
	}

	if (decimal_number == -128)
	{
		fprintf(stderr, "Wrong symbols in string number!");
		free(flags);
		return 0;
	}

	int counter = 0;

	if (decimal_number == 0)
	{
		counter = 1;
		minus_flag = false;
	}

	count_digits_in_different_format(&counter, decimal_number, flags[0]);

	if (flags[1] == '#' && flags[0] != 'd')
	{
		counter += 2;
	}

	if (minus_flag == true || (minus_flag == false && flags[2] == '+'))
	{
		counter += 1;
	}

	int out_buf_space = 0;

	if (counter < out_buf_str_len)
	{
		out_buf_space = out_buf_str_len - counter;
		counter = out_buf_str_len;
	}

	else if (counter >= out_buf_str_len && flags[1] == ' ' && minus_flag == false)
	{
		out_buf_space = 1;
		counter += 1;
	}

	int i = counter - 1;

	if (flags[3] == '-')
	{
		i = counter - out_buf_space - 1;
	}

	if (decimal_number == 0)
	{
		out_buf[i] = '0';
		--i;
	}
	else
	{
		converte_to_format(&decimal_number, flags[0], out_buf, &i);
	}

	if (flags[4] != '0' || (flags[4] == '0' && flags[3] == '-'))
	{
		if (flags[1] == '#' && flags[0] != 'd')
		{
			out_buf[i--] = flags[0];
			out_buf[i--] = '0';
		}

		if (minus_flag == true)
		{
			out_buf[i] = '-';
			--i;
		}

		else if (minus_flag == false && flags[2] == '+')
		{
			out_buf[i] = '+';
			--i;
		}

		if (flags[3] == '-')
		{
			for (int fs = counter - out_buf_space; fs < counter; ++fs)
			{
				out_buf[fs] = ' ';
			}
		}

		else
		{
			for (; i >= 0; --i)
			{
				out_buf[i] = ' ';
			}
		}
	}
	else
	{
		for (; out_buf_space > 0; --out_buf_space)
		{
			out_buf[i--] = '0';
		}

		if (flags[1] == '#' && flags[0] != 'd')
		{
			out_buf[i--] = flags[0];
			out_buf[i--] = '0';
		}

		if (minus_flag == true)
		{
			out_buf[i] = '-';
		}
		else if (minus_flag == false && flags[2] == '+')
		{
			out_buf[i] = '+';
		}
	}

	out_buf[counter] = '\0';

	free(flags);

	return 1;
}
