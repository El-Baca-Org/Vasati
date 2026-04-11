#include "../include/include-class/Zaman.hpp"
#include <cassert>
#include <iostream>

void test_vkt_turk_v_d_standard() {
    zaman z;

    // Set dummy inputs
    z.h_aksam_td = 1000;

    z.h_istibak_nucum_td = 1060;
    z.h_yatsi_td = 1100;
    z.h_isa_sani_td = 1120;

    z.h_imsak_td = 280;
    z.h_sabah_td = 300;
    z.h_gunes_td = 400;
    z.h_israk_td = 450;
    z.h_kerahet_td = 750;
    z.h_ogle_td = 800;
    z.h_ikindi_td = 1020;
    z.h_asr_sani_td = 1080;
    z.h_isfirar_sems_td = 1140;
    z.h_kible_saati_td = 720;

    // Clear string buffers
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

    z.vkt_turk_v_d();

    // Check computed _td values
    assert(z.aksam_td == 0);
    assert(z.istibak_nucum_td == 1060 - 1000); // 60
    assert(z.yatsi_td == 1100 - 1000); // 100
    assert(z.isa_sani_td == 1120 - 1000); // 120
    assert(z.imsak_td == (1440 - 1000) + 280); // 720
    assert(z.sabah_td == (1440 - 1000) + 300); // 740
    assert(z.gunes_td == (1440 - 1000) + 400); // 840
    assert(z.israk_td == (1440 - 1000) + 450); // 890
    assert(z.kerahet_td == (1440 - 1000) + 750); // 1190
    assert(z.ogle_td == (1440 - 1000) + 800); // 1240
    assert(z.ikindi_td == (1440 - 1000) + 1020); // 1460
    assert(z.asr_sani_td == (1440 - 1000) + 1080); // 1520
    assert(z.isfirar_sems_td == (1440 - 1000) + 1140); // 1580
    assert(z.kible_saati_td == (1440 - 1000) + 720); // 1160

    // Check string formatting
    // 60 -> 1:0
    assert(z.istibak_nucum == "1:0");
    // 100 -> 1:40
    assert(z.yatsi == "1:40");
    // 120 -> 2:0
    assert(z.isa_sani == "2:0");
    // 720 -> 12:0 -> 0:0 mod 12? 720 / 60 = 12. 12 % 12 = 0. So "0:0"
    assert(z.imsak == "0:0");
    // 740 -> 12:20 -> 0:20
    assert(z.sabah == "0:20");
    // 840 -> 14:0 -> 2:0
    assert(z.gunes == "2:0");
    // 890 -> 14:50 -> 2:50
    assert(z.israk == "2:50");
    // 1190 -> 19:50 -> 7:50
    assert(z.kerahet == "7:50");
    // 1240 -> 20:40 -> 8:40
    assert(z.ogle == "8:40");
    // 1460 -> 24:20 -> 0:20
    assert(z.ikindi == "0:20");
    // 1520 -> 25:20 -> 1:20
    assert(z.asr_sani == "1:20");
    // 1580 -> 26:20 -> 2:20
    assert(z.isfirar_sems == "2:20");
    // 1160 -> 19:20 -> 7:20
    assert(z.kible_saati == "7:20");

    std::cout << "test_vkt_turk_v_d_standard passed." << std::endl;
}

void test_vkt_turk_v_d_edge_cases() {
    zaman z;

    z.h_aksam_td = 1439;

    z.h_istibak_nucum_td = 1440;
    z.h_yatsi_td = 1440;
    z.h_isa_sani_td = 1440;

    z.h_imsak_td = 0;
    z.h_sabah_td = 1;
    z.h_gunes_td = 59;
    z.h_israk_td = 60;
    z.h_kerahet_td = 61;
    z.h_ogle_td = 600; // 10:00
    z.h_ikindi_td = 600;
    z.h_asr_sani_td = 600;
    z.h_isfirar_sems_td = 600;
    z.h_kible_saati_td = 600;

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

    z.vkt_turk_v_d();

    assert(z.aksam_td == 0);
    assert(z.istibak_nucum_td == 1);
    assert(z.yatsi_td == 1);
    assert(z.isa_sani_td == 1);
    assert(z.imsak_td == 1); // (1440 - 1439) + 0 = 1
    assert(z.sabah_td == 2);
    assert(z.gunes_td == 60);
    assert(z.israk_td == 61);
    assert(z.kerahet_td == 62);
    assert(z.ogle_td == 601);

    assert(z.istibak_nucum == "0:1");
    assert(z.sabah == "0:2");
    assert(z.gunes == "1:0");
    assert(z.israk == "1:1");
    assert(z.kerahet == "1:2");
    assert(z.ogle == "10:1");

    std::cout << "test_vkt_turk_v_d_edge_cases passed." << std::endl;
}

int main() {
    test_vkt_turk_v_d_standard();
    test_vkt_turk_v_d_edge_cases();
    std::cout << "All vkt_turk_v_d tests passed." << std::endl;
    return 0;
}
