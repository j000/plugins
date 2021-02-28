#ifndef PLUGIN_HPP
#define PLUGIN_HPP

extern "C" {
#include "plugin.h"
}
#include <string>

class Plugin {
	Plugin_t* m_plugin;

	void* m_handle;
	Plugin_t* (*m_create)();
	void (*m_destroy)(Plugin_t*);
	void (*m_test)(Plugin_t*);
	char* (*m_name)(Plugin_t*);

public:
	Plugin(std::string);
    ~Plugin();
    void test();
    std::string name() const;
};

#endif /* PLUGIN_HPP */
