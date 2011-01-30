
#include <assert.h>
#include <stdlib.h>
#include "../src/inotify-map.h"

int   wdref[4]   = { 1, 2, 1, 4 };
char *pathref[4] = { "one", "two", "three", "four" };

static void setup() {

    int i;

    if (!inotify_map_isempty())
        return;

    for(i=0; i < 4; i++)
        inotify_map(wdref[i], pathref[i]);
}

static void teardown() {

    inotify_unmap_all();
}

static void validate_list(int index, char **list) {

    int i;

    assert(list);

    for(i=0; i < 4; i++) {
        char **path, found = 0;

        if (i != wdref[index])
            continue;

        for(path=list; !found && *path; path++) {
            if (!strcmp(*path, pathref[index]))
                found = 1;
        }
        assert(found);
    }
}

void test_inotify_unmap_wd() {

    int i;

    setup();

    assert(inotify_unmap_wd(wdref[0]));
    assert(inotify_unmap_wd(wdref[1]));
    assert(inotify_unmap_wd(wdref[2]) == 0);
    assert(inotify_unmap_wd(wdref[3]));

    assert(inotify_map_isempty());

    teardown();
}

void test_inotify_unmap_path() {

    int i;

    setup();

    for(i=0; i < 4; i++)
        assert(inotify_unmap_path(pathref[i]));

    assert(inotify_map_isempty());

    teardown();
}

void test_inotify_unmap_all() {

    setup();
    
    inotify_unmap_all();
    assert(inotify_map_isempty());

    teardown();
}

void test_inotify_map_get_wd() {

    int i;

    setup();
    
    for(i=0; i < 4; i++)
        assert(inotify_map_get_wd(pathref[i]) == wdref[i]);

    teardown();
}

void test_inotify_map_lookup() {

    int i;

    setup();

    for(i=0; i < 4; i++)
        validate_list(i, inotify_map_lookup(wdref[i]));

    assert(inotify_map_lookup(25) == NULL);
    
    teardown();
}

void test_inotify_map_lookup_by_path() {

    int i;

    setup();
    
    for(i=0; i < 4; i++)
        validate_list(i, inotify_map_lookup_by_path(pathref[i]));

    assert(inotify_map_lookup_by_path("do not exist") == NULL);
    
    teardown();
}

int main() {

    test_inotify_unmap_wd();
    test_inotify_unmap_path();
    test_inotify_unmap_all();
    test_inotify_map_get_wd();
    test_inotify_map_lookup();
    test_inotify_map_lookup_by_path();
    
    return 0;
}
