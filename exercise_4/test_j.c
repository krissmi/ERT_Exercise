#include <stdio.h>
#include <math.h>
#include <unistd.h>

#pragma clang diagnostic ignored "-Wunused-but-set-variable"

#define MAX(x, y) \
    ({  __typeof__ (x) _x = (x); \
        __typeof__ (y) _y = (y); \
        _x > _y ? _x : _y;       \
    })

// gcc -lm test_j.c -o test_j

double function_j(double f, double fp, double fptilde) 
{
  static double a   = 0.0081;
  static double aC  = 0.0317;
  static double saC = 0.0547;
  static double saX = 0.32;

  static double b   = 0.6;
  static double sbC = 0.0783;
  static double sbX = 0.16;

  static double g   = 9.807;
  static double gC  = 5.87;

  double fptildemin = (1.0 / 2.0 / M_PI) * pow((4.0 * b / 5.0), (1.0 / 4.0));

  double aX  = (log(a) - log(aC)) / log(fptildemin);
  double gX  = -log(gC) / log(fptildemin);

  double fpt = MAX(fptilde, fptildemin);

  double alpha   = aC  * pow(fpt, aX);
  double gamma   = gC  * pow(fpt, gX);
  double sigma_a = saC * pow(fpt, saX);
  double sigma_b = sbC * pow(fpt, sbX);

  double exp1arg = -1.25 * pow((f / fp), -4);
  double sigma   = (f <= fp) * sigma_a + (f > fp) * sigma_b;

  double exp2arg = -0.5 * pow((f - fp) / (sigma * fp), 2);

  double S = alpha * pow(g, 2) * pow((2 * M_PI), -4) * pow(f, -5) * exp(exp1arg) * pow(gamma, exp(exp2arg));

  return S;
}

int main(int argc, char *argv[]) 
{
  double S, f, fp, fptilde;

  for (f = -5.; f <= 5.; f += 0.01) {
    for (fp = 0.; fp <= 10.; fp += 0.01) {
      for (fptilde = 0.; fptilde <= 10.; fptilde += 0.01) {
        S = function_j(f, fp, fptilde);
      }
    }
  }

  return 0;
}

