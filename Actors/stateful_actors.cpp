#include <iostream>
#include <caf/all.hpp>

using namespace std;
using namespace caf;

/*
Stateful actor API'si fonksiyon tabanlı aktörlerde, durumu korumayı kolaylaştırır.
örneğin; iki actor üye değişkenileri birbirlerinin referensını tutuyorsa, bunlar aralarında bir cycle oluştururlar nede yok edilirler.
Stateful actorleri kullanarak bu cycle'ı kırabiliriz. Çünkü nesne yok edilecek.
*/

// Messaging interface
using cell = typed_actor<reacts_to<put_atom, int>,
						 replies_to<get_atom>::with<int>>;

struct cell_state {
	int value = 0;
};

// Message handler , statik , stateful api
cell::behavior_type type_checked_cell(cell::stateful_pointer<cell_state> self) {
	return {
		[=](put_atom, int val){
			self->state.value = val;
		},
		[=](get_atom) {
			return self->state.value;
		}
	};
}

//Message handler, dinamik , stateful api
behavior unchecked_cell(stateful_actor<cell_state>* self) {
	return {
		[=](put_atom, int val) {
			self->state.value = val;
		},
		[=](get_atom) {
			return self->state.value;
		}
	};
}

// Stateful actorlerde aynı şekilde oluşturulurlar.

auto cell1 = system.spawn(type_checked_cell);
auto cell2 = system.spawn(unchecked_cell);