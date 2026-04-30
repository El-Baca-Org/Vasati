## 2026-04-30 - XML Ayrıştırma Optimizasyonu
**Learning:** XML dosya okuma ve ayrıştırma işlemi (pugi::xml_document.load_file) sınıf yapıcısında (constructor) tekrarlı olarak çağrıldığında ciddi performans darboğazına neden oluyor.
**Action:** `zaman` sınıfında XML belgesi (dosya) ve kök düğümü (sehir) değişkenlerini statik yaparak ve Lazy Initialization (Tembel Başlatma) uygulayarak, veritabanının belleğe sadece bir kez yüklenmesini sağladım.
