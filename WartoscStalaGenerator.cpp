#include "WartoscStalaGenerator.h"

WartoscStalaGenerator::WartoscStalaGenerator(double wartosc) : m_wartosc(wartosc) {}

double WartoscStalaGenerator::generuj(double t)
{
    return m_wartosc;
}
