#include "static_vector.h"
#include <vector>

int main(){
    tflib::static_vector<std::vector<int>, 5> vecs = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    vecs.remove_at(0);

    for (auto& vec : vecs){
        std::cout << vec[1] << '\n';
    }
}