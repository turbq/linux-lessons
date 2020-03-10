#include <stdio.h>
#include "solution.h"

int main()
{
	int *pcnt, cnt=44;
	pcnt = &cnt;
	char str[] = "hello";
	size_t mul = 2;
	int result;
	printf("cnt = %d\nstr = %s\nmul = %d\npcnt addr = %x\npcnt val = %d\n", cnt, str, (int)mul, pcnt, *pcnt);
	result = stringStat(str, mul, pcnt);
	
	printf("result = %d\ncnt = %d\n", result, *pcnt);
	
	return 0;
}
