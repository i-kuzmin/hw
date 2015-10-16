#ifndef __REGULAR_EXPRESSIONS_H__
#define __REGULAR_EXPRESSIONS_H__

#include <boost/regex.hpp>

#include <string>
#include <istream>
#include <deque>

class Re {
    typedef std::deque<char> Buffer;
    static const char TRANS[];

public:
    typedef std::map<unsigned, size_t> MatchList;

public:
    Re( const std::string& pattern)
      : m_pattern( pattern), m_offset(0)
    {}

    /**
     * Add data to re search.
     * @arg data - input addition;
     * @arg len  - input data len;
     * @arg list - matched strings;
     *
     * @return true in case of partial match.
     * (i.e. require additional data)
     */
    bool partial_match( const char * data, size_t len, MatchList& list) {
        reserve( 2 * len);
        for ( int i = 0; i < len; ++i) {
            uint8_t c = ((uint8_t *)data)[ i];
            m_buffer.push_back( ofrst(c));
            m_buffer.push_back( oscnd(c));
        }

        typedef boost::regex_iterator<
            std::deque<char>::const_iterator> dregex_iterator;

        dregex_iterator m( m_buffer.begin(), m_buffer.end(), m_pattern,
             boost::match_default | boost::match_partial);

        for (static dregex_iterator end; m != end; ++m) {
            if((*m)[0].matched == false) {
                // partial match.
                m_offset += std::distance( m_buffer.cbegin(), (*m)[0].first);
                m_buffer.erase( m_buffer.begin(), (*m)[0].first);
                return true;
            } else {
                // full match:
                size_t off = ( m_offset +
                        std::distance( m_buffer.cbegin(), (*m)[0].first)) / 2;
                list[off] = std::distance( (*m)[0].first, (*m)[0].second) / 2;
                        //std::string( (*m)[0].first, (*m)[0].second);
            }
        }

        m_offset += m_buffer.size();
        m_buffer.clear();
        return false;
    }

private:
    static inline char ofrst( const uint8_t b) {
        return TRANS[ b >> 4];
    }

    static inline char oscnd( const uint8_t b) {
        return TRANS[ b & 0xf];
    }

    void reserve( size_t len) {
        m_buffer.resize( m_buffer.size() + len);
        m_buffer.resize( len);
    }

private:
    boost::regex m_pattern;
    Buffer m_buffer;
    size_t m_offset;
};

void grep( std::istream& in, const std::string& pattern);

#endif
