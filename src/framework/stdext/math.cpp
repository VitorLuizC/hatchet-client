/*
 * Copyright (c) 2010-2024 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <algorithm>
#include <climits>
#include <cmath>
#include <random>

#ifdef _MSC_VER
#pragma warning(disable:4267) // '?' : conversion from 'A' to 'B', possible loss of data
#endif

namespace stdext
{
    uint32_t adler32(const uint8_t* buffer, size_t size)
    {
        size_t a = 1, b = 0;
        while (size > 0) {
            size_t tlen = size > 5552 ? 5552 : size;
            size -= tlen;
            do {
                a += *buffer++;
                b += a;
            } while (--tlen);

            a %= 65521;
            b %= 65521;
        }
        return (b << 16) | a;
    }

    int random_range(const int min, const int max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution dis(0, INT_MAX);
        return min + (dis(gen) % (max - min + 1));
    }

    float random_range(const float min, const float max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float> dis(0.0, 1.0);
        return min + (max - min) * dis(gen);
    }

    std::mt19937& random_gen()
    {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        return generator;
    }

    bool random_bool(const double probability)
    {
        static std::bernoulli_distribution booleanRand;
        return booleanRand(random_gen(), std::bernoulli_distribution::param_type(probability));
    }

    int32_t normal_random(const int32_t minNumber, const int32_t maxNumber)
    {
        static std::normal_distribution normalRand(0.5f, 0.25f);

        float v;
        do {
            v = normalRand(random_gen());
        } while (v < 0.0 || v > 1.0);

        auto&& [a, b] = std::minmax(minNumber, maxNumber);
        return a + std::lround(v * (b - a));
    }
}