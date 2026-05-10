## 2026-05-08 - [XML Parsing Optimization]
**Learning:** Parsing the XML document in the constructor of `zaman` class without caching causes a significant performance bottleneck (around 40ms per 100 instantiations). Repeatedly loading the file creates high overhead.
**Action:** Used a C++11 method-local magic static and an immediately invoked lambda to cache the `cityinfo` XML node (`zaman::sehir`), reducing 100 instantiations from ~40ms to ~14ms.

## 2026-05-10 - [XML Node Caching for O(1) Lookup]
**Learning:** Repeatedly calling `pugi::xml_node::find_child_by_attribute` is an O(N) linear search that creates a major bottleneck in hot paths, such as inside object constructors (`zaman::vkt_h_v_d()`).
**Action:** Cached XML nodes mapped by sequential attributes (like `dayofyear` in Vakitler.xml) into a static array (`cached_nodes[400]`), transforming the lookup to O(1). This eliminated the bottleneck on every object instantiation.
