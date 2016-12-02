#include <iostream>
#include <caf/all.hpp>

using namespace std;

/*
ACTORS :

CAF'da aktörler, hesaplama birimleri için hafif soyutlama şeklidir. 
Kendi durumları vardır ve diğerlerinin bu durumlara erişimine izin vermeyen aktif nesnelerdir.
Bir aktörün durumunu değiştirmenin tek yolu, ona bir mesaj göndermektir.

CAF Özel durumları kapsayacak şekilde çeşitli aktör uygulamalarını destekler. 
3 Farklı Aktör Uygulaması Vardır 
	> Dinamik veya statik olarak yazılmış
	> Sınıf veya fonksiyon tabanlı
	> Asenkronize olay işleyici veya alımları bloklayıcı
Açık bir şekilde birbiri ile kombine edilebilir. Bir şey dışında. Statik olarak tanımlanmış aktörler
genellikle olay tabanlıdır.
Örnegin; bir aktör dinamik yazılmış olarak mesajlaşabilir, bir class geliştirebilir ve alımları bloklayabilir.
Kullanıcılar tarafından tanımlanmış ortak temel sınıflar "local_actor" olarak çagırılır.

Dinamik yazılmış aktörler Erlang ve Akka geliştiricilerinden geliyor.
Hızlı prototipleme için kullanılır ama kapsamlı unit test gerekir.

Statik yazılmış aktörler daha fazla kaynak kod gerektirir 
ama derleyicinin aktörler arasındaki iletişimini doğrulamasını etkin kılar.

Aktörlerde, Blocking receive API'yi kullanmak genellikle özel thread gerektirir.
Event-based aktörler diğer taraftadır. Event-based aktörler genellikle zamanlamalı işbirliği yaparak ve
çok hafif hafıza alanı ile çalışır. (bir kaç yüz byte.)


ORTAM / Actor Systems

Tüm aktörler bir "actor_system" i temsil eden ortamda tutulurlar.
Bu ortam şunları içerir: scheduler, registry, middleman(opsiyonel)
Tek bir süreç çoklu actor_system örnegine sahip olabilir. Ama bu genellikle önerilmez.
Dağıtık CAF uygulamaları iki veya daha fazla actor systeminin bağlantısından oluşur.


COMMON ACTOR BASE TYPES : Ortak aktör taban tipleri  

UML diyagramı url : http://actor-framework.readthedocs.io/en/stable/_images/actor_types.png

Class local_actor
*/