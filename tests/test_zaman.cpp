#include <iostream>
#include <cassert>
#include <ctime>
#include "include-class/zaman.hpp"

void test_tkvm_h_v_d() {
    zaman z;

    // Call the function explicitly
    z.tkvm_h_v_d();

    // Verify 'now' is properly set and within reasonable bounds
    time_t current_time = time(0);
    assert(z.now <= current_time);
    assert(z.now >= current_time - 2); // allow small delay

    // Copy to avoid static buffer overwrites just in case
    tm expected_ltm = *localtime(&z.now);

    assert(z.h_rakam_sene == (1900 + expected_ltm.tm_year));
    assert(z.h_rakam_ay == (1 + expected_ltm.tm_mon));
    assert(z.h_rakam_gun_ayin == expected_ltm.tm_mday);
    assert(z.h_rakam_gun_senenin == (1 + expected_ltm.tm_yday));
    assert(z.h_rakam_gun_haftanin == expected_ltm.tm_wday);

    std::cout << "test_tkvm_h_v_d passed!" << std::endl;
}

int main() {
    std::cout << "Running tests..." << std::endl;
    test_tkvm_h_v_d();
    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
