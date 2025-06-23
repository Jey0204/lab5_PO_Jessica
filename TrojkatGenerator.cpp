#include "TrojkatGenerator.h"
#include <cmath>     // For fmod, fabs
#include <algorithm> // For std::min, std::max if needed

TrojkatGenerator::TrojkatGenerator(SygnalGenerator *dekorowanySygnal, double amplituda, double czestotliwosc, double wypelnienie)
    : SygnalDekorator(dekorowanySygnal), m_amplituda(amplituda), m_czestotliwosc(czestotliwosc), m_wypelnienie(wypelnienie), m_czas(0.0)
{
    if (m_czestotliwosc > 0)
    {
        m_okres = 1.0 / m_czestotliwosc;
    }
    else
    {
        m_okres = 0.0;
    }
    if (m_wypelnienie <= 0.0 || m_wypelnienie >= 1.0)
    {
        m_wypelnienie = 0.5;
    }
}

double TrojkatGenerator::generuj(double t)
{
    double okres = 1.0 / m_czestotliwosc;
    double czas_w_okresie = fmod(t, okres);
    double wartosc;
    if (czas_w_okresie < m_wypelnienie * okres) {
        wartosc = (2 * m_amplituda / (m_wypelnienie * okres)) * czas_w_okresie - m_amplituda;
    } else {
        wartosc = (-2 * m_amplituda / (okres * (1 - m_wypelnienie))) * (czas_w_okresie - m_wypelnienie*okres) + m_amplituda;
    }
    return SygnalDekorator::generuj(t) + wartosc;
}
