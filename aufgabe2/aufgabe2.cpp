#include"aufgabe2.hpp"
#include<algorithm>

//helper function, which does not allocate new strings
bool indice_comp(const int a, const int b, const std::string& text)
{
    bool ans = false;

    //compares substrings in T with each other
    for(uint32_t i = a; i < text.length(); ++i)
    {
        for(uint32_t j = b; j < text.length(); j++)
        {
            if(text.at(a) < text.at(b)) {return true;}
            //in the case where they are even, we have to go on both substrings in T an indice further
            if(text.at(a) == text.at(b))
            {
                //is set to true, in case its the end of or substring i to n-1
                ans = true;
                break;
            }
            //first position that does not "match" end comparission
            else {return false;}
        }
    }
    return ans;
}

void construct(std::vector<uint32_t>& sa, const std::string& text)
{
    sa.clear();
    //pushes indices from 0 to n-1 into sa 
    for(uint32_t i {}; i < text.size(); ++i) sa.push_back(i);
    std::sort(sa.begin(), sa.end(), [&] (int a, int b) { return indice_comp(a,b,text); });
}
