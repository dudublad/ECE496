#ifndef GENERATEFIRCOEFF_H
#define GENERATEFIRCOEFF_H

#include <QBuffer>
#include <Stk.h>

QVector<double> generateFIRCoeff(double fc1, double fc2, std::string filter_type);
QVector<double> generateLPF(double fc, double fs);

#endif // GENERATEFIRCOEFF_H
