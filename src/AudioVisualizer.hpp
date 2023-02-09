#pragma once

#include "ofMain.h"

class AudioVisualizer {

  private:
    vector<float> fftSmooth;
    int bands;

  public:
    AudioVisualizer();

    void setBands(int);

    vector<float> getAmplitudes();
    int getBands();

    void updateAmplitudes();
};