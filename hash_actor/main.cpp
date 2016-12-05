#include <iostream>
#include <string>
#include <caf/all.hpp>
#include "sha1.hpp"

using namespace std;
using namespace caf;

behavior hash_actor(event_based_actor* self){
    return {
            [=](const string& plainText) -> string {
                aout(self) << "Plain Text : " << plainText << endl;
                return string(sha1(plainText));
            }
    };
}

void hash_cli(event_based_actor* self, const actor& hash_serv, const string& plaintText){
    self->request(hash_serv, std::chrono::seconds(10), plaintText).then(
        [=](const string& responseText){
            aout(self) << "Hash Text : " << responseText << endl;
        }
    );
}

int main() {
    actor_system_config cfg;
    actor_system system{cfg};

    auto hash_serv = system.spawn(hash_actor);
    system.spawn(hash_cli, hash_serv, "GNU");

    return 0;
}