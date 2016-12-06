#include <iostream>
#include <caf/all.hpp>

using std::endl;
using namespace std;
using namespace caf;

//Atom sabitlerinin tanımlanması
using topla_atom = atom_constant<atom("topla")>;
using cikar_atom = atom_constant<atom("cikar")>;
using carp_atom = atom_constant<atom("carp")>;


//Messaging interface tanımlamaları
using math_actor = typed_actor<replies_to<topla_atom, int, int>::with<int>,
                               replies_to<cikar_atom, int, int>::with<int>,
                               replies_to<carp_atom , int, int>::with<int>>;

//Prototipler
behavior hesaplama(event_based_actor* self);
void doRequest(event_based_actor* self, const actor& targetActor);

// fonksiyon tabanlı , dinamik yazılmış , event based API
behavior hesaplama(event_based_actor* self){
    return behavior{
            [](topla_atom, int n1, int n2){
                return n1+n2;
            },
            [](cikar_atom, int n1, int n2){
                return n1-n2;
            },
            [](carp_atom, int n1, int n2){
                return n1*n2;
            }
    };
}

void doRequest(event_based_actor* self, const actor& targetActor){
    int val1 = 10 , val2 = 5;
    self->request(targetActor, std::chrono::seconds(1), topla_atom::value, val1, val2).then(
            [=](int result){
                aout(self) << "Toplam : " << val1 << "+" << val2 << "=" << result << endl;
            }
    );
    self->request(targetActor, std::chrono::seconds(1), cikar_atom::value, val1, val2).then(
            [=](int result){
                aout(self) << "Cikarma : " << val1 << "-" << val2 << "=" << result << endl;
            }
    );
    self->request(targetActor, std::chrono::seconds(1), carp_atom::value, val1, val2).then(
            [=](int result){
                aout(self) << "Carpim : " << val1 << "*" << val2 << "=" << result << endl;
            }
    );
}

int main(){
    actor_system_config cfg;
    actor_system system{cfg};

    auto hesaplayici = system.spawn(hesaplama);
    system.spawn(doRequest,hesaplayici);

    return 0;
}

