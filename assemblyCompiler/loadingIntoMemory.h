void loadIntoMemory(char *instruction, struct symbolTable **symboltable, int symbolCount,int *memory, int *memCount,int *regs)
{
	char *symbol = getName(instruction + strlen("READ") + 1);
	char num[100];
	int input;
	gets(num);
	input = changeToInt(num);
	int i;
	for (i = 0; i < symbolCount; i++)
	{
		if (index(symboltable[i]->variable, symbol) == 0)
		{
			if (index(instruction, "[") >= 0)
			{
				int j;
				instruction[strlen(instruction) - 1] = '\0';
				j = changeToInt(getName(instruction + strlen("READ") + strlen(symboltable[i]->variable) + 2));
				memory[symboltable[i]->address + j] = input;
			}
			else
				memory[symboltable[i]->address] = input;
			return;
		}

	}
	if (i == symbolCount)
	{
		symbol[1] = '\0';
		regs[symbol[0] - 'A'] = input;
		
	}
}
int getIndex(char *ins)
{
	int i,sum=0;
	for (i = 0; ins[i] != '['; i++)
	{

	}
	i += 1;
	for (i; ins[i] != ']'; i++)
		sum = sum * 10 + (ins[i] - '0');
	return sum;
}
void transferContent(char *instruction, struct symbolTable **symboltable,int symbolCount, int *memory, int *registerCodes)
{
	int i;
	if (index(instruction, "X") != strlen(instruction) - 1)
	{
		for (i = 0; i < symbolCount; i++)
		{
			if (index(instruction, symboltable[i]->variable) >= 0)
			{
				char *regs = getName(instruction + strlen("MOV "));
				regs[strlen(regs) - 1] = '\0';
				registerCodes[regs[0] - 'A'] = memory[symboltable[i]->address + getIndex(instruction)];
			}
		}
	}
	else
	{
		for (i = 0; i < symbolCount; i++)
		{
			if (index(instruction, symboltable[i]->variable) >= 0)
			{
				char *regs = getName(instruction + strlen("MOV "));
				regs[strlen(regs) - 1] = '\0';
				memory[symboltable[i]->address + getIndex(instruction)] = registerCodes[regs[0] - 'A'];
			}
		}
	}
}
int getLabel(char *label, struct labelTable **labellist)
{
	int i;
	for (i = 0; index(label, labellist[i]->label) == -1; i++)
	{}
	return labellist[i]->address;
}
void push(struct stack *stack, int element)
{
	int t = stack->top+1;
	stack->top += 1;
	stack->labels = (int *)realloc(stack->labels, sizeof(int)*(t + 1));
	stack->labels[t] = element;
}
int pop(struct stack *stack)
{
	stack->top -= 1;
	return stack->labels[stack->top + 1];
}
void loadintoLabels(char *instruction, struct labelTable **labelsList, int labelCount,int insCount,struct intermediateLanguage **targetlanguage,struct stack *stack)
{
	labelsList[labelCount] = (struct labelTable *)malloc(sizeof(struct labelTable));
	if (index(instruction, "ELSE") == 0)
	{
		targetlanguage[pop(stack)]->p4 = insCount + 1;
	}
	else if (index(instruction, "ENDIF") == 0)
	{
		targetlanguage[pop(stack)]->p1 = insCount + 1;
	}
	else
	instruction[strlen(instruction) - 1] = '\0';
	labelsList[labelCount]->label = getName(instruction);
	labelsList[labelCount]->address = insCount + 1;

}