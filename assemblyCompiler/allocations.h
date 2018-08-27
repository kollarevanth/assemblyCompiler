struct symbolTable
{
	char *variable;
	int address;
	int size, isconstant;
};
struct labelTable
{
	char *label;
	int address;
};
struct stack
{
	int *labels;
	int top;
};
struct intermediateLanguage
{
	int insNo, opCode;
	int p1, p2, p3, p4,isConstant;
};
void clearAll(struct intermediateLanguage **tar, int insCount)
{
	tar[insCount]->p1 = -1; tar[insCount]->p2 = -1; tar[insCount]->p3 = -1; tar[insCount]->p4 = -1; tar[insCount]->isConstant = -1;
}
int index(char *a, char *b)
{
	int i, j;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == b[0])
		{
			for (j = 0; b[j] != '\0'&&a[i + j] == b[j]; j++)
			{

			}

			if (b[j] == '\0')
				return i;
		}
	}
	return -1;
}

char *getName(char *sentence)
{
	int i = 0;
	char *res = NULL;
	for (i = 0; sentence[i] != '\0'&&sentence[i] != ','&&sentence[i] != '='&&sentence[i] != '['&&sentence[i] != ']'&&sentence[i] != '\0'&&sentence[i] != ' '; i++)
	{
		res = (char *)realloc(res, sizeof(char)*(i + 1));
		res[i] = sentence[i];
	}
	res[i] = '\0';
	return res;
}
int changeToInt(char *number)
{
	int sum = 0;
	for (int i = 0; number[i] != '\0'; i++)
		sum = sum * 10 + (number[i] - '0');
	return sum;
}
void allocateVariable(char *instruction, int symbolCount, struct symbolTable **symboltable,int *numberOfInts)
{
	symboltable[symbolCount] = (struct symbolTable *)malloc(sizeof(struct symbolTable));
	symboltable[symbolCount]->variable = getName(instruction + strlen("DATA "));
	if (index(instruction, "[") >= 0){
		symboltable[symbolCount]->size = changeToInt(getName(instruction + strlen("DATA ") + strlen(symboltable[symbolCount]->variable) + 1));
		instruction[strlen(instruction) - 1] = '\0';
	}
	else
		symboltable[symbolCount]->size = 1;
	symboltable[symbolCount]->address = *numberOfInts;
	symboltable[symbolCount]->isconstant = -1;
	*numberOfInts += symboltable[symbolCount]->size;
}
void allocateConstant(char *instruction, struct symbolTable **symboltable, int symbolCount, int *memory, int *memCount,int *numberOfInts)
{
	symboltable[symbolCount] = (struct symbolTable *)malloc(sizeof(struct symbolTable));
	symboltable[symbolCount]->variable = getName(instruction + strlen("DATA  "));
	symboltable[symbolCount]->size = 1;
	symboltable[symbolCount]->address = *numberOfInts;
	symboltable[symbolCount]->isconstant = changeToInt((getName(instruction+index(instruction,"=")+1)));
	memory[*numberOfInts] = changeToInt(getName(instruction + strlen("DATA  ") + strlen(symboltable[symbolCount]->variable) + 1));
	*numberOfInts += symboltable[symbolCount]->size;

}