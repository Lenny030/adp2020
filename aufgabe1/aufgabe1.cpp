#include "aufgabe1.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <sys/types.h>
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
            std::cout << "Wrong input \n";
            return 'X'; 
    }
}

std::string reverseComplement(std::string const& input){
    //cuz string is const, i use the reverseiterator from the header "iterator" 
    std::reverse_iterator<std::string::const_iterator> r = input.rbegin();
    std::string rev(r, input.rend());
    //building complement of reversed string
    for(u_int32_t i {}; i < rev.size(); ++i){
        char temp {rev[i]};
        rev[i] = complement(temp); 
    }
    return rev;
}

std::pair<std::string, std::string> readFasta(std::string const& in_file){

    std::string line, meta, seq;
    std::ifstream file (in_file);

    if (file.is_open()){
        while(getline(file, line)){
            if(line[0] == '>' || line[0] == ';'){
                meta.append(line);
            }
            else{
                seq.append(line);
            }
        }  
        return std::pair<std::string, std::string> (meta, seq);
    }
    else { 
        return std::pair<std::string, std::string> ("", "");
    }
}

bool writeFasta(std::string const& out_file,
                std::string const& meta,
                std::string const& seq){

    std::ofstream file;
    file.open(out_file);

    if (file.is_open()) {
        //meta output
        file << meta << std::endl;
        //splitting the seq into 80 char long lines
        for(u_int32_t i {}; i < seq.size(); i+=80) {
            std::string temp = seq.substr(i, 80);
            file << temp << std::endl;
        }
             
        file.close();
        return true;
    }
    else {
        return false;
    }
}

bool reverseComplementFASTA(std::string const& input_file,
                            std::string const& output_file){

    std::pair<std::string, std::string> yeet {readFasta(input_file)};
    if(yeet.first == "" && yeet.second == "") {return false;} 

    return writeFasta(output_file, yeet.first, (reverseComplement(yeet.second)));

}

