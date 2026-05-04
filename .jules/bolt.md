## 2024-05-04 - XML Parsing Bottleneck Elimination
**Learning:** Parsing the XML database (`pugi::xml_document::load_file`) in the `zaman` class constructor on every object instantiation creates a severe performance bottleneck.
**Action:** Use lazy initialization with static class variables to parse the XML database only once. This reduces the time for 10000 object creations from 3.82s to 0.018s.
