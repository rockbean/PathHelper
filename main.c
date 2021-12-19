#include <stdio.h>
#include <string.h>

#include "pathHelper.h"

void normalize_test(void)
{
    char ret[PATH_LENGTH_MAX] = {0};

    char *test1 = "~/aaa/bbb/ccc";
    path_normalize(test1, ret, PATH_LENGTH_MAX);
    printf("1... %s => %s\n", test1, ret);

    char *test2 = "./aaa/bbb/ccc";
    path_normalize(test2, ret, PATH_LENGTH_MAX);
    printf("2... %s => %s\n", test2, ret);

    char *test3 = "~/aa/./bb";
    path_normalize(test3, ret, PATH_LENGTH_MAX);
    printf("3... %s => %s\n", test3, ret);

    char *test4 = "././aa/.";
    path_normalize(test4, ret, PATH_LENGTH_MAX);
    printf("4... %s => %s\n", test4, ret);


    char *test5 = "/././.";
    path_normalize(test5, ret, PATH_LENGTH_MAX);
    printf("5... %s => %s\n", test5, ret);

    char *test6 = "./../aa";
    path_normalize(test6, ret, PATH_LENGTH_MAX);
    printf("6... %s => %s\n", test6, ret);

    char *test7 = "/aa/..";
    path_normalize(test7, ret, PATH_LENGTH_MAX);
    printf("7... %s => %s\n", test7, ret);

    char *test8 = "./../../../../../../..";
    path_normalize(test8, ret, PATH_LENGTH_MAX);
    printf("8... %s => %s\n", test8, ret);

    char *test9 = "./.aa.txt";
    path_normalize(test9, ret, PATH_LENGTH_MAX);
    printf("9... %s => %s\n", test9, ret);

    char *test10 = "./.....aa.txt";
    path_normalize(test10, ret, PATH_LENGTH_MAX);
    printf("10... %s => %s\n", test10, ret);
}

void prev_dir_test(void)
{
    char ret[PATH_LENGTH_MAX] = {0};
    char *test1 = "./aa/bb/cc";
    path_prev_dir(test1, ret);
    printf("1... %s => %s\n", test1, ret);

    char *test2 = "./aa/bb/.";
    path_prev_dir(test2, ret);
    printf("2... %s => %s\n", test2, ret);
}

void path_last_test(void)
{
    char ret[PATH_LENGTH_MAX] = {0};
    char *test1 = "./.";
    bzero(ret, PATH_LENGTH_MAX);
    path_last_component(test1, ret);
    printf("1... %s => %s\n", test1, ret);

    char *test2 = "./..";
    bzero(ret, PATH_LENGTH_MAX);
    path_last_component(test2, ret);
    printf("2... %s => %s\n", test2, ret);

    char *test3 = "/.";
    bzero(ret, PATH_LENGTH_MAX);
    path_last_component(test3, ret);
    printf("3... %s => %s\n", test3, ret);

    char *test4 = "/..";
    bzero(ret, PATH_LENGTH_MAX);
    path_last_component(test4, ret);
    printf("4... %s => %s\n", test4, ret);

    char *test5 = "/aa/bb/cc";
    bzero(ret, PATH_LENGTH_MAX);
    path_last_component(test5, ret);
    printf("5... %s => %s\n", test5, ret);
}

void path_suffix_test(void)
{
    char ret[PATH_LENGTH_MAX] = {0};
    char *test1 = "~/..";
    char *suffix1 = "./bb/..";
    bzero(ret, PATH_LENGTH_MAX);
    path_append_suffix(suffix1, test1, ret, PATH_LENGTH_MAX);
    printf("1... %s + %s => %s\n", test1, suffix1, ret);

    char *test2 = "/.";
    char *suffix2 = "/.";
    bzero(ret, PATH_LENGTH_MAX);
    path_append_suffix(suffix2, test2, ret, PATH_LENGTH_MAX);
    printf("2... %s + %s => %s\n", test2, suffix2, ret);
}

void path_prefix_test(void)
{
    char ret[PATH_LENGTH_MAX] = {0};
    char *prefix1 = "~/..";
    char *test1 = "./bb/..";
    bzero(ret, PATH_LENGTH_MAX);
    path_with_prefix(prefix1, test1, ret, PATH_LENGTH_MAX);
    printf("1... %s + %s => %s\n", prefix1, test1, ret);

    char *prefix2 = "/.";
    char *test2 = "/.";
    bzero(ret, PATH_LENGTH_MAX);
    path_with_prefix(prefix2, test2, ret, PATH_LENGTH_MAX);
    printf("2... %s + %s => %s\n", prefix2, test2, ret);
}

int main(int argc, char *argv[])
{
    normalize_test();

    prev_dir_test();

    path_last_test();

    path_suffix_test();

    path_prefix_test();
    return 0;
}