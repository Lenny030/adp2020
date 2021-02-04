#include "QGramIndex.hpp"
#include <math.h>
#include <iostream>

//constructor makes internal copy of arguments
QGramIndex::QGramIndex(const std::string & text_, const uint8_t q_)
    : text{text_}, q{q_}
{
    if(1 > q_ || q_ > 13) throw std::invalid_argument("Invalid q!");

    //Memberinitialation
    //step1
    this -> dir.resize (pow(4, q_) +1);
    this -> suftab.resize (text_.length()-(q_-1)+1);

    //step2+
    //compute for all k-meres the correspondng hashes with a bitmask 
    uint32_t j {};
    uint32_t prev = hash(text_.substr(0,q_));  //have to intilaize the first hash 
    this -> dir[prev]++;

    for(uint32_t i = 1; i <= text_.size() -q_+1; ++i) 
    {
        j = hashNext(prev, text_[i+q_-1]);
        this -> dir[j]++;
        prev = j;
    } 

    //step3
    //builds up the cumsum
    for(uint32_t i = 1; i < this -> dir.size(); ++i)
    {
        this -> dir[i] += this -> dir[i-1];
    }

    //step4
    prev = hash(text_.substr(0, q_));            //again intilaize first hash
    this -> dir[prev]--;                         //build final dir
    this -> suftab[dir[prev]] = 0;               //set index in suftab

    for(uint32_t i = 1; i <= text_.size() -q_+1; ++i)
    {
        j = hashNext(prev, text_[i+q_-1]); 
        this -> dir[j]--;
        this -> suftab[this -> dir[j]] = i;
        prev = j;
    }
}

//getter-----------------------------------------------------------------------
std::vector<uint32_t> QGramIndex::getHits(const uint32_t h) const
{
    if(h < 0 || h >= pow(4, this -> q)) throw std::invalid_argument("Invalid hash");
    std::vector<uint32_t> hits {};
    
    for(uint32_t i = this -> dir[h]; i < this -> dir[h+1]; ++i)
    {
        hits.push_back(this -> suftab[i]);
    } 
    return hits;
}

const std::string& QGramIndex::getText() const{
    return this -> text;
}

uint8_t QGramIndex::getQ() const{
    return this -> q;
}

//hashing----------------------------------------------------------------------
uint32_t QGramIndex::hash(const std::string& qgram) const
{
    if(this -> q != qgram.length()) throw std::invalid_argument("Invalid q-gram. Wrong length!");
    uint32_t hashimashi = 0;

    for(uint32_t i = 0; i < qgram.size(); ++i)
    {
        hashimashi *= 4;
        hashimashi += ordValue(qgram[i]);
    } 
    return hashimashi;
}

uint32_t QGramIndex::hashNext(const uint32_t prev_hash, const char new_pos) const
{
    unsigned mask = ~0 << 2*this -> q;      //invert mask and shift 2 * q positions
    return ~mask & (prev_hash << 2 | ordValue(new_pos));    //eleminate unnecessary positions and set new bits
}
