#include "ACTrie.hpp"
#include <stdexcept>

//Constructor------------------------------------------------------------------
ACTrie::ACTrie(const std::vector<std::string> & needles)
{
    // Exception handeling, empty vector & needle check
    if(needles.empty()) std::logic_error("empty vector, input requiered");

    //only letters between A & Z are valid needles
    for(auto vec : needles)
    {
        for(uint32_t j = 0; j < vec.size() ; ++j)
        {
            if(int(vec[j]) < 65 || int(vec[j]) > 90) {
                throw std::invalid_argument("Wrong needles");
            }
        }
    }

    //Build Trie structure with Pattern-Exit-Node 
    for(auto vec : needles)
    {
        
    }


}

