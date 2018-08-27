

int getParameter1(char *instruction, struct symbolTable **symboltable)
{
	int i;
	char *instruction1 = instruction;
	instruction = getName(instruction + index(instruction, " ")+1);
	if (index(instruction, "X") >= 0)
	{
		instruction[1] = '\0';
		return instruction[0] - 'A';
	}
	for (i = 0; index(instruction, symboltable[i]->variable) == -1;i++)
	{
	}
	if (index(instruction1, "[") >= 0)
		return symboltable[i]->address + getIndex(instruction1);
	return symboltable[i]->address;

}

int getParameter2(char *instruction, struct symbolTable **symboltable)
{
	int i;
	char *instruction1 = instruction;
	instruction = getName(instruction + index(instruction, ",")+1);
	if (index(instruction, "X") >= 0)
	{
		instruction[1] = '\0';
		return instruction[0] - 'A';
	}
	for (i = 0; index(instruction, symboltable[i]->variable) == -1; i++)
	{
	}
	if (index(instruction, "[") >= 0)
		return symboltable[i]->address + getIndex(instruction1);
	return symboltable[i]->address;

}

int getParameter3(char *instruction, struct symbolTable **symboltable)
{
	int i;
	char *instruction1 = instruction;
	for (i = 0; instruction[i] != ','; i++)
	{

	}
	instruction += i + 1;
	instruction = getName(instruction + index(instruction, ",")+1);
	if (index(instruction, "X") >= 0)
	{
		instruction[1] = '\0';
		return instruction[0] - 'A';
	}
	for (i = 0; index(instruction, symboltable[i]->variable) == -1; i++)
	{
	}
	if (index(instruction,"[")>=0)
		return symboltable[i]->address + getIndex(instruction1);
	return symboltable[i]->address;

}
int getOpCode(char *instruction1)
{
	char *instruction = getName(instruction1);
	if (index(instruction, "ADD") >= 0)
		return 3;
	if (index(instruction, "SUB") >= 0)
		return 4;
	if (index(instruction, "MUL") >= 0)
		return 5;
	if (index(instruction, "MOV") >= 0)
	{
		if (index(instruction1, "X") == strlen(instruction1)-1)
			return 2;
		else
			return 1;
	}
	if (index(instruction, "JMP") >= 0)
		return 6;
	if (index(instruction, "IF") >= 0)
		return 7;
	if (index(instruction, "EQ") >= 0)
		return 8;
	if (index(instruction, "LT") >= 0)
		return 9;
	if (index(instruction, "GT") >= 0)
		return 10;
	if (index(instruction, "LTEQ") >= 0)
		return 11;
	if (index(instruction, "GTEQ") >= 0)
		return 12;
	if (index(instruction, "PRINT") >= 0)
		return 13;
	if (index(instruction, "READ") >= 0)
		return 14;
	return 15;
}

void changeInstruction(char *instruction)
{
	int i;
	for (i = 0; instruction[i] != ' '; i++)
	{

	}
	i++;
	for (i = i; instruction[i] != '\0'; i++)
		if (instruction[i] == ' ')
			instruction[i] = ',';
}
int getComparisionOpCode(char *ins)
{
	if (index(ins, "EQ") >= 0)
		return 8;
	if (index(ins, "LT") >= 0)
		return 9;
	if (index(ins, "GT") >= 0)
		return 10;
	if (index(ins, "LTEQ") >= 0)
		return 11;
	if (index(ins, "GTEQ") >= 0)
		return 12;

}

void loadintoInstructionTable(char *instruction, struct intermediateLanguage **targetLanguage, int insCount, struct symbolTable **symboltable, struct labelTabel **labellist,struct stack *stack)
{
	targetLanguage[insCount] = (struct intermediateLanguage *)malloc(sizeof(struct intermediateLanguage));
	clearAll(targetLanguage, insCount);
	targetLanguage[insCount]->insNo = insCount + 1;
	targetLanguage[insCount]->opCode = getOpCode(instruction);
	if (index(instruction, "CONST") >= 0)
		targetLanguage[insCount]->isConstant = 1;
	if (targetLanguage[insCount]->opCode <= 2)
	{
		targetLanguage[insCount]->p1 = getParameter1(instruction, symboltable);
		targetLanguage[insCount]->p2 = getParameter2(instruction, symboltable);
	}
	else if (targetLanguage[insCount]->opCode <=5)
	{
		targetLanguage[insCount]->p1 = getParameter1(instruction, symboltable);
		targetLanguage[insCount]->p2 = getParameter2(instruction, symboltable);
		targetLanguage[insCount]->p3 = getParameter3(instruction, symboltable);
	}
	else if (targetLanguage[insCount]->opCode == 6)
	{
		targetLanguage[insCount]->p1 = getLabel(getName(instruction + strlen("JMP ")),labellist);
	}
	else if (targetLanguage[insCount]->opCode==14)
	{
		targetLanguage[insCount]->p1 = getParameter1(instruction, symboltable);
	}
	else if (targetLanguage[insCount]->opCode == 13)
	{
		targetLanguage[insCount]->p1 = getParameter1(instruction, symboltable);
	}
	else if (targetLanguage[insCount]->opCode==7)
	{
		changeInstruction(instruction);
		targetLanguage[insCount]->p1 = getParameter1(instruction, symboltable);
		targetLanguage[insCount]->p3 = getComparisionOpCode(instruction);
		targetLanguage[insCount]->p2 = getParameter3(instruction, symboltable);
		push(stack,insCount);
	}
	else
	{
		if (index(instruction, "ELSE") == 0)
		{
			targetLanguage[insCount]->opCode = 6;
			push(stack, insCount);
		}
		else if (index(instruction, "ENDI") == 0)
		{
			targetLanguage[insCount]->opCode = 6;
			targetLanguage[pop(stack)]->p1 = insCount+1;
		}
	}
}