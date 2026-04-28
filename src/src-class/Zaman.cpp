/**
 * -e-
 *
 * vasatî - version 0.9
 * --------------------------------------------------------
 * Copyright (C) 1439-1440, by M.M.M. Samil R.T.Ü (muhammed.samil.albayrak@outlook.com)
 *
 * This software is licensed under T1. For details, see the end of this file.
 *
 * This software utilizes the pugixml parser.
 * [Copyright (C) 2006-2018, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)]
 */

#ifndef SOURCE_ZAMAN_CPP
#define SOURCE_ZAMAN_CPP

#include "include-class/Zaman.hpp"

inline void append_time(std::string& str, unsigned int total_minutes) {
	unsigned int h = (total_minutes / 60) % 12;
	unsigned int m = total_minutes % 60;

	char buffer[16];
	char* p = buffer;
	if (h >= 10) { *p++ = '0' + (h / 10); }
	*p++ = '0' + (h % 10);
	*p++ = ':';
	if (m >= 10) { *p++ = '0' + (m / 10); }
	*p++ = '0' + (m % 10);

	str.append(buffer, p - buffer);
}

void zaman::tkvm_h_v_d()
{
	//zaman paketinin temel verileri;
	zaman::now   = time(0)         ;
	zaman::ltm   = localtime(&now) ;
	zaman::dt    = ctime(&now)     ;

	zaman::h_rakam_gun_senenin    = (1 + zaman::ltm->tm_yday)   ;
	zaman::h_rakam_gun_ayin       = zaman::ltm->tm_mday         ;
	zaman::h_rakam_gun_haftanin   = zaman::ltm->tm_wday         ;
	zaman::h_rakam_sene           = (1900 + zaman::ltm->tm_year);
	zaman::h_rakam_ay             = (1 + zaman::ltm->tm_mon)    ;
};
void zaman::tkvm_turk_v_d()
{
	zaman::rakam_gun_haftanin = zaman::h_rakam_gun_haftanin;

	{
	//hicri seneyi bulma algoritması.
	int a_rakami      = zaman::h_rakam_sene - 621              ;
	int b_rakami      = a_rakami / 33                          ;
	int c_rakami      = a_rakami + b_rakami                    ;

	zaman::rakam_sene = c_rakami                               ;
	};

	zaman::rakam_gun_ayin = 0; //bilgi boş olduğu belli olsun için
	zaman::rakam_gun_senenin = 0; //yukardaki gibi.
	zaman::rakam_ay = 0; //yukardaki gibi keza.
};

void zaman::vkt_h_v_d()
{

	zaman::dosya_adresi    = "include/XML/vakitler.xml";
	zaman::dosya.load_file(  zaman::dosya_adresi  )    ;
	zaman::sehir           = dosya.child("cityinfo")   ;

	char buffer[5];

	std::sprintf             (buffer, "%d", zaman::h_rakam_gun_senenin);
	const char *h_rakam_gun_senenin_string  = buffer                   ;
	zaman::xml_bu_gun        = zaman::sehir.find_child_by_attribute("prayertimes", "dayofyear", h_rakam_gun_senenin_string).text().get();

	zaman::h_aksam         = zaman::xml_bu_gun.substr(50, 6);
	zaman::h_istibak_nucum = zaman::xml_bu_gun.substr(56, 6);
	zaman::h_yatsi         = zaman::xml_bu_gun.substr(62, 6);
	zaman::h_isa_sani      = zaman::xml_bu_gun.substr(68, 6);

	//buradaka kodları yeniliyoruz çünkü bir sonraki gün kılacağız verileri:

	std::sprintf               (buffer, "%d", (zaman::h_rakam_gun_senenin + 1));
	h_rakam_gun_senenin_string = buffer;
	zaman::xml_bu_gun          = zaman::sehir.find_child_by_attribute("prayertimes", "dayofyear", h_rakam_gun_senenin_string).text().get();

	zaman::h_imsak          = zaman::xml_bu_gun.substr(0, 4) ;
	zaman::h_sabah          = zaman::xml_bu_gun.substr(5, 5) ;
	zaman::h_gunes          = zaman::xml_bu_gun.substr(10, 5);
	zaman::h_israk          = zaman::xml_bu_gun.substr(15, 5);
	zaman::h_kerahet        = zaman::xml_bu_gun.substr(20, 6);
	zaman::h_ogle           = zaman::xml_bu_gun.substr(26, 6);
	zaman::h_ikindi         = zaman::xml_bu_gun.substr(32, 6);
	zaman::h_asr_sani       = zaman::xml_bu_gun.substr(38, 6);
	zaman::h_isfirar_sems   = zaman::xml_bu_gun.substr(44, 6);
	zaman::h_kible_saati    = zaman::xml_bu_gun.substr(74, 6);

	zaman::h_aksam_td             = (std::stoi(h_aksam.substr(0, 2)) * 60)         + (std::stoi(h_aksam.substr(3, 5)))        ;
	zaman::h_istibak_nucum_td     = (std::stoi(h_istibak_nucum.substr(0, 2)) * 60) + (std::stoi(h_istibak_nucum.substr(3, 5)));
	zaman::h_yatsi_td             = (std::stoi(h_yatsi.substr(0, 2)) * 60)         + (std::stoi(h_yatsi.substr(3, 5)))        ;
	zaman::h_isa_sani_td          = (std::stoi(h_isa_sani.substr(0, 2)) * 60)      + (std::stoi(h_isa_sani.substr(3, 5)))     ;
	zaman::h_imsak_td             = (std::stoi(h_imsak.substr(0, 2)) * 60)         + (std::stoi(h_imsak.substr(2, 5)))        ;
	zaman::h_sabah_td             = (std::stoi(h_sabah.substr(0, 2)) * 60)         + (std::stoi(h_sabah.substr(2, 5)))        ;
	zaman::h_gunes_td             = (std::stoi(h_gunes.substr(0, 2)) * 60)         + (std::stoi(h_gunes.substr(2, 5)))        ;
	zaman::h_israk_td             = (std::stoi(h_israk.substr(0, 2)) * 60)         + (std::stoi(h_israk.substr(2, 5)))        ;
	zaman::h_kerahet_td           = (std::stoi(h_kerahet.substr(0, 2)) * 60)       + (std::stoi(h_kerahet.substr(3, 5)))      ;
	zaman::h_ogle_td              = (std::stoi(h_ogle.substr(0, 2)) * 60)          + (std::stoi(h_ogle.substr(3, 5)))         ;
	zaman::h_ikindi_td            = (std::stoi(h_ikindi.substr(0, 2)) * 60)        + (std::stoi(h_ikindi.substr(3, 5)))       ;
	zaman::h_asr_sani_td          = (std::stoi(h_asr_sani.substr(0, 2)) * 60)      + (std::stoi(h_asr_sani.substr(3, 5)))     ;
	zaman::h_isfirar_sems_td      = (std::stoi(h_isfirar_sems.substr(0, 2)) * 60)  + (std::stoi(h_isfirar_sems.substr(3, 5))) ;
	zaman::h_kible_saati_td       = (std::stoi(h_kible_saati.substr(0, 2)) * 60)   + (std::stoi(h_kible_saati.substr(3, 5)))  ;

};
void zaman::vkt_turk_v_d()
{
	zaman::aksam_td         = 0;
	zaman::istibak_nucum_td = zaman::h_istibak_nucum_td  - zaman::h_aksam_td        ;
	zaman::yatsi_td         = zaman::h_yatsi_td          - zaman::h_aksam_td        ;
	zaman::isa_sani_td      = zaman::h_isa_sani_td       - zaman::h_aksam_td        ;
	zaman::imsak_td         = (1440 - zaman::h_aksam_td) + zaman::h_imsak_td        ; //1440 bir günün toplam dakikası
	zaman::sabah_td         = (1440 - zaman::h_aksam_td) + zaman::h_sabah_td        ;
	zaman::gunes_td         = (1440 - zaman::h_aksam_td) + zaman::h_gunes_td        ;
	zaman::israk_td         = (1440 - zaman::h_aksam_td) + zaman::h_israk_td        ;
	zaman::kerahet_td       = (1440 - zaman::h_aksam_td) + zaman::h_kerahet_td      ;
	zaman::ogle_td          = (1440 - zaman::h_aksam_td) + zaman::h_ogle_td         ;
	zaman::ikindi_td        = (1440 - zaman::h_aksam_td) + zaman::h_ikindi_td       ;
	zaman::asr_sani_td      = (1440 - zaman::h_aksam_td) + zaman::h_asr_sani_td     ;
	zaman::isfirar_sems_td  = (1440 - zaman::h_aksam_td) + zaman::h_isfirar_sems_td ;
	zaman::kible_saati_td   = (1440 - zaman::h_aksam_td) + zaman::h_kible_saati_td  ;

	zaman::aksam = "00:00";
	append_time(zaman::istibak_nucum, zaman::istibak_nucum_td);
	append_time(zaman::yatsi,         zaman::yatsi_td);
	append_time(zaman::isa_sani,      zaman::isa_sani_td);
	append_time(zaman::imsak,         zaman::imsak_td);
	append_time(zaman::sabah,         zaman::sabah_td);
	append_time(zaman::gunes,         zaman::gunes_td);
	append_time(zaman::israk,         zaman::israk_td);
	append_time(zaman::kerahet,       zaman::kerahet_td);
	append_time(zaman::ogle,          zaman::ogle_td);
	append_time(zaman::ikindi,        zaman::ikindi_td);
	append_time(zaman::asr_sani,      zaman::asr_sani_td);
	append_time(zaman::isfirar_sems,  zaman::isfirar_sems_td);
	append_time(zaman::kible_saati,   zaman::kible_saati_td);

};

void zaman::sat_h_v_d()
{
	zaman::h_saat   = zaman::ltm->tm_hour;
	zaman::h_dakika = zaman::ltm->tm_min ;
	zaman::h_saniye = zaman::ltm->tm_sec ;
};
void zaman::sat_turk_v_d()
{
	zaman::h_zaman_td  = ((zaman::h_saat * 60) * 60)      + (zaman::h_dakika * 60) + zaman::h_saniye;
	zaman::zaman_td    = ((1440 - zaman::h_aksam_td) * 60) + zaman::h_zaman_td                      ;

	zaman::saat      =  int((( zaman::zaman_td   / 60) / 60 ) % 12);
	zaman::dakika    =  int((  zaman::zaman_td   / 60) % 60 )      ;
	zaman::saniye    =  int((  zaman::zaman_td ) % 60)             ;

	char buffer[32];
	char* p = buffer;
	if (zaman::saat >= 10) { *p++ = '0' + (zaman::saat / 10); }
	*p++ = '0' + (zaman::saat % 10);
	*p++ = ':';
	if (zaman::dakika >= 10) { *p++ = '0' + (zaman::dakika / 10); }
	*p++ = '0' + (zaman::dakika % 10);
	*p++ = ':';
	if (zaman::saniye >= 10) { *p++ = '0' + (zaman::saniye / 10); }
	*p++ = '0' + (zaman::saniye % 10);
	*p = '\0';

	zaman::simdiki_zaman_turk.append(buffer, p - buffer);

};




void zaman::h_v_d()
{
	tkvm_h_v_d()     ;
	vkt_h_v_d ()     ;
	sat_h_v_d ()     ;
};
void zaman::turk_v_d()
{
	tkvm_turk_v_d()     ;
	vkt_turk_v_d ()     ;
	sat_turk_v_d ()     ;
};



void zaman::gos_turk_v()
{
	std::cout << "__TURK__            Topluca   : " << "" << std::endl << std::endl;

	std::cout << "__TURK__            Sene      : " << zaman::rakam_sene          << std::endl;
	std::cout << "__TURK__            Ay        : " << zaman::rakam_ay            << ". ay"   << std::endl;
	std::cout << "__TURK__ (Yilin)    Gun       : " << zaman::rakam_gun_senenin   << ". gunu" << std::endl;
	std::cout << "__TURK__ (Ayin)     Gun       : " << zaman::rakam_gun_ayin      << ". gunu" << std::endl;
	std::cout << "__TURK__ (Haftanin) Gun       : " << zaman::rakam_gun_haftanin  << ". gunu" << std::endl << std::endl;

	std::cout << "__TURK__ saat ve dakika       : " << zaman::simdiki_zaman_turk   << std::endl;
	std::cout << "__TURK__ Saat                 : " << zaman::saat                 << std::endl;
	std::cout << "__TURK__ Dakika               : " << zaman::dakika               << std::endl;
	std::cout << "__TURK__ Saniye               : " << zaman::saniye               << std::endl << std::endl;

	std::cout << "__TURK__ aksam                : " << zaman::aksam         << std::endl;
	std::cout << "__TURK__ istibak-i nucum      : " << zaman::istibak_nucum << std::endl;
	std::cout << "__TURK__ yatsi (isa-i evvel)  : " << zaman::yatsi         << std::endl;
	std::cout << "__TURK__ isa-i sani           : " << zaman::isa_sani      << std::endl;
	std::cout << "__TURK__ imsak                : " << zaman::imsak         << std::endl;
	std::cout << "__TURK__ sabah                : " << zaman::sabah         << std::endl;
	std::cout << "__TURK__ gunes                : " << zaman::gunes         << std::endl;
	std::cout << "__TURK__ israk                : " << zaman::israk         << std::endl;
	std::cout << "__TURK__ kerahet              : " << zaman::kerahet       << std::endl;
	std::cout << "__TURK__ ogle                 : " << zaman::ogle          << std::endl;
	std::cout << "__TURK__ ikindi               : " << zaman::ikindi        << std::endl;
	std::cout << "__TURK__ asr-i sani           : " << zaman::asr_sani      << std::endl;
	std::cout << "__TURK__ isfirar-i sems       : " << zaman::isfirar_sems  << std::endl;
	std::cout << "__TURK__ kible saati          : " << zaman::kible_saati   << std::endl;

	std::cout << std::endl;
};
void zaman::gos_h_v()
{
	std::cout << std::endl << std::endl << std::endl << std::endl;

	std::cout << "(hrist) (ing)      Topluca    : " << zaman::dt                   << std::endl ;

	std::cout << "(hrist)            Sene       : " << zaman::h_rakam_sene         << std::endl ;
	std::cout << "(hrist)            Ay         : " << zaman::h_rakam_ay           << ". ay"   << std::endl;
	std::cout << "(hrist) (Yilin)    Gun        : " << zaman::h_rakam_gun_senenin  << ". gunu" << std::endl;
	std::cout << "(hrist) (Ayin)     Gun        : " << zaman::h_rakam_gun_ayin     << ". gunu" << std::endl;
	std::cout << "(hrist) (Haftanin) Gun        : " << zaman::h_rakam_gun_haftanin << ". gunu" << std::endl << std::endl;

	std::cout << "(hrist) Saat                  : " << zaman::h_saat          << std::endl;
	std::cout << "(hrist) Dakika                : " << zaman::h_dakika        << std::endl;
	std::cout << "(hrist) Saniye                : " << zaman::h_saniye        << std::endl << std::endl;

	std::cout << "(hrist) aksam                 : " << zaman::h_aksam         << std::endl;
	std::cout << "(hrist) istibak-i nucum       : " << zaman::h_istibak_nucum << std::endl;
	std::cout << "(hrist) yatsi (isa-i evvel)   : " << zaman::h_yatsi         << std::endl;
	std::cout << "(hrist) isa-i sani            : " << zaman::h_isa_sani      << std::endl;
	std::cout << "(hrist) imsak                 : " << zaman::h_imsak         << std::endl;
	std::cout << "(hrist) sabah                 : " << zaman::h_sabah         << std::endl;
	std::cout << "(hrist) gunes                 : " << zaman::h_gunes         << std::endl;
	std::cout << "(hrist) israk                 : " << zaman::h_israk         << std::endl;
	std::cout << "(hrist) kerahet               : " << zaman::h_kerahet       << std::endl;
	std::cout << "(hrist) ogle                  : " << zaman::h_ogle          << std::endl;
	std::cout << "(hrist) ikindi                : " << zaman::h_ikindi        << std::endl;
	std::cout << "(hrist) asr-i sani            : " << zaman::h_asr_sani      << std::endl;
	std::cout << "(hrist) isfirar-i sems        : " << zaman::h_isfirar_sems  << std::endl;
	std::cout << "(hrist) kible saati           : " << zaman::h_kible_saati   << std::endl;
};

zaman::zaman()
{
	h_v_d();
	turk_v_d();

	gos_turk_v();
	gos_h_v();
}
zaman::~zaman()
{
}

#endif

/**
 * Copyright (C) 1439-1440, by M.M.M. Samil R.T.Ü (muhammed.samil.albayrak@outlook.com)
 *
 * T1 License Details:
 *
 * Redistribution and usage require notification to the developer.
 * Unauthorized use and development are prohibited. Rights may be revoked
 * if any hostility against Turkey is identified. This license and its
 * terms must be cited without omission in any redistributed or derivative
 * works. The code cannot be sold or used for commercial profit.
 *
 * -e-
 */
