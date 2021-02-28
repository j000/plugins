#include "plugin.h"
#include <iostream>

class Foo : public Plugin {
	const char* const m_name = "Foo";

public:
	Foo()
	{
        std::cout << "    " << m_name << " created" << std::endl;
	};
	~Foo()
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

PLUGIN(Foo)
