#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <sys/ioctl.h>
#include <cstdio>
#include <unistd.h>

class Options {
public:
    enum Mode { TEXT, HEX };

public:
    Options() : m_mode(HEX), m_skip(0) {}

    Mode mode() const { return m_mode; }
    void mode(Mode m) { m_mode = m; }

    //int length() const { return m_length; }
    //void length( int l) { m_length = l; }

    int skip() const { return m_skip; }
    void skip( int s) { m_skip = s; }

    const std::string & search() const { return m_search; }
    void search( const std::string & p) { m_search = p; }

    size_t width() {
        struct winsize w = {0};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        if (w.ws_col < 17) return 0;

        size_t termW = (w.ws_col - 13) / 4;

        if ( termW >= 16) return  termW / 16 * 16;
        if ( termW >=  4) return  termW /  4 *  4;
        return termW;
    }

private:
    std::string m_search;
    Mode m_mode;
    int m_skip;
};

#endif
