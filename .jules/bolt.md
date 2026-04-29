## 2023-10-27 - [Zaman Sınıfı XML Parsing Performansı]
**Learning:** `zaman` sınıfı içerisinde, her obje üretildiğinde büyük bir XML dosyasının (Vakitler.xml) tekrar tekrar parse edilmesi ciddi bir darboğaz (bottleneck) yaratıyordu.
**Action:** XML dosyası (pugi::xml_document) ve ilgili node'lar statik değişkenlere dönüştürülüp, ilk obje üretiminde bir kere parse edilecek şekilde (lazy initialization) ayarlandı. C++ sınıflarında dosya I/O gibi ağır operasyonları constructor'da instance-level tutmamak gerektiği öğrenildi.
