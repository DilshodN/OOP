#pragma once

#include <iostream>

class BmpModifyException : public std::exception{};

class BmpModifyArgsException final: public BmpModifyException{};
class BmpFileErrorException final: public BmpModifyException{};