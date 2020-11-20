#include"aufgabe2.hpp"
#include<algorithm>
#include<iostream>


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
        return a > b;
    });
}

void construct_alt(std::vector<uint32_t>& sa, const std::string& text)
{
    sa.clear();
    //pushes indices from 0 to n-1 into sa
    for(uint32_t i {}; i < text.size(); ++i) sa.push_back(i);
    std::sort(sa.begin(), sa.end(), [&] (uint32_t a, uint32_t b)
    {
        bool ans = true;
        while(a < text.length() && b < text.length())
        {
            //orders suffices ascending
            if(text[a] > text[b]) { return false; }
            if(text[a] < text[b]) { return true; }
            //when the chars are equal we move a postion further in both strings
            else
            {
                //set to treu in case, smaller suffix reaches end, and ist equal to longer
                ++a;
                ++b;
            }
       }
       return ans;
    });
}

void construct_speed(std::vector<uint32_t>& sa, const std::string& text)
{
    sa.clear();
    //pushes indices from 0 to n-1 into sa 
    for(uint32_t i {}; i < text.size(); ++i) sa.push_back(i);

    std::sort(sa.begin(), sa.end(), [&] (uint32_t a, uint32_t b) 
    {
    const char* a_ptr = text.c_str() + a -1, *b_ptr = text.c_str() +b -1;
    while(*(a_ptr++) == *(b_ptr++));
    return *a_ptr < *b_ptr;
    });
}

