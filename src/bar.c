#include "plugin.h"
#include <stdio.h>
#include <stdlib.h>

struct Plugin_t {
	char* name;
};

Plugin_t* plugin_create(void)
{
	Plugin_t* tmp = malloc(sizeof(Plugin_t));
	tmp->name = "bar";
	printf("    %s created\n", tmp->name);
	return tmp;
}

void plugin_destroy(Plugin_t* plug)
{
	printf("    %s destroyed\n", plug->name);
	free(plug);
}

void plugin_test(Plugin_t* plug)
{
	static int counter = 0;
	printf("    %s tested %d times\n", plug->name, counter++);
}

const char* plugin_name(Plugin_t* plug)
{
	return plug->name;
}
