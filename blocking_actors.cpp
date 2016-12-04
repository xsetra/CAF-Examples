#include <iostream>
#include <caf/all.hpp>
using namespace std;
using namespace caf;
/*
 * BLOCKING ACTORS
 Blocking aktörleri genellikle farklı thread'lerde çalışır ve zamanlaması CAF tarafından yapılmaz.
 event based aktörler gibi değildir. Blocking aktörler açık alım fonksiyonları vardır.
 Ayrıca blocking actorleri özel callbackler ile sistem mesajlarını işlemez (default message handler)
 Bu blocking aktörlerin behavior'u üzerinde tam yetki sağlar
 Örneğin : exit_msg , exit_reason::kill
 */

/*
 * Receving Messages
"receive" fonksiyonu, mailbox'un 1. öğesinden başlayarak sıralı ve tekrarlı olarak elementleri alır.
 Bir mesaj handler alır bu handler mailboxtan elementleri alır. Handler tarafından bir element eşleşmedikçe, o elementi almaz.

 Bir aktörün receive çağrısı blokludur. Tâ ki, mailboxtan bir mesaj askıdan çıkarılırsa başarı ile o zmana çagıraiblir.

Behavior tarafından onaylanmayan mesajlar , otomatik olarak atlanır ve mailbox'taki sonraki element kontrol edilir.
 */

self->receive(
        [](int x) { /*...*/ }
);

/*
 * Catch-all receive statements
 Diğer sistemin bize gönderdigi mesaj bizim standardımızda degilse kullanıcıya hata mesajı yollar.
 */
self->receive(
        [&](float x){
            //...
        },
        [&](const down_msg& x){
            // ...
        },
        [&](const exit_msg& x){
            //...
        },
        others >> [](message_view& x) -> result<message> {
            // beklenmeyen mesaj tipi için göndericiye hata mesajı dön.
            return sec::unexpected_message;
        }
);
/*
 * Receive Loops
Mesajları döngü halinde mailboxtan alabilmek için özel yapılar var.
 receive for , receive while , do_receive .until
 */
