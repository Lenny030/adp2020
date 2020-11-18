#include"aufgabe2.hpp"
#include<algorithm>

void construct(std::vector<uint32_t>& sa, const std::string& text)
{
    sa.clear();
    //pushes indices from 0 to n-1 into sa 
    for(uint32_t i {}; i < text.size(); ++i) sa.push_back(i);
    //sorts sa, by comparing corresponding substrings of text 
    auto naiv = [&] (int const a, int const b) { return (text.substr(a, text.length()) <= text.substr(b, text.length())); };

    std::sort(sa.begin(), sa.end(), naiv);
}
