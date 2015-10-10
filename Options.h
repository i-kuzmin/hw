#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <sys/ioctl.h>
#include <cstdio>
#include <unistd.h>

class Options {
public:
    enum Mode { TEXT, HEX };

public:
    Options() : m_mode(HEX) {}

    Mode mode() const { return m_mode; }
    void mode(Mode m) { m_mode = m; }

    size_t width() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return ((w.ws_col - 13) / 16) * 4;
    }

private:
    Mode m_mode;
};

#endif
