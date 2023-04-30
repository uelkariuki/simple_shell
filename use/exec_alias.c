#include "main.h"

/*sizes*/
#define MAX_ALIAS_COUNT 100
#define MAX_ALIAS_LENGTH 50

/*lets define the variables used in alias*/
alias_t aliases[MAX_ALIAS_COUNT];
int alias_count = 0;
Alias* alias_list = NULL;

void execute_alias(char **args)
{
	int i = 1;
	char *alias_name, *alias_value;
	while (args[i] != NULL)
	{
		char *alias_command = strdup(args[i]);
		if (alias_command == NULL)
		{
			perror("execute_alias: strdup failed");
			exit(EXIT_FAILURE);
		}
		alias_name = strtok(alias_command, "=");
		alias_value = strtok(NULL, "=");
		if (alias_name == NULL || alias_value == NULL)
		{
			fprintf(stderr, "execute_alias: invalid alias command: %s\n", args[i]);
			free(alias_command);
			i++;
			continue;
		}
		if (alias_value[0] == '\'' && alias_value[strlen(alias_value)-1] == '\'')
		{
			alias_value[strlen(alias_value)-1] = '\0';
			alias_value++;
		}
		if (add_alias(alias_name, alias_value, i) != 0)
		{
			fprintf(stderr, "execute_alias: invalid alias command: %s=%s\n", alias_name, alias_value);
		}
		free(alias_command);
		i++;
	}
	add_alias("ls", "ls --color=auto", 0);
	add_alias("la", "ls -al", 0);
}

/*function setting aliases*/
void define_alias(char *name, char *value)
{
	int i;
	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			strcpy(aliases[i].value, value);
			return;
		}
	}

	/*if alias doesnt exist*/
	strcpy(aliases[alias_count].name, name);
	strcpy(aliases[alias_count].value, value);
	alias_count++;

	if (alias_count >= MAX_ALIAS_COUNT)
	{
		printf("alias: too many aliases\n");
	}
}
void print_alias(alias_t alias)
{
	printf("%s='%s'\n", aliases[i].name, aliases[i].value);
}


void print_aliases()
{
	Alias* alias = alias_list;
	while (alias != NULL)
	{
		alias_t alias_struct = { .name = alias->name, .value = alias->value };
		print_alias(alias_struct);
		alias = alias->next;
	}
}
char *get_alias(char *alias_name)
{
	Alias *alias = alias_list;
	while (alias)
	{
		if (strcmp(alias->name, alias_name) == 0)
		{
			return alias->value;
		}
		alias = alias->next;
	}
	return NULL;
}
void add_alias(char* alias_name, char* alias_value, int line_num)
{
	Alias* alias = alias_list;
	while (alias != NULL)
	{
		if (strcmp(alias->name, alias_name) == 0)
		{
			strcpy(alias->value, alias_value);
			alias->line_num = line_num;
			return;
		}
		alias = alias->next;
	}
	Alias* new_alias = malloc(sizeof(Alias));
	strcpy(new_alias->name, alias_name);
	strcpy(new_alias->value, alias_value);
	new_alias->line_num = line_num;
	new_alias->next = alias_list;
	alias_list = new_alias;
}
void free_aliases()
{
	Alias* alias = alias_list;
	while (alias != NULL)
	{
		Alias* next = alias->next;
		free(alias);
		alias = next;
	}
	alias_list = NULL;
}
