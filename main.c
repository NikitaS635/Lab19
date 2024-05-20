#include <stdio.h>
#include "C:\Users\User2\CLionProjects\untitled copy\libs\data_structures\string\string_.h"
#include <windows.h>
#include <assert.h>
#include <stdlib.h>
void test2()
{
    char *s = "line";
    assert(string_length(s) == 4);
}
void test3()
{
    char *s = "li\0ne";
    assert(string_length(s) == 2);
}
void test4A()
{
    char s[] = "line";
    char *fi = find(s, s+4, 'n');
    assert(*fi == 'n');
}
void test4B()
{
    char s[] = "line";
    char *h = findNonSpace(s);
    assert(*h == 'l');
}
void test4C()
{
    char s[] = " line";
    char *h = findSpace(s);
    assert(*h == ' ');
}
void test4D()
{
    char s[] = "line";
    char *h = findNonSpaceReverse(s+3, s);
    assert(*h == 'e');
}
void test4E()
{
    char s[] = " line";
    char *h = findSpaceReverse(s+3, s);
    assert(*h == ' ');
}
void test5()
{
    char *s1 = "Li";
    char *s2 = "Li";
    int ms = my_strcmp(s1, s2);
    assert(ms == 0);
    char *s3 = "L";
    char *s4 = "Li";
    int ms2 = my_strcmp(s3, s4);
    assert(ms2 < 0);
    char *s5 = "Li";
    char *s6 = "L";
    int ms3 = my_strcmp(s5, s6);
    assert(ms3 > 0);
}
void test6()
{
    char s[] = "hello";
    char s1[20];
    copy(s, s+5, s1);
    assert(strcmp(s1, "hello") == 0);
}
void alltest()
{
    test2();
    test3();
    test4A();
    test4B();
    test4C();
    test4D();
    test4E();
    test5();
    test6();
    printf("Все тесты пройдены");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    alltest();
    return 0;
}