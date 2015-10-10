#ifndef __HIEW_H__
#define __HIEW_H__

#include <fstream>
#include <iostream>

class Hiew {
    class LineMerger;

public:
    enum LineFeed { LF, CR, CRLF, NLL };

public:
    Hiew(std::ostream& out = std::cout)
      : m_out( out), m_lineFeed( CRLF),
        m_width( 16), m_mergeLines( true)
    {}

    /**
     * Line Feed fro text mode output
     * @default CRLF
     */
    void line_feed( LineFeed lf) { m_lineFeed = lf; }

    /**
     * Output width for hex mode output
     * @default 16
     */
    void width( size_t w) { m_width = w; }

    /**
     * Merge the same lines in hex mode output
     * @default true
     */
    void merge_lines( bool v) { m_mergeLines = v; }

public:
    void hex( std::istream& in);
    void text( std::istream& in);

private:
    static const char * const m_trans[];

    std::ostream& m_out;
    LineFeed m_lineFeed;
    size_t m_width;
    bool m_mergeLines;
};

#endif
