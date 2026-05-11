cat << 'DIFF' > patch.diff
<<<<<<< SEARCH
	static const pugi::xml_node cached_sehir = []() {
		static pugi::xml_document doc;
		if (!doc.load_file("include/XML/Vakitler.xml") && !doc.load_file("vakitler.xml")) {
			throw std::runtime_error("XML load failed");
		}
		pugi::xml_node node = doc.child("cityinfo");
		if (!node) {
			throw std::runtime_error("Missing cityinfo node");
		}
		return node;
	}();
	zaman::sehir = cached_sehir;

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
=======
	static const pugi::xml_node* cached_nodes = []() {
		static pugi::xml_document doc;
		if (!doc.load_file("include/XML/Vakitler.xml") && !doc.load_file("vakitler.xml")) {
			throw std::runtime_error("XML load failed");
		}
		pugi::xml_node node = doc.child("cityinfo");
		if (!node) {
			throw std::runtime_error("Missing cityinfo node");
		}

		// ⚡ Bolt Optimization: Cache XML nodes by dayofyear attribute (O(1) lookup instead of O(N))
		// Eliminates O(N) linear search bottleneck on every object instantiation
		static pugi::xml_node nodes[400];
		for (pugi::xml_node pt = node.child("prayertimes"); pt; pt = pt.next_sibling("prayertimes")) {
			int day = pt.attribute("dayofyear").as_int(-1);
			if (day >= 0 && day < 400) {
				nodes[day] = pt;
			}
		}
		return nodes;
	}();

	zaman::sehir = cached_nodes[0].parent();

	int current_day = zaman::h_rakam_gun_senenin;
	if (current_day >= 0 && current_day < 400) {
		zaman::xml_bu_gun = cached_nodes[current_day].text().get();
	}

	zaman::h_aksam         = zaman::xml_bu_gun.substr(50, 6);
	zaman::h_istibak_nucum = zaman::xml_bu_gun.substr(56, 6);
	zaman::h_yatsi         = zaman::xml_bu_gun.substr(62, 6);
	zaman::h_isa_sani      = zaman::xml_bu_gun.substr(68, 6);

	//buradaka kodları yeniliyoruz çünkü bir sonraki gün kılacağız verileri:

	int next_day = zaman::h_rakam_gun_senenin + 1;
	if (next_day >= 0 && next_day < 400) {
		zaman::xml_bu_gun = cached_nodes[next_day].text().get();
	}
>>>>>>> REPLACE
DIFF
