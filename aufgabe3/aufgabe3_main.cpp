#include "Alignment.hpp"


int main (int argc, char* argv[]) {
    if (argc == 3) {
        try {
            //erster Modus nur zwei sequenzen
            std::string seq_v = (argv[1]);
            std::string seq_h = (argv[2]);
            Alignment a (seq_v, seq_h);
            //a.compute(3,-1,-2);
            a.compute(3,-4,-6, false);
            std::string a1,gaps,a2;
            a.getAlignment(a1, gaps, a2);
            std::cout << "score: " << a.score() << '\n';
        }
        catch (...) {
            return 1;
        }
    }
    else if (argc == 6) {
        try {
            // zweiter Modus mit userdefinierten Match, Mismatch und Gap- Kosten
            std::string seq_v = (argv[1]);
            std::string seq_h = (argv[2]);
            Alignment a (seq_v, seq_h);
            int match = atoi((argv[3]));
            int mismatch = atoi((argv[4]));
            int gap = atoi((argv[5]));
            a.compute(match, mismatch, gap, false);
            std::string a1,gaps,a2;
            a.getAlignment(a1, gaps, a2);
            std::cout << "score: " << a.score() << '\n';
        }
        catch (...) {
            return 1;
        }
    }
    else if (argc == 7) {
        // Smith-Waterman
        try {
            // zweiter Modus mit userdefinierten Match, Mismatch und Gap- Kosten
            std::string seq_v = (argv[1]);
            std::string seq_h = (argv[2]);
            Alignment a (seq_v, seq_h);
            int match = atoi((argv[3]));
            int mismatch = atoi((argv[4]));
            int gap = atoi((argv[5]));
            a.compute(match, mismatch, gap, true;
            std::string a1,gaps,a2;
            a.getAlignment(a1, gaps, a2);
            std::cout << "score: " << a.score() << '\n';
        }
        catch (...) {
            return 1;
        }
    }
    else {
        std::cout << "error: undefined input in main\n";
        return 1;
    }
}

