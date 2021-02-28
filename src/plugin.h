#ifndef PLUGIN_H
#define PLUGIN_H

class Plugin {
public:
	virtual ~Plugin(){};
	virtual const char* name() const = 0;
	virtual void test() = 0;
};

extern "C" Plugin* plugin_create();

#define PLUGIN(X) X plugin_tmp{}; Plugin* plugin_create(){return &plugin_tmp;}

#endif /* PLUGIN_H */
