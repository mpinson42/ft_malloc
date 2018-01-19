#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#define M (1024 * 1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = realloc(addr1, 0);
	addr1 = realloc(addr1, 4097);
	return (0);
}
