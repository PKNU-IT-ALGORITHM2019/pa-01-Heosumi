#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WORD 200000
#define MAX 20000
#pragma warning(disable:4996)

char *diction[WORD];
int size = 0;

int read_line(FILE *fp, char str[], int n)
{
	int i = 0;
	int ch = fgetc(fp);
	while (ch != '\n'&& ch != EOF)
	{
		if (i < n)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void read(char *a)
{
	int i = 0;
	char b[MAX];
	FILE *fp;
	fopen_s(&fp, a, "r");
	if (fp == NULL)
	{
		printf("fail\n");
		exit(1);
	}
	else
		printf("success\n");

	while (!feof(fp))
	{
		read_line(fp, b, MAX);
		if (strcmp(_strdup(b), "\0") != 0)
		{
			diction[i] = _strdup(b);
			i++;
			size++;
		}
	}
	fclose(fp);
}

int find(int begin,int end, char *target)
{
	int middle = (begin + end) / 2;
	char word[MAX];
	int i = 0, count = 0;

	while (diction[middle][i] != '(')
	{
		word[i] = diction[middle][i];
		i++;
	}
	word[i] = '\0';
	i = 0;

	if (strcmp(target, word) < 0)
		return find(begin, middle - 1, target);
	else if (strcmp(target, word) == 0)
	{
		while (strcmp(target, word) == 0)
		{
			count++;
			while (diction[middle + count][i] != '(')
			{
				word[i] = diction[middle + count][i];
				i++;
			}
			word[i] = '\0';
			i = 0;
		}
		printf("Found %d items.\n", count);

		for (int j = 0; j < count; j++)
		{
			printf("%s\n", diction[middle++]);
		}
		return middle;
	}
	else
		return find(middle + 1, end, target);
}

int main()
{
	char f[MAX];
	char *buf1, *buf2;
	while (1)
	{
		printf("$ ");
		buf1 = strtok(f, "\0");
		if (strcmp(buf1, "read") == 0)
		{
			buf2 = strtok(NULL, "\0");
			if (buf2 == NULL)
				continue;
			read(buf2);
		}
		else if (strcmp(buf1, "find") == 0)
		{
			buf2 = strtok(NULL, "\0");
			find(0, size - 1, buf2);
		}
		else if (strcmp(buf1, "size") == 0)
			printf("%d\n", size);
		else if (strcmp(buf1, "exit") == 0)
			exit(1);
		else
			printf("error\n");
	}
	return 0;
}