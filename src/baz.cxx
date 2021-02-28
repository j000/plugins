#include "plugin.h"
#include <iostream>

class Baz : public Plugin {
	const char* const m_name = "Baz";

public:
	Baz()
	{
        std::cout << "    " << m_name << " created" << std::endl;
	};
	~Baz()
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

PLUGIN(Baz)
