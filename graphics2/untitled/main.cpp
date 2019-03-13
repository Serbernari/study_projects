#include <stdio.h>
#include <vector>
#include <array>
#include <cmath>

typedef std::vector<float> TPointList1D;
typedef std::vector<std::array<float,2>> TPointList2D;

// t is a value that goes from 0 to 1 to interpolate in a C1 continuous way across uniformly sampled data points.
// when t is 0, this will return B.  When t is 1, this will return C.
float CubicHermite (float A, float B, float C, float D, float t)
{
    float a = -A/2.0f + (3.0f*B)/2.0f - (3.0f*C)/2.0f + D/2.0f;
    float b = A - (5.0f*B)/2.0f + 2.0f*C - D / 2.0f;
    float c = -A/2.0f + C/2.0f;
    float d = B;

    return a*t*t*t + b*t*t + c*t + d;
}

template <typename T>
inline T GetIndexClamped(const std::vector<T>& points, int index)
{
    if (index < 0)
        return points[0];
    else if (index >= int(points.size()))
        return points.back();
    else
        return points[index];
}

int main (int argc, char **argv)
{
    printf("HI! HI!HI!HI!HI!HI!HI! \n");
    const float c_numSamples = 13;

    // show some 1d interpolated values
    {
        const TPointList1D points =
        {
            0.0f,
            1.6f,
            2.3f,
            3.5f,
            4.3f,
            5.9f,
            6.8f
        };

        printf("1d interpolated values.  y = f(t)n");
       for (int i = 0; i < c_numSamples; ++i)
        {
            float percent = ((float)i) / (float(c_numSamples - 1));
            float x = (points.size()-1) * percent;

            int index = int(x);
            float t = x - floor(x);
            float A = GetIndexClamped(points, index - 1);
            float B = GetIndexClamped(points, index + 0);
            float C = GetIndexClamped(points, index + 1);
            float D = GetIndexClamped(points, index + 2);

            float y = CubicHermite(A, B, C, D, t);
            printf("  Value at %0.2f = %0.2fn", x, y);
        }
        printf("n");
    }

    // show some 2d interpolated values
    {
        const TPointList2D points =
        {
            { 0.0f, 1.1f },
            { 1.6f, 8.3f },
            { 2.3f, 6.5f },
            { 3.5f, 4.7f },
            { 4.3f, 3.1f },
            { 5.9f, 7.5f },
            { 6.8f, 0.0f }
        };

        printf("2d interpolated values.  x = f(t), y = f(t)n");
        for (int i = 0; i < c_numSamples; ++i)
        {
            float percent = ((float)i) / (float(c_numSamples - 1));
            float x = 0.0f;
            float y = 0.0f;

            float tx = (points.size() -1) * percent;
            int index = int(tx);
            float t = tx - floor(tx);

            std::array<float, 2> A = GetIndexClamped(points, index - 1);
            std::array<float, 2> B = GetIndexClamped(points, index + 0);
            std::array<float, 2> C = GetIndexClamped(points, index + 1);
            std::array<float, 2> D = GetIndexClamped(points, index + 2);
            x = CubicHermite(A[0], B[0], C[0], D[0], t);
            y = CubicHermite(A[1], B[1], C[1], D[1], t);

            printf("  Value at %0.2f = (%0.2f, %0.2f)n", tx, x, y);
        }
        printf("n");
    }

   //  WaitForEnter();
    return 0;
}
