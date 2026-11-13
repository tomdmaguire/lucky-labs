#pragma once

#include <cmath>
#include <numbers>

namespace lucky
{

/** ITU-R BS.1770 K-weighting for one channel: the high shelf then the high pass, at any sample rate.
    Square and sum its output for loudness. */
class KWeighting
{
public:
    void prepare (double sampleRate)
    {
        const auto pi = std::numbers::pi;
        {
            const auto f0 = 1681.974450955533, gainDb = 3.999843853973347, q = 0.7071752369554196;
            const auto k = std::tan (pi * f0 / sampleRate);
            const auto vh = std::pow (10.0, gainDb / 20.0);
            const auto vb = std::pow (vh, 0.4996667741545416);
            const auto a0 = 1.0 + k / q + k * k;
            shelf = { (vh + vb * k / q + k * k) / a0, 2.0 * (k * k - vh) / a0, (vh - vb * k / q + k * k) / a0,
                      2.0 * (k * k - 1.0) / a0, (1.0 - k / q + k * k) / a0 };
        }
        {
            const auto f0 = 38.13547087602444, q = 0.5003270373238773;
            const auto k = std::tan (pi * f0 / sampleRate);
            const auto a0 = 1.0 + k / q + k * k;
            highPass = { 1.0, -2.0, 1.0, 2.0 * (k * k - 1.0) / a0, (1.0 - k / q + k * k) / a0 };
        }
    }

    void reset() noexcept
    {
        shelf.z1 = shelf.z2 = highPass.z1 = highPass.z2 = 0.0;
    }

    double process (double x) noexcept { return highPass.process (shelf.process (x)); }

private:
    struct Biquad
    {
        double b0 = 1, b1 = 0, b2 = 0, a1 = 0, a2 = 0;
        double z1 = 0, z2 = 0;

        double process (double x) noexcept
        {
            const auto y = b0 * x + z1;
            z1 = b1 * x - a1 * y + z2;
            z2 = b2 * x - a2 * y;
            return y;
        }
    };

    Biquad shelf, highPass;
};

} // namespace lucky
