//
// Created by tigerlili on 03.11.20.
//

#include "aufgabe1.hpp"
#include <iostream>
#include <fstream>

char complement(char const x) {
    char lenny{};
    if (x == 'A') { lenny = 'T'; }
    else if (x == 'T') { lenny = 'A'; }
    else if (x == 'G') { lenny = 'C'; }
    else if (x == 'C') { lenny = 'G'; }
    else { std::cout << "Error: no dna base.\n"; }
    return lenny;
}


std::string reverseComplement(std::string const& input) {
    std::string output{};
    for (long i = input.length()-1; i >= 0; i--) {
        output.push_back(complement(input[i]));
    }
    return output;
}

std::pair<std::string, std::string> readFasta(std::string const& in_file) {
    std::string meta, seq{};


    std::ifstream myfile(in_file);
    //if (!myfile.good()) return std::pair<std::string, std::string> ("","");
    std::string line;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line[0] == '>' || line[0] == ';') {
                meta.append(line);
            }
            else {seq.append(line);}
        }
        myfile.close();
        return std::pair<std::string, std::string> (meta, seq);
    } else {
        return std::pair<std::string, std::string> ("","");
    }
}

bool writeFasta(std::string const& out_file,
                std::string const& meta,
                std::string const& seq) {

    /*std::ofstream myfile(out_file);
    if (!myfile.good()) {return false;}
    myfile << meta << '\n';
    uint16_t count{1};
    for(char elem : seq) {
        if (count == 81) {
            myfile << '\n';
            count = 1;
        }
        myfile << elem;
        count++;
    }*/

    std::ofstream myfile;
    myfile.open(out_file);
    if (!myfile.is_open()) {
        std::cout << "failed to open";
        return false;
    }
    else {
        myfile << meta << '\n';
        uint16_t count{1};
        for(char elem : seq) {
            if (count == 81) {
                myfile << '\n';
                count = 1;
            }
            myfile << elem;
            count++;
        }
        myfile.close();
        return true;
    }
    //return true;
}

bool reverseComplementFASTA(std::string const& input_file,
                            std::string const& output_file) {
    std::pair<std::string, std::string> lenny;
    lenny = readFasta(input_file);
    if(lenny.first.empty() && lenny.second.empty()) {return false;}
    std::string seq = reverseComplement(lenny.second);
    return writeFasta(output_file, lenny.first, seq);
}