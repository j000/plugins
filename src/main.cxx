#include "Plugin.hpp"
#include <dlfcn.h>
#include <iostream>
#include <memory>
#include <vector>

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " plugins_to_use.so" << std::endl;
		return -1;
	}

	std::vector<std::unique_ptr<Plugin>> plugins{};

	for (int i = 1; i < argc; ++i) {
		try {
			plugins.emplace_back(new Plugin(argv[i]));
		} catch (const std::runtime_error& e) {
			std::cout << argv[i] << ": " << e.what() << std::endl;
		}
	}
	std::cout << "Using plugins" << std::endl;

	// use
	for (auto& plugin : plugins) {
		std::cout << plugin->name() << std::endl;
		plugin->test();
	}
	for (auto& plugin : plugins) {
		std::cout << plugin->name() << std::endl;
		plugin->test();
	}

	std::cout << "Done" << std::endl;
	return 0;
}
