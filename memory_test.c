#include "memory.h"
#include "memory_test.h"

const int test_value = 10;
const int test_index = 5;

int test_encode = 56;
int test_operand = 72;
int test_command = 32;
int encoded_command;

void memory_test() 
{
	printf("%s", "Memory tests: \r\n");

	set_register_test();
	get_register_test();
	set_value_test();
	get_value_test();
	out_of_memory_test();
	encode_command_test();
	decode_command_test();

	printf("%s", "\r\n\r\n");
}

void encode_command_test()
{
	int ok;
	int flag;

	sc_regInit();

	ok = sc_commandEncode(test_command, test_operand, &encoded_command);
	sc_regGet(FLAG_COMMAND, &flag);

	if (ok == OK && !flag)
	{
		printf("%s", "Test 'commandEncode': passed \r\n");
	}
	else
	{
		printf("%s", "Test 'commandEncode': error \r\n");
	}
}

void decode_command_test()
{
	int ok;
	int flag;

	ok = sc_commandDecode(&test_command, &test_operand, encoded_command);
	sc_regGet(FLAG_COMMAND, &flag);

	if (ok == OK && !flag)
	{
		printf("%s", "Test 'commandDecode': passed \r\n");
	}
	else
	{
		printf("%s", "Test 'commandDecode': error \r\n");
	}
}

void set_register_test() 
{
	int out;
	sc_regInit();

	out = sc_regSet(FLAG_OVERFLOW, 0);
	out &= sc_regSet(FLAG_COMMAND, 0);
	out &= sc_regSet(FLAG_OUT_OF_MEMORY, 1);
	out &= sc_regSet(FLAG_DIVISION, 1);
	out &= sc_regSet(FLAG_ODD, 1);

	if (out == OK) 
	{
		printf("%s", "Test 'regSet': passed \r\n");
	}
	else
	{
		printf("%s", "Test 'regSet': error \r\n");
	}
}

void get_register_test()
{
	//register initialized in set_register_test
	int result;
	int flag;
	int ok;

	ok = sc_regGet(FLAG_COMMAND, &flag);
	result = !flag;

	ok &= sc_regGet(FLAG_OUT_OF_MEMORY, &flag);
	result &= flag;

	ok &= sc_regGet(FLAG_DIVISION, &flag);
	result &= flag;

	ok &= sc_regGet(FLAG_ODD, &flag);
	result &= flag;

	ok &= sc_regGet(FLAG_OVERFLOW, &flag);
	result &= !flag;

	if (ok == OK && result) 
	{
		printf("%s", "Test 'regGet': passed \r\n");
	}
	else
	{
		printf("%s", "Test 'regGet': error \r\n");
	}
}

void set_value_test() 
{
	int result;
	int flag;

	sc_memoryInit();
	sc_regInit();

	result = sc_memorySet(test_index, test_value);
	sc_regGet(FLAG_OUT_OF_MEMORY, &flag);
	
	if (!flag && result == OK)
	{
		printf("%s", "Test 'memorySet': passed \r\n");
	}
	else
	{
		printf("%s", "Test 'memorySet': error \r\n");
	}
}

void get_value_test() 
{
	int result;
	int flag;
	int actualValue;

	//memory alredy initialized 
	//after set_value_test

	result = sc_memoryGet(test_index, &actualValue);
	sc_regGet(FLAG_OUT_OF_MEMORY, &flag);

	if (actualValue == test_value && !flag && result == OK)
	{
		printf("%s", "Test 'memoryGet': passed \r\n");
	}
	else
	{
		printf("%s", "Test 'memoryGet': error \r\n");
	}
}

void out_of_memory_test()
{
	const int value = 10;
	const int index = 101;

	int result;
	int flag;

	sc_memoryInit();
	sc_regInit();

	result = sc_memorySet(index, value);
	sc_regGet(FLAG_OUT_OF_MEMORY, &flag);

	if (flag && result == OUT_OF_RANGE_ERROR)
	{
		printf("%s", "Test 'out of memory': passed \r\n");
	}
	else 
	{
		printf("%s", "Test 'out of memory': error \r\n");
	}
}