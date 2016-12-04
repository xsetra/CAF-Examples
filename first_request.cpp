#include <iostream>
#include <caf/all.hpp>

using namespace std;
using namespace caf;

// messaging interface
using cell = typed_actor<reacts_to<put_atom, int>,
                         replies_to<get_atom>::with<int>>;

struct cell_state {
    int value = 0;
};

cell::behavior_type cell_impl(cell::stateful_pointer<cell_state> self, int x0) {
    self->state.value = x0;
    return {
            [=](put_atom, int val) {
                self->state.value = val;
            },
            [=](get_atom){
                return self->state.value;
            }
    };
}

void waiting_testee(event_based_actor* self, vector<cell> cells){
    for(auto& x : cells){
        self->request(x,second(1), get_atom::value).await([=](int y) {
            aout(self) << "cell #" << x.id() << " -> " << y << endl;
        });
    }
}

void multiplexed_testee(event_based_actor* self, vector<cell> cells {
    for(auto& x : cells){
        self->request(x, seconds(1), put_atom::value).then([=](int y) {
           aout(self) << "cell $" << x.id() << " -> " << y << endl;
        });
    }
}

void blocking_testee(blocking_actor* self, vector<cell> cells){
    for(auto& x : cells){
        self->request(x, seconds(1), get_atom::value).receive([&](int y){
            aout(self) << "cell blocking #" << x.id() << " -> " y << endl;
        },
        [&](error& err) {
            aout(self) << "cell blocking $" << x.id() << " -> " << self->system().render(err) << endl;
        });
    }
}

int caf_main(actor_system& system){
    vector<cell> cells;
    for(auto i = 0; i < 5; i++){
        cells.emplace_back(system.spawn(cell_impl, i * i));
    }
}

CAF_MAIN()