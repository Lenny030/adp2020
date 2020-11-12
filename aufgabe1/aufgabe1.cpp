//
// Created by tigerlili on 03.11.20.
//

#include "aufgabe1.hpp"
#include <iostream>
#include <fstream>

//string and utility included in hpp

//returns complement of {A,C,G,T}, otherwise 0 
char complement(char const x){

    switch(x) {
        case 'A':
            return 'T';
        case 'C':
            return 'G';
        case 'G':
            return 'C';
        case 'T':
            return 'A';
        default:
            return '0'; 
    }
}

//reads the givin string backwards and push_backs the complement of each char
std::string reverseComplement(std::string const& input){

    std::string rev {};

    for(int i = input.length()-1; i >= 0; --i)
    {
        rev.push_back(complement(input.at(i)));
    }
return rev;
}
            
std::pair<std::string, std::string> readFasta(std::string const& in_file){

    std::string line, meta, seq;
    std::ifstream f (in_file, std::ifstream::in);           //in flag = file open for reading

    //as long as the file is open keep getting lines and append them to the correspoding string
    if (f.is_open())
    {
        while(getline(f, line))
        {
            if(line[0] == '>' || line[0] == ';'){
                meta.append(line);
            }
            else {seq.append(line);}
        }
        f.close();
        return std::pair<std::string, std::string> (meta, seq);
    } else {
        return std::pair<std::string, std::string> ("","");
    }
}

bool writeFasta(std::string const& out_file,
                std::string const& meta,
                std::string const& seq) {

    std::ofstream f;
    f.open(out_file, std::ofstream::out);   //file open for writing

    //if its open and writable then ... return true
    if (f.is_open())
    {
        //meta output
        f << meta << std::endl;
        //splitting the seq into 80 char long lines
        for(u_int32_t i {}; i < seq.size(); i+=80) {
            std::string temp = seq.substr(i, 80);
            f << temp << std::endl;
        }
        f.close();
        return true;
    }
    return false;
}

bool reverseComplementFASTA(std::string const& input_file,
                            std::string const& output_file){

    std::pair<std::string, std::string> yeet {readFasta(input_file)};
    //returns false, if elements of tuple are empty, otherwise true
    if(yeet.first == "" && yeet.second == "") {return false;} 
    return writeFasta(output_file, yeet.first, (reverseComplement(yeet.second)));
}
