#include <catch2/catch_test_macros.hpp>
#include "storage.hpp"

TEST_CASE("Storage basic operations") {
    Storage s;

    SECTION("set and get") {
        REQUIRE(s.set("a", "1"));
        auto val = s.get("a");
        REQUIRE(val.has_value());
        REQUIRE(val.value() == "1");
    }

    SECTION("delete key") {
        s.set("b", "2");
        REQUIRE(s.del("b"));
        REQUIRE_FALSE(s.get("b").has_value());
    }

    SECTION("get missing key") {
        REQUIRE_FALSE(s.get("no_key").has_value());
    }
}
