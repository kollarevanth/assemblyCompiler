#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include"allocations.h"
#include"loadingIntoMemory.h"
#include"artithematic.h"
#include"generateInstructions.h"
#include"ExecutingObjectFile.h"


void writeIntoFile(struct intermediateLanguage **tl, int insCount)
{
	FILE *fp;
	fp = fopen("IntermediateCode.obj", "w");
	int i=0;
	while (i < insCount)
	{
		fprintf(fp, "%d,%d,%d,%d,%d,%d,%d\n", tl[i]->insNo, tl[i]->opCode, tl[i]->p1, tl[i]->p2, tl[i]->p3, tl[i]->p4, tl[i]->isConstant);
		i++;
	}
	fclose(fp);
}
int isConstant(char *name, struct symbolTable **symboltable)
{
	int i;
	if (index(name, "X") >= 0)
		return 0;
	for (i = 0; index(symboltable[i]->variable, name) == -1; i++)
	{
	}
	if (symboltable[i]->isconstant>-1)
		return 1;
	else
		return 0;
}
int getConstant(char *name, struct symbolTable **symboltable)
{
	int i;
	for (i = 0; index(symboltable[i]->variable, name) == -1; i++)
	{
	}
	if (symboltable[i]->isconstant != -1)
		return symboltable[i]->isconstant;
}
void main()
{
	int *memory = (int *)malloc(sizeof(int) * 1000);
	struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
	stack->top = -1; stack->labels = NULL;
	int *registerCodes = (int *)malloc(sizeof(int) * 8);
	struct symbolTable **symboltable=NULL;
	struct intermediateLanguage **targetLanguage= NULL;
	struct labelTable **labelslist = NULL;
	int symbolCount = 0, insCount = 0,memIndex=0,labelsCount=0,numberOfInts=0;
	char instruction[100];
	FILE *fp = fopen("sourceCode.txt", "r");
	while (fgets(instruction,100,fp)!=EOF)
	{
		char *instruction1 = getName(instruction);
		instruction[strlen(instruction) - 1] = '\0';
		if (index(instruction, "ENDIF") != 0&&index(instruction, "END") >= 0)
			goto out;
		if (index(instruction, "START") >= 0)
			continue;
		if (index(instruction, "DATA") >= 0)
		{
			symboltable = (struct symbolTable **)realloc(symboltable, sizeof(struct symbolTable *)*(symbolCount + 1));
			allocateVariable(instruction, symbolCount, symboltable, &numberOfInts);
			symbolCount++;
		}
		else if (index(instruction, "CONST") >= 0)
		{
			symboltable = (struct symbolTable **)realloc(symboltable, sizeof(struct symbolTable *)*(symbolCount + 1));
			allocateConstant(instruction, symboltable, symbolCount, memory, &memIndex, &numberOfInts);
			symbolCount++;

		}
		else if (index(instruction, ":") >= 0 || index(instruction, "ELSE") >= 0 || index(instruction, "ENDIF") >= 0)
		{
			labelslist = (struct labelTable **)realloc(labelslist, sizeof(struct labelTable *)*(labelsCount + 1));
			loadintoLabels(instruction, labelslist, labelsCount,insCount,targetLanguage,stack);
			labelsCount++;
		}
		if (index(instruction, ":") >= 0)
			return;
		else if (index(instruction, "DATA") == -1 && index(instruction, "CONST") == -1 && index(instruction, "END") == -1  && index(instruction1, ":")==-1)
		{
			targetLanguage = (struct intermediateLanguage **)realloc(targetLanguage, sizeof(struct intermediateLanguage *)*(insCount + 1));
			
			loadintoInstructionTable(instruction, targetLanguage, insCount, symboltable, labelslist,stack);
			if (index(instruction,"MOV")>=0&&(isConstant(getName(instruction + index(instruction, ",") + 1),symboltable) == 1))
			{
				int temp=targetLanguage[insCount]->p2;
				targetLanguage[insCount]->p2 = -1;
				targetLanguage[insCount]->isConstant = getConstant(getName(instruction + index(instruction, ",") + 1), symboltable);
			}
			insCount++;
		}
		
	}
out:
	writeIntoFile(targetLanguage, insCount);
	ExecuteTheObjectFile();
	_getch();
}