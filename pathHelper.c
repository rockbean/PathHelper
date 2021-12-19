#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "pathHelper.h"

#define PATH_FUNC_START  do {

#define PATH_FUNC_END   } while(0);

int path_normalize(const char *path, char *output, size_t outsize)
{
    int ret = 0;
PATH_FUNC_START

    if (!path || !output) {
        ret = -1;
        break;
    }

    size_t path_len = strlen(path);
    if (path_len <= 0) {
        ret = -1;
        break;
    }

    bzero(output, outsize);

    char *i_ptr = (char *)path;
    if ((*i_ptr == '~') && (*(i_ptr + 1) == '/')) {
        /* case: ~/xxx/xxx/xxx */
        struct passwd *user = getpwuid(getuid());
        size_t home_len = strlen(user->pw_dir);
        if (!user->pw_dir || !home_len) {
            ret = -1;
            break;
        } else if (outsize < (home_len + path_len - 1)) {
            ret = -1;
            break;
        }
        memcpy(output, user->pw_dir, home_len);
        strncpy(output + home_len, i_ptr + 1, path_len - 1);
        output [outsize - 1] = '\0';
    } else if (*i_ptr != '/') {
        /* case: xxx/xxx/xxx */
        getcwd(output, outsize);
        size_t len = strlen(output);
        if ((len + path_len - 1) > outsize) {
            bzero(output, outsize);
            ret = -1;
            break;
        }
        strncpy(output + len, i_ptr + 1, path_len - 1);
        output[outsize - 1] = '\0';
    } else {
        strcpy(output, path);
    }

    char *slash_dot = NULL;
    while ((slash_dot=strstr(output, "/."))) {
        char *end = slash_dot;
        if (*(slash_dot + 2) == '.' && 
            ((*(slash_dot + 3) == '/') || (*(slash_dot + 3) == '\0'))) {
            /* case /xxx/../ or /xxx/.. */
            while((end != output) && *(--end) != '/');
            if (end == output) {
                strcpy(output, "/");
                break;
            }
            if (*(slash_dot + 3) == '/') {
                strcpy(end, slash_dot + 3);
            } else if (*(slash_dot + 3) == '\0') {
                *end = '\0';
            }
        } else if (*(slash_dot + 2) == '/') {
            /* case /xxx/./ */
            if (*(end + 2) == '\0') {
                strcpy(output, "/");
            } else {
                strcpy(end, end + 2);
            }
        } else if (*(slash_dot + 2) == '\0') {
            /* case /xxx/. */
            if (end == output) {
                strcpy(output, "/");
            } else {
                *end = '\0';
            }
        } else {
            break;
        }
    }

PATH_FUNC_END
    return ret;
}

int path_with_prefix(const char *prefix, char *path, char *output, size_t outsize)
{
    int ret = 0;
PATH_FUNC_START

    if (!prefix || !path || !output) {
        ret = -1;
        break;
    }

    char real_prefix[PATH_LENGTH_MAX] = {0};
    if (path_normalize(prefix, real_prefix, PATH_LENGTH_MAX) < 0) {
        ret = -1;
        break;
    }
    strncpy(output, real_prefix, outsize);
    output[outsize - 1] = '\0';

    char real_path[PATH_LENGTH_MAX] = {0};
    if (path_normalize(path, real_path, PATH_LENGTH_MAX) < 0) {
        ret = -1;
        break;
    } else if (real_path[1] == '\0') {
        break;
    }

    size_t prefix_len = strlen(real_prefix);
    size_t path_len = strlen(real_path);
    if ((prefix_len + path_len) > outsize) {
        ret = -1;
        break;
    }

    strcpy(output + prefix_len, real_path);

PATH_FUNC_END
    return ret;
}

int path_append_suffix(const char *suffix, char *path, char *output, size_t outsize)
{
    int ret = 0;
PATH_FUNC_START

    if (!suffix || !path || !output) {
        ret = -1;
        break;
    }

    char real_path[PATH_LENGTH_MAX] = {0};
    if (path_normalize(path, real_path, PATH_LENGTH_MAX) < 0) {
        ret = -1;
        break;
    }
    strncpy(output, real_path, outsize);
    output[outsize - 1] = '\0';

    char real_suffix[PATH_LENGTH_MAX] = {0};
    if (path_normalize(suffix, real_suffix, PATH_LENGTH_MAX) < 0) {
        ret = -1;
        break;
    } else if (real_suffix[1] == '\0') {
        break;
    }

    size_t suffix_len = strlen(real_suffix);
    size_t path_len = strlen(real_path);
    if ((suffix_len + path_len) > outsize) {
        ret = -1;
        break;
    }

    strcpy(output + path_len, real_suffix);

PATH_FUNC_END
    return ret;
}

int path_prev_dir(const char *path, char *dir)
{
    int ret = 0;
PATH_FUNC_START

    if (!path || !dir) {
        ret = -1;
        break;
    }

    char real_path[PATH_LENGTH_MAX] = {0};
    if (path_normalize(path, real_path, PATH_LENGTH_MAX) < 0) {
        ret = -1;
        break;
    }

    size_t len = strlen(real_path);
    char *end = real_path + len;
    while((end != real_path) && *(--end) != '/');
    if (end == real_path) {
        strcpy(dir, "/");
    } else {
        len =  end - real_path;
        strncpy(dir, real_path, len);
        dir[len] = '\0';
    }

PATH_FUNC_END
    return ret;
}

int path_last_component(const char *path, char *last)
{
    int ret = 0;
PATH_FUNC_START
    if (!path || !last) {
        ret = -1;
        break;
    }

    char real_path[PATH_LENGTH_MAX] = {0};
    if (path_normalize(path, real_path, PATH_LENGTH_MAX) < 0) {
        ret = -1;
        break;
    }

    size_t len = strlen(real_path);
    char *begin = real_path + len;
    while((begin != real_path) && *(--begin) != '/');
    if (*(begin + 1) != '\0') {
        strcpy(last, begin + 1);
    }

PATH_FUNC_END
    return ret;
}