#include <stdio.h>
#include <stdlib.h>


char *bigmas (char *w, int *len)
{
	char *mas;
	int i = 0;
	mas = malloc((*len) * 2);
	while(i < *len)
	{
		mas[i] = w[i];
		i++;
	}
	*len = (*len) * 2;
	free(w);
	w = mas;
	return w;
}


int main()
{
	char *word;
	char c;
	int len = 8;
	int i = 0;
	word = malloc(len * sizeof(*word));
	while ((c = getchar()) != EOF){
		if (c == '\n')
			break;
		i++;
		if (i > len - 1){
			word = bigmas(word, &len);
		}
		word[i - 1] = c;
	}
	word[i + 1]=0;
	printf("Hello, %s!\n", word);
	free(word);
	return 0;
}
