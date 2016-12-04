#include <iostream>
#include <caf/all.hpp>

using namespace std;
using namespace caf;

/*
 * Composable behavior'lar ile çalışırken  param<T>
 * param<T> ' nin amacı : Hem atom sabiti hemde atom sabiti olmadan  erişim için tek bir
 * arayüzün sağlanması
 * Sabitle erişim, const T& ile modellenmiştir. üye fonksiyonları get() and operator->
 *
 * Bir degere değiştirme erişimi edinirken , Değere birden fazla referans varsa, CAF değeri değiştirilebilir erişimi sağlamadan önce degeri kopyalar.
 *
 * Değiştirilebilir referans, üye fonksiyonlardan döner "get_mutable()" ve "move()"
 * move() fonksiyonu std::move(x.get_mutable()) için kolaylıktır.
 *
 * Aşagıdaki ornek, basit bir sözlüğü geliştirirken , nasıl param<std::string>'i kullanılacagını gösteriyor.
 */

// Messaging interface
using dict = typed_actor<reacts_to<put_atom, string, string>,
                         replies_to<get_atom, string>::with<string>>;

class dict_behavior : public composable_behavior<dict> {
public:
    result<string> operator()(get_atom, param<string> key) override {
        auto i =  values_.find(key);
        if (i==values_.end())
            return "";
        return i->second;
    }
    result<void> operator()(put_atom, param<string> key, param<string> value) override {
        if(values_.count(key) != 0)
            return unit;
        values_.empace(key.move(), value.move());
        return unit;
    }
protected:
    std::unordered_map<string, string> values_;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}