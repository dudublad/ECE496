#ifndef FFT_H
#define FFT_H

#include <QBuffer>
#include "fftw3.h"
#include "FileWvOut.h"
#include <Stk.h>

QVector<double> fft(QVector<double> in_wave);
std::vector<double> fft_v(std::vector<double> in_wave);

#endif // FFT_H
