extern "C" {
#include "plugin.h"
}
#include "Plugin.hpp"
#include <dlfcn.h>
#include <stdexcept>

Plugin::Plugin(const std::string name)
{
	if (!(m_handle = dlopen(name.c_str(), RTLD_NOW))) {
		throw std::runtime_error(dlerror());
	}

	if (!(m_create = reinterpret_cast<decltype(m_create)>(
			  dlsym(m_handle, "plugin_create")))) {
		throw std::runtime_error("Could not find plugin_create in " + name);
	}

	if (!(m_destroy = reinterpret_cast<decltype(m_destroy)>(
			  dlsym(m_handle, "plugin_destroy")))) {
		throw std::runtime_error("Could not find plugin_destroy in " + name);
	}

	if (!(m_name = reinterpret_cast<decltype(m_name)>(
			  dlsym(m_handle, "plugin_name")))) {
		throw std::runtime_error("Could not find plugin_name in " + name);
	}

	if (!(m_test = reinterpret_cast<decltype(m_test)>(
			  dlsym(m_handle, "plugin_test")))) {
		throw std::runtime_error("Could not find plugin_test in " + name);
	}

	m_plugin = m_create();
	if (!m_plugin)
		throw std::runtime_error("Creating " + name + " failed");
}

Plugin::~Plugin()
{
	m_destroy(m_plugin);
	dlclose(m_handle);
}

void Plugin::test()
{
	m_test(m_plugin);
}

std::string Plugin::name() const
{
	return std::string{m_name(m_plugin)};
}
