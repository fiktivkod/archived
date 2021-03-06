
#include <stdio.h>
#include <stdlib.h>
#include "unit.h"
#include "../src/log.h"
#include "../src/path.h"

void test_normalize() {

    char *ptr;

    ptr = path_normalize("usr/", "include/", 0);
    assert(ptr == NULL);

    ptr = path_normalize("/usr/src/", "linux", 0);
    assert_string(ptr, "/usr/src/linux");
    free(ptr);

    ptr = path_normalize("/segment1///segment2//", "segment3", 1);
    assert_string(ptr, "/segment1/segment2/segment3/");
    free(ptr);

    ptr = path_normalize("/stuff/with/ahell/lot/of/slashes/at/the///", "end", 1);
    assert_string(ptr, "/stuff/with/ahell/lot/of/slashes/at/the/end/");
    free(ptr);

    ptr = path_normalize("~", NULL, 0);
    printf("HOME EXPAND: %s\n", ptr);
    free(ptr);

    ptr = path_normalize("~/sub", "file", 0);
    printf("HOME EXPAND2: %s\n", ptr);
    free(ptr);

    ptr = path_normalize("/mnt/cdrom", "keff", 0);
    assert_string(ptr, "/mnt/cdrom/keff");
    free(ptr);
}

void test_mkpath() {

    assert_string(mkpath("%s/%s", "/mnt/", "file"), "/mnt//file");
    assert_string(mkpath("%s/%s%i", "/dev", "tty", 2), "/dev/tty2");
}

void test_isabspath() {

    assert(is_abspath("file") == 0);
    assert(is_abspath("./file") == 0);
    assert(is_abspath(".file") == 0);
    assert(is_abspath("..file") == 0);
    assert(is_abspath("/../relpath") == 0);
    assert(is_abspath("/path/to/file") == 1);
    assert(is_abspath("/ab/xy/.file") == 1);
    assert(is_abspath("/ab/xy/..file") == 1);
    assert(is_abspath("/ab/.xy/file") == 1);
    assert(is_abspath("/ab/..xy/file") ==1);
}

void test_isfile() {

    assert(is_file("t_path.c") == 1);
    assert(is_file("file.dontexists") == 0);
    assert(is_file("../src") == 0);
    assert(is_file("/") == 0);
}

void test_isdir() {

    assert(is_dir("t_path.c") == 0);
    assert(is_dir("../src") == 1);
    assert(is_dir("/") == 1);
}

void test_basename() {

    int i;

    char data[11][2][64] = {
        { "", "." },
        { "/", "/" },
        { "///", "/" },
        { ".", "."},
        { "..", ".." },
        { "../../rel1", "rel1" },
        { "./rel2", "rel2" },
        { "justsomestring", "justsomestring" },
        { "/usr/src/", "src" },
        { "/usr/src///", "src" },
        { "/usr/src/linux-2.6.30-r5/drivers", "drivers" }
    };

    for(i=0; i < 11; i++)
        assert_string(basename_s(data[i][0]), data[i][1]);
}

void test_dirname() {

    int i;
    const char *path = "/one/two/three/four/";

    char data[13][2][64] = {
        { "", "." },
        { "/", "/" },
        { "///", "/" },
        { ".", "."},
        { "..", "." },
        { "../", "." },
        { "../../rel", "../.." },
        { "./rel", "." },
        { "x", "." },
        { "justsomestring", "." },
        { "/usr/src/", "/usr" },
        { "/usr/src///", "/usr" },
        { "/usr/src/linux-2.6.30-r5/drivers", "/usr/src/linux-2.6.30-r5" }
    };

    for(i=0; i < 12; i++)
        assert_string(dirname_s(data[i][0], 0), data[i][1]);

    path = dirname_s(path, 1);
    assert_string(dirname_s(path, 1), "/one/two/");
}

void test_path_isparent() {

    assert(path_isparent("/dir1/dir2/", "/dir1/") != 0);
    assert(path_isparent("/dir1/dir2/", "/dir1") != 0);
    assert(path_isparent("/dir1/dir2/", "/dir") == 0);
    assert(path_isparent("/dir1/dir2/", "/dir1/dir2/sub/") == 0);
    assert(path_isparent("/dir1/dir2/", "/var/") == 0);
}

void test_real_path() {

    const char *p2, *p1;

    p1 = real_path("../test/Makefile");
    assert(p1);
    printf("%s\n", p1);

    p1 = real_path("t_path.c");
    assert(p1);
    p1 = strdup(p1);

    p2 = real_path("./t_path.c");

    assert_string(p1, p2);

    free(p1);
}

int main(int argc, char *argv[]) {

    init_log(LOG_ALL, NULL);

    test_isabspath();
    test_isfile();
    test_isdir();
    test_normalize();
    test_mkpath();
    test_basename();
    test_dirname();
    test_path_isparent();
    test_real_path();

    return 0;
}
