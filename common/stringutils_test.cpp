#include "stringutils.h"
#include "test.h"

void stringutils_test()
{
    equal(split("hi->hello"s, "->"s).first, "hi"s);
    equal(split("hi->hello"s, "->"s).second, "hello"s);
    equal(splitv("hi->hello->there->you"s, "->"s)[2], "there"s);
    equal(splitv("hi->hello->there->    you"s, "->"s)[3], "    you"s);
    equal(trim(splitv("hi -> hello -> there ->    you"s, "->"s)[3]), "you"s);
    equal(trimv(splitv("hi -> hello -> there ->    you"s, "->"s))[3], "you"s);
    equal(to_unsigned_long("123"), static_cast<unsigned long>(123));
    equal(between("sfdsfd (abc) sfdsdf", "(", ")"), "abc"s);
    equal(between("sfdsfd (abc) sfdsdf", '(', ')'), "abc"s);
}

int main()
{
    stringutils_test();
    return 0;
}
