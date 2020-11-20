#include"aufgabe2.hpp"
#include<algorithm>

void construct(std::vector<uint32_t>& sa, const std::string& text)
{
    sa.clear();
    //pushes indices from 0 to n-1 into sa 
    for(uint32_t i {}; i < text.size(); ++i) sa.push_back(i);

    std::sort(sa.begin(), sa.end(), [&] (uint32_t a, uint32_t b) 
    {
        if(text[a] > text[b]) { return false; }
        if(text[a] < text[b]) { return true; }
        while(text[a] ==  text[b])
        {
            ++a;
            ++b;
        }
        return text[a] < text[b];
    });
}

