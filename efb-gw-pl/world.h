// �������͍����@ WORLD by M. Morise
//
// FFTW���g���̂ŁC�ʓr�C���X�g�[�����K�v�ł��D
//

// ����ŕ������Ă���o�O
// decimateForF0 : �J�n����E�I���ԍ�4�T���v�����炢�Ɍ덷������܂��D

#include <fftw3.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define PI 3.1415926535897932384

// windows�Ȃ�ł�
#pragma warning( disable : 4996 )

#pragma comment(lib, "libfftw3-3.lib")
#pragma comment(lib, "libfftw3f-3.lib")
#pragma comment(lib, "libfftw3l-3.lib")
#define MAX_FFT_LENGTH 2048
#define FLOOR_F0 71.0
#define DEFAULT_F0 150.0
// 71�́Cfs: 44100�ɂ�����FFT����2048�ɂł��鉺���D
// 70 Hz�ɂ����4096�_�K�v�ɂȂ�D
// DEFAULT_F0�́C0.0.4�ł̐V�@�\�D�����̗]�n�͂��邪�C�b��I�Ɍ��肷��D

// F0����@ DIO : Distributed Inline-filter Operation
void dio(double *x, int xLen, int fs, double framePeriod, 
		 double *timeAxis, double *f0);
int getSamplesForDIO(int fs, int xLen, double framePeriod);

// �X�y�N�g�������@ STAR : Synchronous Technique and Adroit Restoration
int getFFTLengthForStar(int fs);
void star(double *x, int xLen, int fs, double *timeAxis, double *f0,
		  double **specgram);
void getMinimumPhaseSpectrum(double *inputSpec, fftw_complex *spectrum, fftw_complex *cepstrum, int fftl);

// ��������w�W����@ PLATINUM : ���̖���
void pt100(double *x, int xLen, int fs, double *timeAxis, double *f0,  
		 double **residualSpecgram);


// WORLD Synthesis
//void synthesis(double *f0, int tLen, double **specgram, double **residualSpecgram, int fftl, double framePeriod, int fs, 
//			   double *synthesisOut, int xLen);
void synthesisPt100(double *f0, int tLen, double **residualSpecgram, int fftl, double framePeriod, int fs, 
			   double *synthesisOut, int xLen);
void getMinimumPhaseSpectrum(double *inputSpec, fftw_complex *spectrum, fftw_complex *cepstrum, int fftl);

//------------------------------------------------------------------------------------
// Matlab �֐��̈ڐA
double std1(double *x, int xLen);
void inv(double **r, int n, double **invr);
void fftfilt(double *x, int xlen, double *h, int hlen, int fftl, double *y);
float randn(void);
void histc(double *x, int xLen, double *y, int yLen, int *index);
void interp1(double *t, double *y, int iLen, double *t1, int oLen, double *y1);
long decimateForF0(double *x, int xLen, double *y, int r);
void filterForDecimate(double *x, int xLen, double *y, int r);
int round1(double x);
void diff(double *x, int xLength, double *ans);
void interp1Q(double x, double shift, double *y, int xLength, double *xi, int xiLength, double *ans);

