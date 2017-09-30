#include "memory.h"

/* Initialize memory array */
int sc_memoryInit() 
{
	memset(memory, 0, sizeof(*memory));
	return OK;
}

/* Set value to memory by address */
int sc_memorySet(int address, int value) 
{
	if (address < 0 || address >= MEMORY_LENGTH) 
	{
		sc_regSet(FLAG_OUT_OF_MEMORY, 1);
		return OUT_OF_RANGE_ERROR;
	}

	memory[address] = value;
	return OK;
}

/* Get value from memroy by address */
int sc_memoryGet(int address, int* value) 
{
	if (address < 0 || address >= MEMORY_LENGTH)
	{
		sc_regSet(FLAG_OUT_OF_MEMORY, 1);
		return OUT_OF_RANGE_ERROR;
	}

	*value = memory[address];
	return OK;
}

/* Save memory buffer to file */
int sc_memorySave(char* filename)
{
	FILE *file = fopen(filename, "w");
	if (!file) 
	{
		return OPEN_FILE_ERROR;
	}

	size_t writeSize = fwrite(memory, sizeof(int), MEMORY_LENGTH, file);
	if (!writeSize)
	{
		return WRITE_FILE_ERROR;
	}

	fclose(file);
	return OK;
}

/* Load memory buffer from file */
int sc_memoryLoad(char* filename) 
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		return OPEN_FILE_ERROR;
	}

	sc_memoryInit();
	size_t readSize = fread(memory, sizeof(int), MEMORY_LENGTH, file);
	if (!readSize)
	{
		return READ_FILE_ERROR;
	}

	fclose(file);
	return OK;
}

/* Initialize register flag */
int sc_regInit()
{
	register_flags = 0;
	return OK;
}

/* Set value for register */
int sc_regSet(int reg, int value)
{
	if (!(reg >= 0 && reg < 4))
	{
		return WRONG_FLAG_ERROR;
	}

	switch (value)
	{
	case 1:
		register_flags |= reg;
		break;
	case 0:
		register_flags &= ~reg;
		break;
	default:
		return WRONG_VALUE_FOR_REGISTER_ERROR;
	}

	return OK;
}

/* Get register value */
int sc_regGet(int reg, int* value) 
{
	if (!(reg >= 0 && reg <= 5))
	{
		return WRONG_FLAG_ERROR;
	}

	*value = (register_flags & reg) > 0 
		? 1 
		: 0;

	return OK;
}

/* Encode command */
int sc_commandEncode(int command, int operand, int* value) 
{
	if (command >= 10 && command <= 76)
	{
		if (operand >= 0 && operand < 128)
		{
			*value = (command << 7) | operand;
		}
		else
		{
			return INVALID_OPERAND;
		}
	}
	else
	{
		sc_regSet(FLAG_COMMAND, 1);
		return INVALID_COMMAND;
	}

	return OK;
}

/* Decode command */
int sc_commandDecode(int* command, int* operand, int value)
{
	*command = (value >> 7);
	*operand = value & (~(*command << 7));

	if (*command >= 10 && *command <= 76) 
	{
		if (*operand >= 0 && *operand <= 128)
		{
			return OK;
		} 
		else
		{
			return INVALID_OPERAND;
		}
	}
	else 
	{
		sc_regSet(FLAG_COMMAND, 1);
		return INVALID_COMMAND;
	}
}