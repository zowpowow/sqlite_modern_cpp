#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sqlite_modern_cpp.h>
#include <catch.hpp>
using namespace  sqlite;
using namespace std;

TEST_CASE("simple examples", "[examples]") {
    database db(":memory:");

    db << "CREATE TABLE foo (a integer, b string);\n";
    db << "INSERT INTO foo VALUES (?, ?)" << 1 << "hello";
    db << "INSERT INTO foo VALUES (?, ?)" << 2 << "world";

    string str;
    db << "SELECT b from FOO where a=?;" << 2L >> str;

    REQUIRE(str == "world");

    std::string sql("select 1+1");
    long test = 0;
    db << sql >> test;

    REQUIRE(test == 2);

}
