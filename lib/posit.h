#ifndef __POSIT_H
#define __POSIT_H

#include <limits>
#include "posit_types.h"

class Posit {
private:
    POSIT_UTYPE mBits;
    int mNbits;
    int mEs;
    bool mNan;

    static int sDefaultNbits;
    static int sDefaultEs;

    Posit(POSIT_UTYPE bits, int nbits, int es, bool nan);
    Posit(int nbits, int es, bool nan);

public:
    static void setDefault(int nbits, int es);

    Posit();
    Posit(double v);
    Posit(int nbits, int es);
    Posit(int nbits, int es, double v);

    explicit operator float()  { return getFloat();  }
    explicit operator double() { return getDouble(); }

    bool isZero() const;                  // check for 0
    bool isOne() const;                   // check for +/- 1
    bool isInf() const;                   // check for +/- infinity
    bool isNeg() const;                   // check for negative
    bool isNan() const;                   // check for NaN

    int nbits() const;                    // size in bits
    int ss() const;                       // sign size in bits
    int rs() const;                       // regime size in bits
    int es() const;                       // exponent size in bits
    int fs() const;                       // fraction size in bits

    Posit zero() const;                   // 0
    Posit one() const;                    // 1
    Posit inf() const;                    // +/-inf
    Posit nan() const;                    // NaN
    Posit eps() const;

    Posit neg() const;                    // -x
    Posit rec() const;                    // /x

    Posit add(const Posit& p) const;      // x + p
    Posit sub(const Posit& p) const;      // x - p as x + -p
    Posit mul(const Posit& p) const;      // x * p
    Posit div(const Posit& p) const;      // x / p as x * /p

    bool eq(const Posit& p) const;        // x == p
    bool gt(const Posit& p) const;        // x > p
    bool ge(const Posit& p) const;        // x >= p
    bool lt(const Posit& p) const;        // x < p
    bool le(const Posit& p) const;        // x <= p

    void set(float n);                    // x = n
    void set(double n);                   // x = n

    float getFloat() const;               // n = x
    double getDouble() const;             // n = x

    // debug
    void setBits(POSIT_UTYPE bits);
    POSIT_UTYPE getBits();
    void print();
};

Posit operator+(const Posit& a, const Posit& b);
Posit operator-(const Posit& a, const Posit& b);
Posit operator*(const Posit& a, const Posit& b);
Posit operator/(const Posit& a, const Posit& b);

Posit& operator+=(Posit& a, const Posit& b);
Posit& operator-=(Posit& a, const Posit& b);
Posit& operator*=(Posit& a, const Posit& b);
Posit& operator/=(Posit& a, const Posit& b);

Posit operator-(const Posit& a);

bool operator<(const Posit&a , const Posit& b);
bool operator<=(const Posit&a , const Posit& b);
bool operator>(const Posit&a , const Posit& b);
bool operator>=(const Posit&a , const Posit& b);
bool operator==(const Posit&a , const Posit& b);
bool operator!=(const Posit&a , const Posit& b);


namespace std {
    // FIXME: Incomplete.
    template <> class numeric_limits<Posit>
    {
    public:
        static const bool is_specialized = true;
        static Posit min();
        static Posit max();
        static Posit lowest();
        static const int digits = -1;
        static const int digits10 = -1;
        static const int max_digits10 = -1;
        static const bool is_signed = true;
        static const bool is_integer = false;
        static const bool is_exact = false;
        static const int radix = 2;
        static Posit epsilon() { return Posit().eps(); }
        static Posit round_error();
        static const int min_exponent = -1;
        static const int min_exponent10 = -1;
        static const int max_exponent = -1;
        static const int max_exponent10 = -1;
        static const bool has_infinity = true;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_present;
        static const bool has_denorm_loss = false;
        static Posit infinity() { return Posit().inf(); }
        static Posit quiet_NaN();
        static Posit signaling_NaN();
        static Posit denorm_min();
        static const bool is_iec559 = false;
        static const bool is_bounded = false;
        static const bool is_modulo = false;
        static const bool traps = false;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_indeterminate;
    };

    Posit sqrt(Posit a);
}

#endif
