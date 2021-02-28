#include "plugin.h"
#include <dlfcn.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
	if (argc < 2) {
        std::cout << "Usage: dlopen plugin_to_use.so" << std::endl;
		return -1;
	}

	std::vector<Plugin*> plugins{};
	std::vector<void*> handles{};

	for (int i = 1; i < argc; ++i) {
		void* handle;

		if (!(handle = dlopen(argv[i], RTLD_NOW))) {
            std::cout << dlerror() << std::endl;
			continue;
		}

        Plugin* (*create)();
		if (!(create = reinterpret_cast<decltype(create)>(dlsym(handle, "plugin_create")))) {
            std::cout << "Could not find plugin_create in " << argv[i] << std::endl;
			continue;
		}

		handles.push_back(handle);
		plugins.push_back(create());
	}
	std::cout << "Using plugins" << std::endl;

	// use
	for (const auto& plugin : plugins) {
        std::cout << plugin->name() << std::endl;
		plugin->test();
	}

	std::cout << "Done" << std::endl;

	// cleanup
	for (const auto& handle : handles) {
		dlclose(handle);
	}
	return 0;
}
