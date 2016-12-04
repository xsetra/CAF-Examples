#include <iostream>
#include <caf/all.hpp>

using namespace std;
using namespace caf;

/*
Class kullanarak bir aktör oluşturmak için:
	1- Constructor'ın ilk argümanı actor_config& reference tipinde olmalıdır. Bu base classa yönlendirmelidir.
	2- make_behavior, event-based actorler için ; act, blocking actorler için geçersiz kılıcıdır.
*/

// class-based, dynamically typed, event-based API
class calculator : public event_based_actor {
	public:
		calculator(actor_config& cfg) : event_based_actor(cfg) {
			// Constructor
		}

		behavior make_behavior() override {
			return calculator_fun(this);
		}
};

// class-based, dynamically typed, blocking API
class blocking_calculator : public blocking_actor {
	public:
		blocking_calculator(actor_config& cfg) : blocking_actor(cfg) {
			// Constructor
		}

		void act() override {
			blocking_calculator_fun(this);
		}
};

// class-based, statically typed, event-based API
class typed_calculator : public calculator_actor::based {
	public:
		typed_calculator(actor_config& cfg) : calculator_actor::base(cfg) {
			//Constructor
		}
		behavior_type make_behavior() override {
			return typed_calculator_fun();
		}
};