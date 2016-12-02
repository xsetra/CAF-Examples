#include <iostream>

using namespace std;

/*
Aktörler, callback'leri (geri aramaları) saklayabilir. (lambda kullanılır)
Bunu yaparken, behavior veya message_handler kullanırlar.
İlki (behavior) , opsiyonel zaman aşımını saklar, diğeri hazırlanırken
*/

// Definition and Composition

// behavior : bir aktörün cevabının kime gönderilecegini tanımlar.
// Opsiyonel Zaman Aşımı : Belirli bir zamandan sonra mesaj alınmaz ise
// aktörün durumunun dinamik olarak değiştirilmesini sağlar. (behavior)

message_handler x1{
	[](int i) {/* ... */},
	[](double db) { /* ... */ },
	[](int a, int b, int c) { /* ... */ }
};
/*
İlk örnegimizde, x1 bir mesaj kabul behavior modelidir.
Bu bir int veya bir double veya 3 int değer içerir.
Diğer mesajlar Default Handler'a gönderilir.
*/
message_handler x2{
	[](double db) {/* ... */},
	[](double db) {/* unreachable */}
};
/*
Algoritma ilk eşleşmede durar. 2. callback erişilemez olur.
*/
message_handler x3 = x1.or_else(x2);
message_handler x4 = x2.or_else(x1);
// Message handler'lar, or_else ile kombine edilebilirler.