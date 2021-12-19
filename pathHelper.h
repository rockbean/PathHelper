#ifndef PATH_HELPER_H
#define PATH_HELPER_H

#define PATH_LENGTH_MAX 2048

int path_normalize(const char *path, char *output, size_t outsize);
int path_with_prefix(const char *prefix, char *path, char *output, size_t outsize);
int path_append_suffix(const char *suffix, char *path, char *output, size_t outsize);
int path_prev_dir(const char *path, char *dir);
int path_last_component(const char *path, char *last);
#endif