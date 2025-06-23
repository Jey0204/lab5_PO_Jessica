#include "SygnalDekorator.h"

SygnalDekorator::SygnalDekorator(SygnalGenerator *dekorowanySygnal) : m_dekorowanySygnal(dekorowanySygnal) {}

SygnalDekorator::~SygnalDekorator()
{
    delete m_dekorowanySygnal;
}

double SygnalDekorator::generuj(double t)
{
    return m_dekorowanySygnal->generuj(t);
}

std::string SygnalDekorator::getType() const
{
    return m_dekorowanySygnal->getType();
}
