#pragma once

template <typename T>
class EMAFilter {
  public:
    T level = T{};
    const float alpha;
    const float alpha2;
    const T threshold;

    EMAFilter(float smoothingFactor, T thresholdValue);
    EMAFilter(float alphaHigh, float alphaLow, T thresholdValue);
    void calculate(T input);
    void reset();
    bool aboveThreshold ();
};

// ----------------------------------------------------- Objects -----------------------------------------------------

extern EMAFilter<float> voltage_ema;
