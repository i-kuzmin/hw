#include "Hiew.h"
#include "Options.h"

#include <sstream>
#include <iostream>


int usage( int argc, char* argv[], int invArg ) {
    //TODO: print help message
    if ( invArg != 0) {
        std::cout << "Invalid ";
        if ( invArg < argc) {
            std::cout << "\"" << argv[invArg] << "\"";
        }
        std::cout << "(argv[" << invArg << "]) argument." << std::endl;
        return -1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    Hiew hiew;
    Options opt;
    hiew.width( opt.width());

    for ( int i = 1; i < argc; ++i) {
        std::string arg( argv[i]);
        if ( arg == "-1") {
            opt.mode( Options::TEXT);
            continue;
        }

        if ( arg == "-2") {
            opt.mode( Options::HEX);
            continue;
        }

        if ( arg == "-lf" ) {
            hiew.line_feed(Hiew::LF);
        }

        if ( arg == "-cr" ) {
            hiew.line_feed(Hiew::CR);
        }

        if ( arg == "-null" ) {
            hiew.line_feed(Hiew::NLL);
        }

        if ( arg == "-crlf" ) {
            hiew.line_feed(Hiew::CRLF);
        }

        if ( arg.compare( 0, 2, "-w") == 0) {
            std::string val;
            if (arg.length() > 2) {
                val = arg.substr(2);
            } else if ( ++i < argc) {
                val = argv[i];
            }
            int width = 0;
            std::istringstream iss(val);
            iss >> width;

            if ( width > 0) {
                hiew.width( width);
                continue;
            } return usage(argc, argv, i);
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
