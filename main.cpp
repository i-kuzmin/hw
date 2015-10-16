#include "Hiew.h"
#include "Options.h"
#include "Re.h"

#include <sstream>
#include <iostream>

int usage( int argc, char* argv[], int invArg ) {
    std::cout << "NAME" << std::endl
              << "    " << argv[0] << " - hex dump tool, with hiew character set." << std::endl
              << std::endl
              << "SYNOPSIS" << std::endl
              << "    " << argv[0] << " [-1|-2|+<n>|-lf|-cr|-crlf|-null|-w<n>|-v] input ..." << std::endl
              << std::endl
              << "OPTIONS" << std::endl
              << "     -1    - text mode output;" << std::endl
              << "     -2    - hex mode output;" << std::endl
              << "     -v    - do not suppress duplicate lines;" << std::endl
              << "     +<n>  - skip first <n> bytes;" << std::endl
              << "     -cr   - use CR symbol for line delimiter in text mode;" << std::endl
              << "     -lf   - use LF symbol for line delimiter in text mode;" << std::endl
              << "     -null - use NULL symbol for line delimiter in text mode;" << std::endl
              << "     -clrf - use CR + LF symbols for line delimiter in text mode;" << std::endl
              << "     -h    - this help message." << std::endl;

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

    if ( argc == 1) return usage(argc, argv, 0);

    for ( int i = 1; i < argc; ++i) {
        std::string arg( argv[i]);
        if ( arg == "-1") {
            opt.mode( Options::TEXT);
            continue;
        }

        if ( arg ==  "-h") {
            return usage( argc, argv, 0);
        }

        if ( arg == "-2") {
            opt.mode( Options::HEX);
            continue;
        }

        if ( arg == "-lf" ) {
            hiew.line_feed(Hiew::LF);
            continue;
        }

        if ( arg == "-cr" ) {
            hiew.line_feed(Hiew::CR);
            continue;
        }

        if ( arg == "-null" ) {
            hiew.line_feed(Hiew::NLL);
            continue;
        }

        if ( arg == "-crlf" ) {
            hiew.line_feed(Hiew::CRLF);
            continue;
        }

        if ( arg == "-v") {
            hiew.merge_lines( false);
            continue;
        }

        if ( arg.compare(0 ,1, "/") == 0) {
            std::string val = arg.substr(1);
            opt.search(val);
            continue;
        }

        int val;
        if ( int_arg( argc, argv, i, "-w", val)) {
            hiew.width( val);
            continue;
        }

        if ( int_arg( argc, argv, i, "+", val)) {
            opt.skip(val);
            continue;
        }

        if ( int_arg( argc, argv, i, "-n", val)) {
            hiew.max_len( val);
            continue;
        }

        std::ifstream in( argv[i], std::ios::binary);
        in.ignore( opt.skip());

        //if ( !opt.search().empty()) {
        //    std::cout << '"' << opt.search() << '"';
        //    grep(in, opt.search());
        //    continue;
        //}

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
