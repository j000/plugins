extern "C" {
#include "plugin.h"
}
#include <iostream>

struct Plugin_t {
	std::string name{};
};

Plugin_t* plugin_create(void)
{
	std::cout << "    baz created" << std::endl;
	auto tmp = new Plugin_t();
	tmp->name = "baz";
	return tmp;
}

void plugin_destroy(Plugin_t* plug)
{
	std::cout << "    baz destroyed" << std::endl;
	delete plug;
}

void plugin_test(Plugin_t* plug)
{
	static int counter = 0;
	std::cout << "    " << plug->name << " tested " << counter++ << " times"
			  << std::endl;
}

const char* plugin_name(Plugin_t* plug)
{
	return plug->name.c_str();
}
