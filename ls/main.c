#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

static
int strcasecmp_custom(const char *a, const char *b)
{
    for (; *a && *b; ++a, ++b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) return ca - cb;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}
static
int alphasort_nocase(const struct dirent **a, const struct dirent **b)
{
    return strcasecmp_custom((*a)->d_name, (*b)->d_name);
}

int main(int argc, char **argv)
{
    bool show_all = false;
    int opt;
    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                show_all = true;
                break;
            default:
                fprintf(stderr, "usage: %s [-a] [path]\n", argv[0]);
        }
    }
    const char *path = (argc > 1) ? argv[optind] : ".";

    struct dirent **dirlist;
    int n = scandir(path, &dirlist, nullptr, alphasort_nocase);
    if (n == -1) {
        perror("scandir");
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        if (!show_all && dirlist[i]->d_name[0] == '.') goto out;
        printf("%s  ", dirlist[i]->d_name);
    out:
        free(dirlist[i]);
    }
    putc('\n', stdout);
    exit(0);
}