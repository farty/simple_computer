#include "stdio.h"

#define MEMORY_LENGTH 100

int memory[MEMORY_LENGTH];

int register_flags;

/* register flags */

#define FLAG_OVERFLOW 0
#define FLAG_DIVISION 1
#define FLAG_OUT_OF_MEMORY 2
#define FLAG_INTERRUPT 3
#define FLAG_COMMAND 4
#define FLAG_ODD 5

/* return codes */

#define OK 0x00

#define OUT_OF_RANGE_ERROR 0x10

#define WRONG_FLAG_ERROR 0x20
#define WRONG_VALUE_FOR_REGISTER_ERROR 0x21

#define OPEN_FILE_ERROR 0x40
#define READ_FILE_ERROR 0x41
#define WRITE_FILE_ERROR 0x42

#define INVALID_COMMAND 0x50
#define INVALID_OPERAND 0x51

/* Initialize memory array */
int sc_memoryInit();

/* Set value to memory by address */
int sc_memorySet(int address, int value);

/* Get value from memroy by address */
int sc_memoryGet(int address, int* value);

/* Save memory buffer to file */
int sc_memorySave(char* filename);

/* Load memory buffer from file */
int sc_memoryLoad(char* filename);

/* Initialize register flag */
int sc_regInit();

/* Set value for register */
int sc_regSet(int reg, int value);

/* Get register value */
int sc_regGet(int reg, int* value);

/* Encode command */
int sc_commandEncode(int command, int operand, int* value);

/* Decode command */
int sc_commandDecode(int* command, int* operand, int value);