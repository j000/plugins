#ifndef PLUGIN_H
#define PLUGIN_H

typedef struct Plugin_t Plugin_t;

extern Plugin_t* plugin_create(void);
extern void plugin_destroy(Plugin_t*);

extern void plugin_test(Plugin_t*);
extern const char* plugin_name(Plugin_t*);

#endif /* PLUGIN_H */
