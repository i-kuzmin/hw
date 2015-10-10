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

bool int_arg( int argc, char* argv[], int& i, const std::string& name, int & intVal)
{
    std::string arg(argv[i]);

    if ( arg.compare( 0, name.length(), name) != 0) { return false; }

    std::string val;

    if ( arg.length() > name.length()) {
        val = arg.substr( name.length());

    } else if ( ++i < argc) {
        val = argv[i];

    } else {
        std::exit( usage( argc, argv, i));
    }

    intVal = 0;
    std::istringstream iss(val);
    iss >> intVal;

    return true;
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

        if ( arg == "-v") {
            hiew.merge_lines( false);
        }

        int val;
        if ( int_arg( argc, argv, i, "-w", val)) {
            hiew.width( val);
        }

        if ( int_arg( argc, argv, i, "-s", val)) {
            opt.skip(val);
        }

        if ( int_arg( argc, argv, i, "-n", val)) {
            hiew.max_len( val);
        }

        std::ifstream in( argv[i], std::ios::binary);
        in.ignore( opt.skip());
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
