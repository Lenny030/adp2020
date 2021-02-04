#include "BLAST_Neighborhood.hpp"
#include <omp.h>
#include "a4_util.h"
std::vector<NHResult> BLAST_Neighborhood::generateNeighborhood( const std::string& query,
                                                                const ScoreMatrix& matrix,
                                                                const int word_size,
                                                                const int score_threshold,
                                                                const int threads)

{
    // w > |q|
    if(word_size > query.size()) { return std::vector<NHResult> {}; }
    if(word_size < 1 || threads < 1 ) { throw std::invalid_argument("word_size / thread > 0"); } 

    //generate k-meres
    std::vector<NHResult> n {};
    std::vector<std::pair<std::string, int>> neighbors = {}; 

    for(uint32_t i {}; i+word_size <= query.length(); ++i)
    {
        NHResult tmp {query.substr(i, word_size), neighbors}; 
        n.push_back(tmp);
    }
    //generate neighbors for each infix 
    int sc {};
    //rather ugly data_structure for now: each infix in n has its own vector of vectors
    std::vector<std::vector<std::vector<int>>> scores {};
    std::vector<std::vector<int>> infix_scores {};
    std::vector<int> tmp {};

    for(uint32_t i = 0; i < n.size(); ++i)
    {
        //computes all scores for each element in infix
        for(int32_t j {}; j < word_size; ++j)
        {
            //for each element in infix a vector with all scores of our alphabet
            for(uint32_t k {}; k < TranslationTableAminoAcids::ALPHABET_SIZE; ++k)
            {
                sc = matrix.score(n[i].infix[j], TranslationTableAminoAcids::INT_TO_CHAR[k]);
                tmp.push_back(sc);
            }
            //clear old scores, for new element of infix
            infix_scores.push_back(tmp);
            tmp.clear();
        }
        //scores is needed for parallel solution
        scores.push_back(infix_scores);
        //clear vector of vectors for new infix
        infix_scores.clear();
    }
    //get all permutation of scores and corresponding infix
    //if score >= score_threshold -> neighbor_infix & score are part of the n[i] struct...
    #pragma omp parallel num_threads(threads)
    #pragma omp for
        for(uint32_t i = 0; i < n.size(); ++i)
        {
            generatePermutations(scores[i], n[i], word_size, score_threshold);
        }
    return n;
}

void BLAST_Neighborhood::generatePermutations(const std::vector<std::vector<int>> & scores, 
                                              NHResult & n,
                                              const int word_size,
                                              const int score_threshold)
{
    //we know we have word_size rows, and TranslationTableAminoAcids::ALPHABET_SIZE (20) cols
    //we have to keep track of the position in each row, to translate it back to our neighbor 
    size_t max = std::pow(TranslationTableAminoAcids::ALPHABET_SIZE, word_size);  

    //we are treating this permutation-problem as a counting problem 
    //where the numbers are word_size long and each digit is a postion in our infix and 
    //each number a combination of our infix
    //heavy workload here -------------------------------------------------------------------
    for(size_t i {}; i < max; ++i)
    {
        size_t tmp = i;
        std::string neighbor {};
        int32_t tmp_sum {};
        for(int32_t j {}; j < word_size; ++j)
        {
            //we convert our numbers into digits where each digit is a index  
            int index = tmp % TranslationTableAminoAcids::ALPHABET_SIZE; 
            tmp /= TranslationTableAminoAcids::ALPHABET_SIZE;
            tmp_sum += scores[j][index];
            //keeping track of our neighbor-infix and corresponding score
            neighbor.push_back(TranslationTableAminoAcids::INT_TO_CHAR[index]);
        }
        if(tmp_sum >= score_threshold) n.neighbors.push_back(std::make_pair(neighbor, tmp_sum));
    }
    //neighbors are not sorted ... 
    std::sort(n.neighbors.begin(), n.neighbors.end());
}
