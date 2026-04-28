#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../include/include-class/Zaman.hpp"

TEST_CASE("zaman constructor and basic operations", "[zaman]") {
    SECTION("Construct zaman object") {
        zaman z;

        // Check that time values are within valid ranges
        REQUIRE(z.saat >= 0);
        REQUIRE(z.saat < 24);
        REQUIRE(z.dakika >= 0);
        REQUIRE(z.dakika < 60);
        REQUIRE(z.saniye >= 0);
        REQUIRE(z.saniye < 60);

        REQUIRE(z.h_saat >= 0);
        REQUIRE(z.h_saat < 24);
        REQUIRE(z.h_dakika >= 0);
        REQUIRE(z.h_dakika < 60);
        REQUIRE(z.h_saniye >= 0);
        REQUIRE(z.h_saniye < 60);

        // Check that calendar values are logical
        REQUIRE(z.h_rakam_sene >= 1900); // Because it is 1900 + ltm->tm_year
        REQUIRE(z.h_rakam_ay >= 1);
        REQUIRE(z.h_rakam_ay <= 12);

        // Check that prayer time strings are populated
        REQUIRE(!z.h_imsak.empty());
        REQUIRE(!z.h_sabah.empty());
        REQUIRE(!z.h_gunes.empty());
        REQUIRE(!z.h_ogle.empty());
        REQUIRE(!z.h_ikindi.empty());
        REQUIRE(!z.h_aksam.empty());
        REQUIRE(!z.h_yatsi.empty());

        REQUIRE(!z.imsak.empty());
        REQUIRE(!z.sabah.empty());
        REQUIRE(!z.gunes.empty());
        REQUIRE(!z.ogle.empty());
        REQUIRE(!z.ikindi.empty());
        REQUIRE(!z.aksam.empty());
        REQUIRE(!z.yatsi.empty());
    }
}
