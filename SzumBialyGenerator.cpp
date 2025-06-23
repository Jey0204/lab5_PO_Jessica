#include "SzumBialyGenerator.h"
#include <chrono> // For seeding random generator

SzumBialyGenerator::SzumBialyGenerator(SygnalGenerator *dekorowanySygnal, double amplituda)
    : SygnalDekorator(dekorowanySygnal), m_amplituda(amplituda)
{
}

double SzumBialyGenerator::generuj(double t)
{
    double szum = (2.0 * (rand() / (RAND_MAX + 1.0)) - 1.0) * m_amplituda;
    return SygnalDekorator::generuj(t) + szum;
}
