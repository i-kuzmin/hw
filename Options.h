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

    int length() const { return m_length; }
    void length( int l) { m_length = l; }

    int skip() const { return m_skip; }
    void skip( int s) { m_skip = s; }

    size_t width() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return ((w.ws_col - 13) / 16) * 4;
    }

private:
    Mode m_mode;
    int m_skip;
};

#endif
