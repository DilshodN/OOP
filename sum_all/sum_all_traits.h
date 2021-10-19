#pragma once

class A{
    int k;
public:
    explicit A(int l) : k(l){};
    A& operator+=(const A& rhs){
        k += rhs.k;
        return *this;
    }
};

template<typename T>
class SumAllTraits;

template<>
class SumAllTraits<std::string>
{
public:
    using SumType = std::string;
};

// CHAR

template<>
class SumAllTraits<char>
{
public:
    using SumType = std::string;
};

template<>
class SumAllTraits<signed char>
{
public:
    using SumType = std::string;
};

template<>
class SumAllTraits<unsigned char>
{
public:
    using SumType = std::string;
};

// SHORT

template<>
class SumAllTraits<short>
{
public:
    using SumType = int;
};

template<>
class SumAllTraits<unsigned short>
{
public:
    using SumType = unsigned int;
};

// INT

template<>
class SumAllTraits<int>
{
public:
    using SumType = long;
};

template<>
class SumAllTraits<unsigned int>
{
public:
    using SumType = unsigned long;
};

// LONG

template<>
class SumAllTraits<long>
{
public:
    using SumType = long long;
};

template<>
class SumAllTraits<unsigned long>
{
public:
    using SumType = unsigned long long;
};

// LONG LONG

template<>
class SumAllTraits<long long>
{
public:
    using SumType = long long;
};

template<>
class SumAllTraits<unsigned long long>
{
public:
    using SumType = unsigned long long;
};

// FLOAT, DOUBLE, LONG DOUBLE

template<>
class SumAllTraits<float>
{
public:
    using SumType = double;
};

template<>
class SumAllTraits<double>
{
public:
    using SumType = long double;
};

