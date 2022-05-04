#include <cstdlib>
#include <math.h>

#pragma once

class Saw {
  public:
    Saw(){};
    Saw(float fs) { setup(fs); }
    ~Saw(){};

    void setup(float fs);

    float process();
    float process(float frequency);
    void setFrequency(float frequency) { frequency_ = frequency; }
    void setPhase(float phase) { phase_ = phase; }
    void setAmp(float mul) { mul_ = mul / M_PI; }
    float getPhase() { return phase_; }
    float getFrequency() { return frequency_; }

  private:
    float phase_;
    float frequency_;
    float invSampleRate_;
    float mul_;
};
