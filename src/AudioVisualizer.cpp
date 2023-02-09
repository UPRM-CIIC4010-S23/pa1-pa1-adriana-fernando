#include "AudioVisualizer.hpp"

/*
    This AudioVisualizer's class purpose is to process sound being played through Sound Players,
    and to give data useful to the visualization of the same.
*/

AudioVisualizer::AudioVisualizer() {
    bands = 64;
    for (int i = 0; i < 8192; i++) {
        fftSmooth.push_back(0);
    }
}

/*
    This function is constantly called to update the fftSmooth vector
    according to the sound being played, which is later used to
    calculate the amplitude.
*/
void AudioVisualizer::updateAmplitudes() {
    ofSoundUpdate();
    float *value = ofSoundGetSpectrum(bands);
    for (int i = 0; i < bands; i++) {
        fftSmooth[i] *= 0.9f;
        if (fftSmooth[i] < value[i]) {
            fftSmooth[i] = value[i];
        }
    }
}

// Setters
void AudioVisualizer::setBands(int bandsUpdate) {
    bands = bandsUpdate;
}

// Getters
int AudioVisualizer::getBands() {
    return bands;
}

/*
    When called, this function returns a vector of amplitudes.
    In the main function, these are what define the length of the bars.
*/
vector<float> AudioVisualizer::getAmplitudes() {
    vector<float> amplitudes;

    for (int i = 0; i < bands; i++) {
        amplitudes.push_back(fftSmooth[i] * -200);
    }

    return amplitudes;
}