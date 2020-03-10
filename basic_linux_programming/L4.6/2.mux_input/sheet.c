#include <stdio.h>

int main()
{
	FILE *fp1,*fp2;
	char *num1 = "93\0", *num2 = "3\0";

	fp1 = fopen("./in1","w");
	fp2 = fopen("./in2","w");
	fprintf(fp1,"%s",num1);
	fprintf(fp2,"%s",num2);

	return 0;
}
