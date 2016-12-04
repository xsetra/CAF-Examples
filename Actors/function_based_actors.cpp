/*
Bir aktör geliştirmek için bir fonksiyon veya fonksiyon nesnesi kullanıyorken, 
ilk argüman, aktörün kendisini işaret etmesi için kullanılmalıdır. Genellikle, event_based_actor*
veya blocking_actor* olur.
*/

#include <iostream>
#include <caf/all.hpp>

using namespace std;
using namespace caf;

// function-based, dynamically typed, event-based API
behavior calculator_fun(event_based_actor*){
	return behavior{
		[](add_atom, int a, int b){
			return a+b;
		},
		[](sub_atom), int a, int b){
			return a-b;
		}
	};
}

// function-based, statically typed, event-based API
calculator_actor::behavior_type typed_calculator_fun() {
	return {
		[](add_atom, int a, int b){
			return a+b;
		},
		[](sub_atom, int a, int b){
			return a-b;
		}
	};
}

// function-based, dynamically typed, blocking API
void blocking_calculator_fun(blocking_actor* self){
	bool running = true;
	// mesaj alıyorken.
	self -> receive_while(running) {
		[](add_atom, int a, int b){
			return a+b;
		},
		[](sub_atom, int a, int b){
			return a-b;
		},
		// istenilen atom sabiti gelmediyse işler farklılasıyor.
		[&](exit_msg& em){
			if (em.reason) {
				self -> fail_state(std::move(em.reason));
				running = false;
			}
		}
	};
}