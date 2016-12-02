#include <iostream>

using namespace std;

/*
ATOMS :

Geri dönüşlü durumlarda mesaj handler tanımlamak kullanışlıdır.
Ama, mesajları basit yoldan meta data ile not etmek gerekir.

Bir aktör düşünün ki, bu aktör tam sayılar için matematiksel hizmet sağlasın.
Aktör iki tam sayı alır, kullanıcı tarafından tanımlanmış işlemleri yapar ve değer döndürür.

Ek bir durum olmadıkça, hangi işlemi yapacagına karar veremez. Bu işlem mesaj içine encode edilmelidir.
Erlang programlama dili, bir yaklaşım ile tanıstırdı bizleri. Numeric olmayan sabitler kullandı. 
Bunlara atom denildi. ÖZel bir amaç için var. Çalışma zamanında string sabitlerini yormaz.

Atom'lar 'constexpr' kullanılarak veya 'atom' fonksiyonu kullanılarak oluşturulurlar.
*/

atom_value a1 = atom("add");
atom_value a2 = atom("multiply");

/*
Uyarı : Derleyici, derleme zamanında kısıtlamalara zorlayamaz, Uzunluk kontrol dışında. 
Bu iddia, atom("!?") != atom("?!") doğru değildir. Çünkü her geçersiz karakter whitespace karaktere çevirilir.
*/

/*
'atom_value' derlenme zamanında hesaplanırken, benzersiz olarak yazılmaz ve callback signature olmadan kullanılamaz.
Bunu gerçekleştirebilmek için, CAF derleme zamanı atom sabitlerini öneriyor.
*/
using add_atom = atom_constant<atom("add")>;
using multiply_atom = atom_constant<atom("multiply")>;
// Bu sabitleri kullanarak, kullanışlı yoldan mesaj gönderme arayüzünü tanımlayabiliriz. 

