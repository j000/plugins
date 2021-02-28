extern "C" {
#include "plugin.h"
}
#include <iostream>

struct Plugin_t {
private:
	const char* const m_name = "foo";

public:
	Plugin_t()
	{
		std::cout << "    " << m_name << " created" << std::endl;
	};
	virtual ~Plugin_t()
	{
		std::cout << "    " << m_name << " destroyed" << std::endl;
	};
	virtual const char* name() const
	{
		return m_name;
	}
	virtual void test()
	{
		std::cout << "    " << m_name << " tested" << std::endl;
	};
};

Plugin_t* plugin_create(void)
{
	Plugin_t* tmp = new Plugin_t{};
	return tmp;
}

void plugin_destroy(Plugin_t* plug)
{
	delete plug;
}

void plugin_test(Plugin_t* plug)
{
	plug->test();
}

const char* plugin_name(Plugin_t* plug)
{
	return plug->name();
}
