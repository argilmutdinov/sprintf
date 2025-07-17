unsigned long long power(int num, int power_value)
{
	unsigned long long result = 1;
	if (power_value == 1)
	{
		return num;
	}
	else if (power_value == 0)
	{
		return 1;
	}

	for (int i = 0; i < power_value; ++i)
	{
		result *= num;
	}
	return result;
}
