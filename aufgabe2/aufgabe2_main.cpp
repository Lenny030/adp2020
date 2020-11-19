#include<iostream>
#include"aufgabe2.cpp"

int main(int argc, char* argv[])
{

    if(argc == 2)
    {
        //modi1
        std::vector<uint32_t> junge {};
        std::string text (argv[1]);
        construct(junge, text);
        for(auto e : junge) std::cout << e << '\n';
        return 0;
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
