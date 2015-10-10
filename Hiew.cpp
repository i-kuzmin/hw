#include "Hiew.h"

#include <iomanip>
#include <cstdint>
#include <vector>

const char * const Hiew::m_trans [] = {
    u8" ",  u8"☺",  u8"☻",  u8"♥",  u8"♦",  u8"♣",  u8"♠",  u8"•",
    u8"◘",  u8"○",  u8"◙",  u8"♂",  u8"♀",  u8"♪",  u8"♫",  u8"☼",
    u8"►",  u8"◄",  u8"↕",  u8"‼",  u8"¶",  u8"§",  u8"▬",  u8"↨",
    u8"↑",  u8"↓",  u8"→",  u8"←",  u8"∟",  u8"↔",  u8"▲",  u8"▼",
    u8" ",  u8"!",  u8"\"", u8"#",  u8"$",  u8"%",  u8"&",  u8"'",
    u8"(",  u8")",  u8"*",  u8"+",  u8",",  u8"-",  u8".",  u8"/",
    u8"0",  u8"1",  u8"2",  u8"3",  u8"4",  u8"5",  u8"6",  u8"7",
    u8"8",  u8"9",  u8":",  u8";",  u8"<",  u8"=",  u8">",  u8"?",
    u8"@",  u8"A",  u8"B",  u8"C",  u8"D",  u8"E",  u8"F",  u8"G",
    u8"H",  u8"I",  u8"J",  u8"K",  u8"L",  u8"M",  u8"N",  u8"O",
    u8"P",  u8"Q",  u8"R",  u8"S",  u8"T",  u8"U",  u8"V",  u8"W",
    u8"X",  u8"Y",  u8"Z",  u8"[",  u8"\\", u8"]",  u8"^",  u8"_",
    u8"`",  u8"a",  u8"b",  u8"c",  u8"d",  u8"e",  u8"f",  u8"g",
    u8"h",  u8"i",  u8"j",  u8"k",  u8"l",  u8"m",  u8"n",  u8"o",
    u8"p",  u8"q",  u8"r",  u8"s",  u8"t",  u8"u",  u8"v",  u8"w",
    u8"x",  u8"y",  u8"z",  u8"{",  u8"|",  u8"}",  u8"~",  u8"⌂",
    u8"А",  u8"Б",  u8"В",  u8"Г",  u8"Д",  u8"Е",  u8"Ж",  u8"З",
    u8"И",  u8"Й",  u8"К",  u8"Л",  u8"М",  u8"Н",  u8"О",  u8"П",
    u8"Р",  u8"С",  u8"Т",  u8"У",  u8"Ф",  u8"Х",  u8"Ц",  u8"Ч",
    u8"Ш",  u8"Щ",  u8"Ъ",  u8"Ы",  u8"Ь",  u8"Э",  u8"Ю",  u8"Я",
    u8"а",  u8"б",  u8"в",  u8"г",  u8"д",  u8"е",  u8"ж",  u8"з",
    u8"и",  u8"й",  u8"к",  u8"л",  u8"м",  u8"н",  u8"о",  u8"п",
    u8"░",  u8"▒",  u8"▓",  u8"│",  u8"┤",  u8"╡",  u8"╢",  u8"╖",
    u8"╕",  u8"╣",  u8"║",  u8"╗",  u8"╝",  u8"╜",  u8"╛",  u8"┐",
    u8"└",  u8"┴",  u8"┬",  u8"├",  u8"─",  u8"┼",  u8"╞",  u8"╟",
    u8"╚",  u8"╔",  u8"╩",  u8"╦",  u8"╠",  u8"═",  u8"╬",  u8"╧",
    u8"╨",  u8"╤",  u8"╥",  u8"╙",  u8"╘",  u8"╒",  u8"╓",  u8"╫",
    u8"╪",  u8"┘",  u8"┌",  u8"█",  u8"▄",  u8"▌",  u8"▐",  u8"▀",
    u8"р",  u8"с",  u8"т",  u8"у",  u8"ф",  u8"х",  u8"ц",  u8"ч",
    u8"ш",  u8"щ",  u8"ъ",  u8"ы",  u8"ь",  u8"э",  u8"ю",  u8"я",
    u8"Ё",  u8"ё",  u8"Є",  u8"є",  u8"Ї",  u8"ї",  u8"Ў",  u8"ў",
    u8"°",  u8"∙",  u8"·",  u8"√",  u8"№",  u8"¤",  u8"■",  u8" "
};

void Hiew::hex( std::istream& in)
{
    using std::hex;
    using std::uppercase;
    using std::setfill;
    using std::setw;
    using std::endl;

    std::vector<char> line(m_width);

    size_t offset = 0;

    while ( in.read(line.data(), line.size()) || in.gcount()) {
        size_t n = in.gcount();
        // hexadecimal output
        m_out << hex << setfill('0') << setw(8) << offset << ":  ";
        for (int i = 0; i < line.size(); ++i) {
            if ( i < n) {
                uint8_t c = line[i];
                m_out << setw(2) << setfill('0') << hex << uppercase
                      << (int) c;

            } else {
                m_out << "  ";
            }

            if      ( i == line.size() - 1) m_out << "  ";
            else if ( i % 4 == 3)           m_out << '-';
            else                            m_out << ' ';
        }

        // characters output
        for (int i = 0; i < n; ++i) {
            uint8_t c = line[i];
            m_out << m_trans[ c];
        }
        m_out << endl;
        offset += n;
    }
}

void Hiew::text( std::istream& in)
{
    using std::endl;
    int n;
    char line[256];
    while ( ( n =  in.readsome(line, sizeof(line)))) {
        uint8_t c = 0;
        uint8_t lc = 0;
        for ( int i = 0; i < n; ++i) {
            lc = c;
            c = line[i];

            switch ( m_lineFeed) {
                case   CR: if ( c  == '\n') { m_out << endl; continue; } break;
                case   LF: if ( c  == '\r') { m_out << endl; continue; } break;
                case  NLL: if ( c  == '\0') { m_out << endl; continue; } break;
                case CRLF:
                    if      ( c  == '\n' && lc == '\r') { m_out << endl; continue;}
                    else if ( lc == '\r')               { m_out << m_trans['\r']; }

                    if      ( c  == '\r')               { continue; }
                    break;
            }
            m_out << m_trans[ c];
        }
    }
}
