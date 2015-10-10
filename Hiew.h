#ifndef __HIEW_H__
#define __HIEW_H__

#include <fstream>
#include <iostream>

class Hiew {
    class LineMerger;

public:
    enum LineFeed { LF, CR, CRLF, NLL };

    static const size_t WIDTH = 16;

public:
    Hiew(std::ostream& out = std::cout)
      : m_out( out), m_lineFeed( CRLF),
        m_width( WIDTH), m_maxLen( 0), m_mergeLines( true)
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
    void width( size_t w) { m_width = ( w ? w : WIDTH); }

    /**
     * Merge the same lines in hex mode output
     * @default true
     */
    void merge_lines( bool v) { m_mergeLines = v; }

    /**
     * Print at most *l* digits
     * @default 0 (no limit)
     */
    void max_len( size_t l) { m_maxLen = l; }

public:
    void hex( std::istream& in);
    void text( std::istream& in);

private:
    static const char * const m_trans[];

    std::ostream& m_out;
    LineFeed m_lineFeed;
    size_t m_width;
    size_t m_maxLen;
    bool m_mergeLines;
};

#endif
