void addValues(char *instruction, int *registerCodes)
{
	char *a, *b, *c;
	a = getName(instruction + strlen("ADD "));
	b = getName(instruction + strlen("ADD ") + strlen(a) + 1);
	c = getName(instruction + strlen("ADD ") + strlen(a) + strlen(b) + 2);
	registerCodes[a[0] - 'A'] = registerCodes[b[0] - 'A'] + registerCodes[c[0] - 'A'];
}
void subValues(char *instruction, int *registerCodes)
{
	char *a, *b, *c;
	a = getName(instruction + strlen("ADD "));
	b = getName(instruction + strlen("ADD ") + strlen(a) + 1);
	c = getName(instruction + strlen("ADD ") + strlen(a) + strlen(b) + 2);
	registerCodes[a[0] - 'A'] = registerCodes[b[0] - 'A'] - registerCodes[c[0] - 'A'];
}
void mulValues(char *instruction, int *registerCodes)
{
	char *a, *b, *c;
	a = getName(instruction + strlen("ADD "));
	b = getName(instruction + strlen("ADD ") + strlen(a) + 1);
	c = getName(instruction + strlen("ADD ") + strlen(a) + strlen(b) + 2);
	registerCodes[a[0] - 'A'] = registerCodes[b[0] - 'A'] * registerCodes[c[0] - 'A'];
}

