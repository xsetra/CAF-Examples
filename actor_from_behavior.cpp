#include <iostream>
#include <caf/all.hpp>

using namespace std;
using namespace caf;

/*
 * ACTORS FROM COMPOSABLE BEHAVIORS
 * Büyük sistemler oluştururken, varolan davranışlardan üretmek iyi bir şeydir.
 * CAF'da hazırlanabilir davranışlar geliştiricilere,  messaging interface'den behavior class oluşturmalarını sağlar.
 */

using add_atom = atom_constant<atom("add")>; //Atom sabiti oluşturdum
using multiply_atom = atom_constant<atom("multiply")>;

// messaging interface
using adder = typed_actor<replies_to<add_atom, int, int>::with<int>>;
using multiplier = typed_actor<replies_to<multiply_atom, int, int>::with<int>>;

// Message handler ile actor arasındaki ilişki, nesne ve metotları arasındaki ilişki gibi.
class adder_bhvr : public composable_behavior<adder> {
public:
    result<int> operator()(add_atom, int x, int y) override {
        return x + y;
    }
};

class multiplier_bhvr : public composable_behavior<multiplier> {
public:
    result<int> operator()(multiply_atom, int x, int y) override {
        return x * y;
    }
};

//calculator_bhvr, kalıtımlanabilir yada birleştirilebilir
using calculator_bhvr = composed_behavior<adder_bhvr, multiplier_bhvr>;

void caf_main(actor_system& system){
    // Composable behavior, direkt olarak spawn edilemez.
    auto f = make_function_view(system.spawn<calculator_bhvr>());
    cout << "10 + 20 = " << f(add_atom::value, 10, 20) << endl;
    cout << "7 * 9 = " << f(multiply_atom::value, 7, 9) << endl;
}

CAF_MAIN()