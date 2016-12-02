#include <string>
#include <iostream>

#include <caf/all.hpp>

using std::endl;
using std::string;

using namespace caf;

behavior mirror(event_based_actor* self) {
  // oluşturulmuş aktörün davranısını geri döndür
  return {
    // Bir mesaja karşılık olarak, bir mesaj döndüren bir mesaj işlemcisi 
    [=](const string& what) -> string {
      // aout ile "Hello World!" yaz (Cout yerine güvenli thread kullanımı)
      aout(self) << what << endl;
      // yanıt "!dlroW olleH"
      return string(what.rbegin(), what.rend());
    }
  };
}

void hello_world(event_based_actor* self, const actor& buddy) {
  // buddy'imize "Hello World!" mesajı gönder.
  self->request(buddy, std::chrono::seconds(10), "Hello World!").then(
    // ... yanıt için 10 s bekle ...
    [=](const string& what) {
      // ... ve yaz
      aout(self) << what << endl;
    }
  );
}

int main() {
  // CAF ortamımız
  actor_system_config cfg;
  actor_system system{cfg};
  // Yeni bir aktör oluştur 'mirror()' fonksiyonunu çağırır.
  auto mirror_actor = system.spawn(mirror);
  // Başka bir aktör oluştur 'hello_world(mirror_actor)' fonksiyonunu çağırır.
  system.spawn(hello_world, mirror_actor);
  // Sistem iki actor yok edilene kadar bekleyecektir.
}