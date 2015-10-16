#include "Re.h"

#include <boost/regex.hpp>

#include <deque>
#include <vector>
#include <iostream>
#include <iterator>

const char Re::TRANS[] = "0123456789ABCDEF";
static size_t RAW_SIZE = 1024;

namespace /*auxilary*/ {

    const char g_trans[] = {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };

    inline char ofrst( const uint8_t b)
    { return g_trans[ b >> 4]; }

    inline char oscnd( const uint8_t b)
    { return g_trans[ b & 0xf]; }

}

void grep( std::istream& in, const std::string& pattern) {
    using boost::regex;
    regex e( pattern);

    char raw[RAW_SIZE];
    std::deque<char> bHex(2 * RAW_SIZE);
    bHex.clear();

    size_t offset = 0;

    while ( in.read(raw, sizeof(raw)) || in.gcount()) {
        int read = in.gcount();


        for ( int i = 0; i < read; ++i) {
            uint8_t c = raw[ i];
            bHex.push_back( ofrst(c));
            bHex.push_back( oscnd(c));
        }

        typedef boost::regex_iterator<
            std::deque<char>::const_iterator> dregex_iterator;

        dregex_iterator m( bHex.begin(), bHex.end(), e,
             boost::match_default | boost::match_partial);
        dregex_iterator end;

        bool hasPartialMatch = false;
        while( m != end) {
            if((*m)[0].matched == false) {
                // Partial match.
                offset += std::distance( bHex.cbegin(), (*m)[0].first) / 2;
                bHex.erase( bHex.begin(), (*m)[0].first);
                hasPartialMatch = true;
                break;
            } else {
                // full match:
                std::cout << "Full match: "
                          << offset + std::distance( bHex.cbegin(), (*m)[0].first) / 2
                          << " - " << std::distance( (*m)[0].first, (*m)[0].second) << std::endl;
                std::cout << std::string( (*m)[0].first, (*m)[0].second) << std::endl;
                std::cout << std::endl;
            }
            // move to next match:
            ++m;
        }
        if ( !hasPartialMatch) {
            offset += bHex.size() / 2;
            bHex.clear();
        }
    }
}
