#include <iostream>
#include <caf/all.hpp>

using namespace std;

/*
Statik ve dinamik olarak yazılmış aktörler oluşturulurken actor_system class'ının 
üye fonksiyonu olan spawn'dan yararlanılır. 

Spawn fonksiyonu ilk parametre olarak bir fonksiyon veya ilk template parametresi olarak class alabilir.
Aşağıdaki fonksiyonlar ve sınıflar aktör'ü temsil eder.
*/
behavior calculator_fun(event_based_actor* self);
void blocking_calculator_fun(blocking_actor* self);
calculator_fun::behavior_type typed_calculator_fun();
class calculator;
class blocking_calculator;
class typed_calculator;


// Her tür implementasyon için aktör oluşturma.
auto a2 = system.spawn(calculator_fun);
auto a3 = system.spawn(typed_calculator_fun);
auto a4 = system.spawn<blocking_calculator>();
auto a5 = system.spawn<calculator>();
auto a6 = system.spawn<typed_calculator>();
scoped_actor self{system};

int main()
{

}