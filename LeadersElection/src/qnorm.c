
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


double getInverseCDFValue(double p) {
    double a1 = -39.69683028665376;
    double a2 = 220.9460984245205;
    double a3 = -275.9285104469687;
    double a4 = 138.3577518672690;
    double a5 =-30.66479806614716;
    double a6 = 2.506628277459239;

    double b1 = -54.47609879822406;
    double b2 = 161.5858368580409;
    double b3 = -155.6989798598866;
    double b4 = 66.80131188771972;
    double b5 = -13.28068155288572;

    double c1 = -0.007784894002430293;
    double c2 = -0.3223964580411365;
    double c3 = -2.400758277161838;
    double c4 = -2.549732539343734;
    double c5 = 4.374664141464968;
    double c6 = 2.938163982698783;

    double d1 = 0.007784695709041462;
    double d2 = 0.3224671290700398;
    double d3 = 2.445134137142996;
    double d4 = 3.754408661907416;

    //Define break-points.

    double p_low =  0.02425;
    double p_high = 1 - p_low;
    long double  q, r, e, u;
    long double x = 0.0;


    //Rational approximation for lower region.

    if (0 < p && p < p_low) {
        q = sqrt(-2*log(p));
        x = (((((c1*q+c2)*q+c3)*q+c4)*q+c5)*q+c6) / ((((d1*q+d2)*q+d3)*q+d4)*q+1);
    }

    //Rational approximation for central region.

    if (p_low <= p && p <= p_high) {
        q = p - 0.5;
        r = q*q;
        x = (((((a1*r+a2)*r+a3)*r+a4)*r+a5)*r+a6)*q / (((((b1*r+b2)*r+b3)*r+b4)*r+b5)*r+1);
    }

    //Rational approximation for upper region.

    if (p_high < p && p < 1) {
        q = sqrt(-2*log(1-p));
        x = -(((((c1*q+c2)*q+c3)*q+c4)*q+c5)*q+c6) / ((((d1*q+d2)*q+d3)*q+d4)*q+1);
    }


    //Pseudo-code algorithm for refinement

    if(( 0 < p)&&(p < 1)){
        e = 0.5 * erfc(-x/sqrt(2)) - p;
        u = e * sqrt(2*M_PI) * exp(x*x/2);
        x = x - u/(1 + x*u/2);
    }


    double iCFDValue = x;
    return iCFDValue;

}