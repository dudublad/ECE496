#include "fft.h"

/* Takes in wave, outputs frequency domain representation
 *
 * input: QVector<double> of size n
 * output: QVector<double> of size floor(n/2)+1
 *          out[0] = DC component, out[n/2+1] = sampling freq/2
*/
QVector<double> fft(QVector<double> in_wave){
    int in_size = in_wave.size();
    int out_size = floor(in_size/2)+1;

    double* mFftIn  = fftw_alloc_real(in_size);
    fftw_complex* mFftOut = fftw_alloc_complex(out_size);
    fftw_plan mFftPlan = fftw_plan_dft_r2c_1d(in_size, mFftIn, mFftOut, FFTW_PRESERVE_INPUT);

    //in_wave->mFftIn
    std::copy(in_wave.begin(), in_wave.end(), mFftIn);

    //execute FFT
    fftw_execute(mFftPlan);

    //Convert cplx output to magnitude, and copy into output vector
    QVector<double> out_wave(out_size);
    for(int i = 0; i < out_size; i++) {
        out_wave[i] = sqrt(pow(mFftOut[i][0],2) + pow(mFftOut[i][1],2));
    }

    //free allocated memory
    fftw_free(mFftIn);
    fftw_free(mFftOut);

    return out_wave;
}
