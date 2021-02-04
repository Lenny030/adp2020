#include "QGramIndex.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Provide 2 main arguments: <text> <query> \n";
        return -1;
    }

    //read file
    std::string line, data;
    std::ifstream f (argv[1], std::ifstream::in);
    if(f.is_open())
    {
        while(getline(f, line)) data.append(line);

        f.close();
    }
    
    //construct QGramIndex and check hits for query
    std::string query {argv[2]};
    uint8_t k = query.size(); 
    QGramIndex qi {data, k};
    std::vector<uint32_t> h = qi.getHits(qi.hash(query));

    for(const auto e : query) std::cout << e;
    std::cout << ": "; 
    for(const auto e : h) std::cout << e << ' ';
    std::cout << std::endl;

    return 0;
}
