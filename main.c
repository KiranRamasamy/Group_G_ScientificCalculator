#include <stdio.h>

#include <string.h>

char* getDataConsole(FILE* stream)
{
	unsigned int maxlen = 128, size = 128;
	char* bufferMemory = (char*)malloc(maxlen);

	if(bufferMemory != NULL) /* NULL if malloc() fails */
	{
		char ch = EOF;
		int pos = 0;

		
		while((ch = getchar()) != EOF && ch != '\n')
		{
			bufferMemory[pos++] = ch;
			if(pos == size) 
			{
				size = pos + maxlen;
				bufferMemory = (char*)realloc(bufferMemory, size);
			}
		}
		bufferMemory[pos] = '\0';
	}
	return bufferMemory;
}



int main()
{
		
    
    

	char* str = NULL;
	

	
	

   


	str = getDataConsole(stdin);
	printf("%s",str);


	free(str);
	str = NULL;
	return EXIT_SUCCESS;
}