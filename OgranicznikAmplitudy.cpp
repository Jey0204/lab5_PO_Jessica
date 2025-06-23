#include "OgranicznikAmplitudy.h"

OgranicznikAmplitudy::OgranicznikAmplitudy(SygnalGenerator *dekorowanySygnal, double limit)
    : SygnalDekorator(dekorowanySygnal)
{
    if (limit < 0)
        limit = -limit;
    m_limitGowny = limit;
    m_limitDolny = -limit;
}

double OgranicznikAmplitudy::generuj(double t)
{
    double wartosc = SygnalDekorator::generuj(t);
    if (wartosc > m_limitGowny)
        return m_limitGowny;
    if (wartosc < m_limitDolny)
        return m_limitDolny;
    return wartosc;
}
