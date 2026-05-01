## 2024-05-01 - [Zaman Class XML Parsing Performance]
**Learning:** XML dosyasını `pugi::xml_document::load_file` ile okumak oldukça ağır bir işlem. `zaman` sınıfı her instantiate edildiğinde bu işlem tekrarlanıyordu. Ancak veriler uygulama yaşam döngüsü boyunca değişmiyor.
**Action:** Bu tür ağır I/O ve parsing işlemlerini `static` üyeler ve lazy initialization kullanarak (sadece bir kez çalışacak şekilde) optimize etmek, sınıfın çoklu kullanım senaryolarında (örneğin döngü içinde 1000 obje oluşturulduğunda ~%73 hızlanma: 0.37s -> 0.10s) önemli performans artışı sağlıyor.
