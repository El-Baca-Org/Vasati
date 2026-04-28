#include "include-class/Zaman.hpp"
#include <cassert>
#include <iostream>
#include <string>

#define ASSERT_EQUAL(actual, expected) \
    if ((actual) != (expected)) { \
        std::cerr << "Assertion failed: " << #actual << " == " << #expected << " (" << (actual) << " != " << (expected) << ") at " << __FILE__ << ":" << __LINE__ << std::endl; \
        exit(1); \
    }

void test_vkt_turk_v_d_calculations() {
    std::cout << "Running test_vkt_turk_v_d_calculations..." << std::endl;
    zaman z;

    // Clear any strings set by constructor
    z.aksam = "";
    z.istibak_nucum = "";
    z.yatsi = "";
    z.isa_sani = "";
    z.imsak = "";
    z.sabah = "";
    z.gunes = "";
    z.israk = "";
    z.kerahet = "";
    z.ogle = "";
    z.ikindi = "";
    z.asr_sani = "";
    z.isfirar_sems = "";
    z.kible_saati = "";

    // Set inputs
    z.h_aksam_td = 1110; // 18:30
    z.h_istibak_nucum_td = 1185; // 19:45
    z.h_yatsi_td = 1200; // 20:00
    z.h_isa_sani_td = 1260; // 21:00
    z.h_imsak_td = 245; // 04:05
    z.h_sabah_td = 300; // 05:00
    z.h_gunes_td = 390; // 06:30
    z.h_israk_td = 435; // 07:15
    z.h_kerahet_td = 480; // 08:00
    z.h_ogle_td = 750; // 12:30
    z.h_ikindi_td = 960; // 16:00
    z.h_asr_sani_td = 1020; // 17:00
    z.h_isfirar_sems_td = 1080; // 18:00
    z.h_kible_saati_td = 600; // 10:00

    z.vkt_turk_v_d();

    // istibak_nucum_td = 1185 - 1110 = 75 mins -> 1:15
    ASSERT_EQUAL(z.istibak_nucum, "1:15");

    // imsak_td = (1440 - 1110) + 245 = 330 + 245 = 575 mins -> 9:35
    ASSERT_EQUAL(z.imsak, "9:35");

    std::cout << "test_vkt_turk_v_d_calculations passed!" << std::endl;
}

void test_vkt_turk_v_d_zero_padding() {
    std::cout << "Running test_vkt_turk_v_d_zero_padding..." << std::endl;
    zaman z;

    // Clear strings
    z.istibak_nucum = "";

    // Set inputs to result in single digit minutes
    z.h_aksam_td = 1110; // 18:30
    z.h_istibak_nucum_td = 1175; // 19:35
    // 19:35 - 18:30 = 65 mins -> 1:05

    z.vkt_turk_v_d();

    // This is expected to fail currently, it will likely be "1:5"
    ASSERT_EQUAL(z.istibak_nucum, "1:05");

    std::cout << "test_vkt_turk_v_d_zero_padding passed!" << std::endl;
}

void test_vkt_turk_v_d_cumulative() {
    std::cout << "Running test_vkt_turk_v_d_cumulative..." << std::endl;
    zaman z;

    z.aksam = "";
    z.istibak_nucum = "";
    // ... ignoring others for brevity, just testing one

    z.h_aksam_td = 1110;
    z.h_istibak_nucum_td = 1185;

    z.vkt_turk_v_d();
    ASSERT_EQUAL(z.istibak_nucum, "1:15");

    z.vkt_turk_v_d();
    // This is expected to fail currently, it will likely be "1:151:15" due to .append()
    ASSERT_EQUAL(z.istibak_nucum, "1:15");

    std::cout << "test_vkt_turk_v_d_cumulative passed!" << std::endl;
}

int main() {
    test_vkt_turk_v_d_calculations();
    test_vkt_turk_v_d_zero_padding();
    test_vkt_turk_v_d_cumulative();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
