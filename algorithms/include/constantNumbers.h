#ifndef CONSTANTNUMBERS_H
#define CONSTANTNUMBERS_H





/*
 ** Collection of constant numbers
 * */



namespace math_const
{
    const double m_pi = 3.141592654;



    float sqrtFast(float num)
    {
        unsigned int i = *(unsigned int*) &num;

        i  += 127 << 23;

        i >>= 1;
        return *(float*) &i;
    };

}














#endif // CONSTANTNUMBERS_H




