# 📚 Alexandria - Kütüphane Yönetim Sistemi

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B17-blue)
![Framework](https://img.shields.io/badge/framework-Qt6-green)
![Build](https://img.shields.io/badge/build-CMake-orange)

**Alexandria**, modern C++ ve Qt framework'ü kullanılarak geliştirilmiş, hızlı, güvenli ve kullanıcı dostu bir masaüstü kütüphane yönetim sistemidir. İskenderiye Kütüphanesi'nden ilham alan bu proje, kitap envanterini yönetmeyi, takip etmeyi ve kütüphane operasyonlarını dijitalleştirmeyi hedefler.

## 🚀 Özellikler

* **Modern Arayüz:** Qt Widgets ile geliştirilmiş temiz, responsive ve kullanıcı dostu grafik arayüz.
* **Güvenli Veritabanı:** SQLite ve QtSql modülü ile entegre, yerel ve güvenli veri saklama.
* **Kitap Yönetimi:**
    * ➕ **Ekleme:** Kitap Adı, Yazar ve ISBN bilgileriyle yeni kayıt oluşturma.
    * 📋 **Listeleme:** Tüm envanteri anlık güncellenen tablo yapısında görüntüleme.
    * 🗑️ **Silme:** Seçili kitapları veritabanından güvenli bir şekilde kaldırma.
    * 🔄 **Durum Takibi:** Kitabın "Mevcut" veya "Ödünç Verildi" durumunu izleme.
* **Çapraz Platform:** Windows, Linux ve macOS üzerinde çalışabilir yapı.

## 🛠️ Kullanılan Teknolojiler

Bu proje, yüksek performans ve sürdürülebilirlik için aşağıdaki teknolojilerle inşa edilmiştir:

* **Programlama Dili:** C++17
* **Framework:** Qt 6 (Core, Gui, Widgets, Sql)
* **Veritabanı:** SQLite 3 (Gömülü / Embedded)
* **Derleme Sistemi:** CMake (v3.16+)

## ⚙️ Kurulum ve Derleme

Projeyi kendi bilgisayarınızda derleyip çalıştırmak için aşağıdaki adımları izleyin.

### Gereksinimler

* C++17 uyumlu bir derleyici (GCC, Clang veya MSVC)
* [Qt 6 SDK](https://www.qt.io/download) (Gerekli bileşenler: `Qt Sql`, `Qt Widgets`)
* [CMake](https://cmake.org/)

### Adım Adım Kurulum

1.  **Repoyu klonlayın:**
    ```bash
    git clone [https://github.com/SweetRomeo/Alexandria.git](https://github.com/SweetRomeo/Alexandria.git)
    cd Alexandria
    ```

2.  **Derleme klasörü oluşturun:**
    ```bash
    mkdir build && cd build
    ```

3.  **Projeyi yapılandırın (CMake):**
    ```bash
    cmake ..
    ```
    *(Not: Eğer Qt yolunuzu sistem bulamazsa `-DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/..."` parametresini eklemeniz gerekebilir.)*

4.  **Derleyin:**
    ```bash
    cmake --build .
    ```

5.  **Çalıştırın:**
    Oluşan `Alexandria` (veya Windows'ta `Debug/Alexandria.exe`) dosyasını çalıştırın.
    > Uygulama ilk açılışta `alexandria.db` veritabanı dosyasını otomatik olarak oluşturacaktır.

## 📸 Ekran Görüntüleri

*(Buraya uygulamanın ekran görüntülerini ekleyebilirsiniz. Örneğin: `![Ana Ekran](docs/screenshot.png)`)*

## 🗺️ Yol Haritası (Roadmap)

Projenin geliştirilme sürecinde planlanan özellikler:

- [x] Temel veritabanı mimarisi (Kitaplar, Kullanıcılar)
- [x] Qt tabanlı grafik arayüze (GUI) geçiş
- [x] Kitap Ekleme / Silme / Listeleme fonksiyonları
- [ ] Kullanıcı Yönetim Sistemi (Üye ekleme/silme)
- [ ] Ödünç Alma & İade Etme (Transaction) Sistemi
- [ ] Gelişmiş Arama ve Filtreleme
- [ ] İstatistik Paneli

## 🤝 Katkıda Bulunma

Katkılarınızı memnuniyetle karşılıyoruz!
1.  Bu repoyu "Fork"layın.
2.  Yeni bir özellik dalı (branch) oluşturun (`git checkout -b ozellik/YeniOzellik`).
3.  Değişikliklerinizi kaydedin (`git commit -m 'Yeni özellik eklendi'`).
4.  Dalınızı gönderin (`git push origin ozellik/YeniOzellik`).
5.  Bir "Pull Request" oluşturun.

## 📄 Lisans

Bu proje [MIT Lisansı](LICENSE) ile lisanslanmıştır. Daha fazla bilgi için `LICENSE` dosyasına bakabilirsiniz.

---
**Geliştirici:** [SweetRomeo](https://github.com/SweetRomeo)
