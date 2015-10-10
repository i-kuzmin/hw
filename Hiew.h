#ifndef __HIEW_H__
#define __HIEW_H__

#include <fstream>
#include <iostream>

class Hiew {
public:
    enum LineFeed { LF, CR, CRLF, NLL };

public:
    Hiew(std::ostream& out = std::cout)
      : m_out( out), m_lineFeed( CRLF), m_width( 16)
    {}

    void line_feed( LineFeed lf) { m_lineFeed = lf; }
    void width( size_t w) { m_width = w; }

public:
    void hex( std::istream& in);
    void text( std::istream& in);

private:
    static const char * const m_trans[];

    std::ostream& m_out;
    LineFeed m_lineFeed;
    size_t m_width;
};

#endif
