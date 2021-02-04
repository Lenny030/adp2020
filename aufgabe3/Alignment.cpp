// global alignment with Needleman-Wunsch

#include "Alignment.hpp"

Alignment::Alignment(const std::string& _seq_v, const std::string& _seq_h)
    : seq_v(_seq_v), seq_h(_seq_h)
{
    //ist eig unnötig, aber espart schreibarbeit, ermöglicht verständis für den preis von ein bisschen speicher
    n = seq_v.size();
    m = seq_h.size();
}

void Alignment::compute(const int match, const int mismatch, const int gap, const bool local_align) {
    // wir machen unsere matritzen eine zeile und spalte größer für die initialisierung
    matrix.resize((n+1)*(m+1), 0);
    traceback.resize((n+1)*(m+1), Traceback::none);

    // solange die gap kosten kleiner null sind können wir uns das beim sw sparen
    if (!local_align) {
        // Initialisierung
        //erste Zeile
        int d = 0;
        for (uint32_t i = 0; i <= m; i++) {
            matrix.at(i) = d;
            if (i != 0) { traceback.at(i) = Traceback::horizontal; }
            d += gap;
        }

        //erste Spalte
        d = gap;
        for (uint32_t j = 1; j <= n; j++) {
            matrix.at((j * (m + 1)) + 0) = d;
            if (j != 0) { traceback.at((j * (m + 1)) + 0) = Traceback::vertikal; }
            d += gap;
        }
        k = m;
        l = n;
    }

    // Reccurrence
    int diagonal;       // F(i-1,j-1)
    int links;          // F(i-1, j)
    int oben;           // F(i,j-1)

    for (uint32_t j = 1; j <= n; j++) {
        for (uint32_t i = 1; i <= m; i++) {
            diagonal = matrix.at(((j - 1) * (m + 1)) + (i - 1));
            links= (matrix.at((j * (m + 1)) + (i - 1))) + gap;
            oben = (matrix.at(((j - 1) * (m + 1)) + i)) + gap;

            // s(x_i, y_j)
            if (seq_v.at(j - 1) == seq_h.at(i - 1)) { diagonal = diagonal + match; }
            else { diagonal = diagonal + mismatch; }

            // max der Drei, bei Gleichheit: diagonal, dann oben, dann links
            if (diagonal >= oben && diagonal >= links) {
                matrix.at((j * (m + 1)) + i) = diagonal;
                traceback.at((j * (m + 1)) + i) = Traceback::diagonal;
            }
            if (oben > diagonal && oben >= links) {
                matrix.at((j * (m + 1)) + i) = oben;
                traceback.at((j * (m + 1)) + i) = Traceback::vertikal;
            }
            if (links > diagonal && links > oben) {
                matrix.at((j * (m + 1)) + i) = links;
                traceback.at((j * (m + 1)) + i) = Traceback::horizontal;
            }

            if ((0 > diagonal) && (0 > oben) && (0 > links) && local_align) {
                // do nothing?
                matrix.at((j*(m+1))+i) = 0;
                traceback.at((j*(m+1))+i) = Traceback::none;
            }

            // speichern uns die Indizes für das Max für sw
            if (local_align && (matrix.at((j*(m+1))+i) > matrix.at((l*(m+1))+k))) {
                k = i;
                l = j;
                std::cout << "why?\n";
            }
        }
    }

    //print matrix
    for (uint32_t j = 0; j <= n; j++) {
        for (uint32_t i = 0; i <= m; i++) {
            std::cout << matrix.at((j*(m+1))+i);
            if (i == 15) {std::cout << '\n';}
        }
    }

}

int Alignment::score() const {
    // error wenn compute nicht davor aufgerufen wurde
    if (matrix.empty()) {
        throw std::runtime_error ("wer das liest ist doof");
    }
    // letzter(nw) oder höchster(sw) Eintrag
    return matrix.at(l*(m+1)+k);
}

void Alignment::getAlignment(std::string &a1, std::string &gaps, std::string &a2) const {
    // Error wenn compute nicht davor aufgerufen wurde
    if (matrix.empty()) {
        throw std::runtime_error ("compute wurde noch nicht aufgerufen");
    }

    // wir wollen den unsinn, der evtl noch in den strings ist nicht
    a1.clear();
    gaps.clear();
    a2.clear();

    //Traceback

    //starten beim letzten Eintrag
    uint32_t j = l;
    uint32_t i = k;

    //solange wir noch können gehen wir weiter
    while (traceback.at((j*(m+1))+i) != Traceback::none) {
        //wenn wir von der diagonalen kommen haben wir beide Buchstaben
        if (traceback.at((j*(m+1))+i) == Traceback::diagonal) {
            a1.push_back(seq_v.at(j-1));
            a2.push_back(seq_h.at(i-1));
            // wir müssen nur noch entschieden ob wir noch ein strich für ein match haben
            if (seq_v.at(j-1) == seq_h.at(i-1)) {
                gaps.push_back('|');
            }
            else {
                gaps.push_back(' ');
            }

            //damit gehen wir zur diagonalen
            j--;
            i--;
        }
        // wenn wir von oben kommen, gehen wir nur bei seq_v einen buchstaben weiter
        // bei seq_h wird der gap ausgegeben
        if (traceback.at((j*(m+1))+i) == Traceback::vertikal) {
            a1.push_back(seq_v.at(j-1));
            a2.push_back('-');
            gaps.push_back(' ');
            j--;
        }

        // wie bei oben nur umgedreht
        if (traceback.at((j*(m+1))+i) == Traceback::horizontal) {
            a1.push_back('-');
            a2.push_back(seq_h.at(i-1));
            gaps.push_back(' ');
            i--;
        }
    }

    // weil wir von hinten gekommen sind, müssen wir noch alles umdrehen
    std::reverse(a1.begin(), a1.end());
    std::reverse(gaps.begin(), gaps.end());
    std::reverse(a2.begin(), a2.end());

    // und dann wird endlich ausgegeben:)
    std::cout << a1 << '\n' << gaps << '\n' << a2 << '\n';
}
