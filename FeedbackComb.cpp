#include "FeedbackComb.h"
#include <math.h>
#include <stdexcept>

FeedbackComb::FeedbackComb() {}

FeedbackComb::FeedbackComb(float delay_time, float decay_time, float mul,
                           float samplingRate) {
    int ret;
    if ((ret = setup(delay_time, decay_time, mul, samplingRate)))
        throw std::runtime_error(
            "feedback comb: decay_time is less then delay_time");
}

int FeedbackComb::setup(float delay_time, float decay_time, float mul,
                        float samplingRate) {
    if (decay_time < delay_time) {
        return -1;
    }
    _mul = mul;
    _samplingRate = samplingRate;
    _delay_time = delay_time;
    _decay_time = _decay_time;
    _alpha = pow(0.001, delay_time / decay_time);
    _K = static_cast<int>(round(_samplingRate * delay_time));
    buf.resize(static_cast<int>(round(_samplingRate * delay_time + 2)));
    // initialize to 0
    for (unsigned i = 0; i < buf.size(); i++)
        buf.at(i) = 0;

    _i = buf.size();
    _j = buf.size() - _K;
    return 0;
}

void setDelay(float decay_time) {
    _delay_time = delay_time;
    _alpha = pow(0.001, delay_time / decay_time);
}

void setDecay(float decay_time) {
    _decay_time = decay_time;
    _alpha = pow(0.001, delay_time / decay_time);
}

float FeedbackComb::process(float input) {
    // store the current vlaue
    _i += 1;
    if (_i >= buf.size()) {
        _i = 0;
    }
    buf.at(_i) = input + (_alpha * buf.at(_i));

    // get the previous value
    _j += 1;
    if (_j >= buf.size()) {
        _j = 0;
    }
    return buf.at(_j) * _mul;
}
