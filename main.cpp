#include "Hiew.h"
#include <sstream>
#include <iostream>


struct Options {
    enum Mode { TEXT, HEX };
public:
    Options() : m_mode(HEX) {}

    Mode mode() const { return m_mode; }
    void mode(Mode m) { m_mode = m; }

private:
    Mode m_mode;
};

int usage( int argc, char* argv[], int invArg ) {
    //TODO: print help message
    if ( invArg != 0) {
        std::cout << "Invalid";
        if ( invArg < argc) {
            std::cout << " \"" << argv[invArg] << "\"";
        }
        std::cout << "(argv[" << invArg << "]) argument.";
        return -1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    Hiew hiew;
    Options opt;

    for ( int i = 1; i < argc; ++i) {
        if ( std::string(argv[i]) == "-1") {
            opt.mode( Options::TEXT);
            continue;
        }

        if ( std::string(argv[i]) == "-2") {
            opt.mode( Options::HEX);
            continue;
        }

        if ( std::string(argv[i]) == "-lf" ) {
            hiew.line_feed(Hiew::LF);
        }

        if ( std::string(argv[i]) == "-cr" ) {
            hiew.line_feed(Hiew::CR);
        }

        if ( std::string(argv[i]) == "-null" ) {
            hiew.line_feed(Hiew::NLL);
        }

        if ( std::string(argv[i]) == "-crlf" ) {
            hiew.line_feed(Hiew::CRLF);
        }

        if ( std::string( argv[i]) == "-w") {
            if ( ++i < argc) {
                size_t width;
                std::istringstream iss( argv[i]);
                iss >> width;
                hiew.width( width);
                continue;
            }
            return usage(argc, argv, i);
        }


        std::ifstream in( argv[i], std::ios::binary);
        switch ( opt.mode()) {
            case Options::TEXT:
                hiew.text( in);
                break;

            case Options::HEX:
                hiew.hex( in);
                break;
        }

    }
}
