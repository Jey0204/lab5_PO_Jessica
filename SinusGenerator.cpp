#define _USE_MATH_DEFINES
#include "SinusGenerator.h"

SinusGenerator::SinusGenerator(SygnalGenerator *dekorowanySygnal, double amplituda, double czestotliwosc)
    : SygnalDekorator(dekorowanySygnal), m_amplituda(amplituda), m_czestotliwosc(czestotliwosc)
{
    // Zakładamy częstotliwość próbkowania 1000 Hz
    double fs = 1000.0;
    m_omega = 2.0 * M_PI * m_czestotliwosc / fs;

    // Poprawna inicjalizacja dla algorytmu różnicowego
    m_x1 = 0.0;
    m_x2 = m_amplituda * sin(m_omega);
}

double SinusGenerator::generuj(double t)
{
    return m_amplituda * sin(2 * 3.14159 * m_czestotliwosc * t);
}
