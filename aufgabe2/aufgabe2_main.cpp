#include<iostream>
#include"aufgabe2.cpp"
#include<chrono>
#include<fstream>

int main(int argc, char* argv[])
{

    if(argc == 2)
    {
        //Reads fasta
        std::ifstream  is(argv[1]);
        if (!is.good())
        { // read file instead of treating as text
          std::cerr << "Cannot open file '" << argv[1] << "'\n";
          return 1;
        }

        std::string tmp, text;
        getline(is, tmp);  // header (optional)
        if (tmp[0] != '>') text = tmp;
        while (getline(is, tmp))
        {
          text += tmp;
        }
        std::cout << "read good \n" ;

        //starts computing
        std::vector<unsigned int> junge {};

        //modi1
        auto start = std::chrono::steady_clock::now();
        construct(junge, text);
        auto end = std::chrono::steady_clock::now();
        std::cout << "sa_size: " << junge.size() << "\n text_size: " << text.size() << std::endl;

        std::cout << "Elapsed time in milliseconds (smart) : "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;
        //modi1
        std::vector<unsigned int> junge0 {};
        auto start0 = std::chrono::steady_clock::now();
        construct_speed(junge0, text);
        auto end0 = std::chrono::steady_clock::now();

        std::cout << "Elapsed time in milliseconds (antons SPEEEEEEEEED : "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end0 - start0).count()
                  << " ms" << std::endl;
    }

    else if(argc >2)
    {
        //modi2
        return 0;
    }

    else
    {
        std::cout << "undefined input" << std::endl;
        return -1;
    }
}
