
struct ins
{
	int opcode, p1, p2, p3, p4, isConstant, insNo;
};

void executeInstructions(struct ins **inst,int *mem,int *regs, int noi)
{
	int pc=0;
	while (pc < noi&&pc>=0)
	{
		switch (inst[pc]->opcode)
		{
		case 2:mem[inst[pc]->p1] = regs[inst[pc]->p2]; break;
		case 1:regs[inst[pc]->p1] = (inst[pc]->p2 == -1) ? inst[pc]->isConstant : mem[inst[pc]->p4]; break;
		case 3:regs[inst[pc]->p1] = regs[inst[pc]->p2] + regs[inst[pc]->p3]; break;
		case 4:regs[inst[pc]->p1] = regs[inst[pc]->p2] - regs[inst[pc]->p3]; break;
		case 5:regs[inst[pc]->p1] = regs[inst[pc]->p2] * regs[inst[pc]->p3]; break;
		case 6:pc = inst[pc]->p1 != -1 ? inst[pc]->p1 - 2 : pc;  break;
		case 7:switch (inst[pc]->p3){
		case 8:if (regs[inst[pc]->p1] != regs[inst[pc]->p2])
			pc = inst[pc]->p4 - 1;
			break;
		case 9:if ((regs[inst[pc]->p1] < regs[inst[pc]->p2])==0)
			pc = inst[pc]->p4 - 1; 
			break;
		case 10:if ((regs[inst[pc]->p1] > regs[inst[pc]->p2])==0)
			pc = inst[pc]->p4 - 1; 
			break;
		case 11:if ((regs[inst[pc]->p1] <= regs[inst[pc]->p2])==0)
			pc = inst[pc]->p4 - 1;
			break;
		case 12:if ((regs[inst[pc]->p1] >= regs[inst[pc]->p2])==0)
			pc = inst[pc]->p4 - 1; 
			break;
		}
			   break;
		case 13:printf("%d ", regs[inst[pc]->p1]);
			break;
		case 14:scanf(" %d", &(regs[inst[pc]->p1]));
			break;
		}
		pc++;
	}
}

void ExecuteTheObjectFile()
{
	FILE *fp;
	fp = fopen("IntermediateCode.obj", "r");
	struct ins **ins = NULL;
	ins = (struct ins **)realloc(ins,sizeof(struct ins));
	int regs[8];
	int *mem = (int *)malloc(sizeof(int) * 1000);
	int pc = 0,i=0;
	ins[0] = (struct ins *)malloc(sizeof(struct ins));
	while (fscanf(fp, "%d,%d,%d,%d,%d,%d,%d", &ins[i]->insNo, &ins[i]->opcode, &ins[i]->p1, &ins[i]->p2, &ins[i]->p3, &ins[i]->p4, &ins[i]->isConstant) != EOF)
	{
		i++;
		ins = (struct ins **)realloc(ins, sizeof(struct ins)*(i+1));
		ins[i] = (struct ins *)malloc(sizeof(struct ins));

	}
	executeInstructions(ins,mem,regs, i);

}