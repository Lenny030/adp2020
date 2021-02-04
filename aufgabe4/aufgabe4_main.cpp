#include "BLAST_Neighborhood.hpp"
#include <omp.h> 

int main(int argc, char* argv[])
{
    if(argc != 6) { return -1; }

    else{
        //objects to call functions on
        BLAST_Neighborhood n {};
        ScoreMatrix s {};
        //std::stoi interpretes string to int, argv[1] = query
        int word_size {std::stoi(argv[3])};
        int score_threshold {std::stoi(argv[4])};
        int threads {std::stoi(argv[5])};
        //loading matrix
        s.load(argv[2]);

        //heavy computing-------------------------------------------------------
        auto start = omp_get_wtime();
        std::vector<NHResult> erg = n.generateNeighborhood (argv[1], s, word_size, score_threshold, threads);
        auto end = omp_get_wtime();

        //printing--------------------------------------------------------------
        for(u_int32_t i {}; i < erg.size(); ++i)
        {
            for(const auto & e : erg[i].infix) std::cout << e;
            std::cout << ":  ";
            for(const auto e : erg[i].neighbors){
                auto & [n, s] = e;
                std::cout << '(' << n << ',' << s << ')';
            }
            std::cout << '\n';
        }
        std::cout << "Estimated time : " << end - start << std::endl;
    }
}
