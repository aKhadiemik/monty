#include "monty.h"

stack_t *stack = NULL;

/**
 * execute_instruction - Executes a Monty instruction
 * @opcode: Opcode to execute
 * @line_number: Line number of the opcode
 */
void execute_instruction(char *opcode, unsigned int line_number, FILE *file)
{
	int i, valid_opcode;
	char *line = NULL;
	instruction_t opcodes[] = {
		{"push", m_push},
		{"pall", m_pall},
		{NULL, NULL}
	};

	valid_opcode = 0;

	if (opcode == NULL || opcode[0] == '#')
		return;

	for (i = 0; opcodes[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, opcodes[i].opcode) == 0)
		{
			valid_opcode = 1;
			opcodes[i].f(&stack, line_number);
			break;
		}
	}

	if (!valid_opcode)
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
		free(line);
		fclose(file);
		exit(EXIT_FAILURE);
	}
}

/**
 * free_stack - Frees all nodes in the stack
 */
void free_stack(void)
{
	while (stack != NULL)
	{
		stack_t *tmp = stack;

		stack = stack->next;
		free(tmp);
	}
}

/**
 * process_file - Processes the Monty file
 * @file: Monty file to process
 */
void process_file(FILE *file)
{
	char *line = NULL, *opcode;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");
		execute_instruction(opcode, line_number, file);
	}

	free(line);
	fclose(file);
}

/**
 * main - Entry point
 * @argc: Argument count
 * @argv: Argument vector
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	FILE *file;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	process_file(file);
	free_stack();

	exit(EXIT_SUCCESS);
}

