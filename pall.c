#include "monty.h"

/**
 * m_pall - prints all the values on the stack
 * @stack: double pointer to the top of the stack
 * @line_number: line number of the instruction
 */
void m_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void)line_number;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
