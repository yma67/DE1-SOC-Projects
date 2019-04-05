#include "../inc/sound_util.h"
#include "../inc/wavetable.h"

const int SAMPLE_RATE = 48000;
const double NOTE_LOOKUP[] = {130.813, 146.832, 164.814, 174.614, 195.998, 220.000, 246.942, 261.626, 293.665, 329.628, 349.228, 391.995, 440.000, 493.883, 523.251};
const int NUM_NOTES = 15; 

void clear_ispressed(int is_pressed[]) {
	int i; 
	for (i = 0; i < NUM_NOTES; i++) is_pressed[i] = 0; 
}

double make_wave(int instant, double frequency) {
	int index = (int)(frequency * (double)instant) % SAMPLE_RATE;
	double interpolation = (double)(index - (int)index);
	double signals = (1.0 - interpolation) * (double)sine[(int)index] +
						   (interpolation) * (double)sine[(int)index + 1];
	return signals;
}

void synthesis_sound(double * signal, int is_pressed[], int * instance, int volume) {
	int i = 0, count_note = 0;
	double total = 0; 
	for (i = 0; i < NUM_NOTES; i++) {
		if (is_pressed[i]) {
			total = total + make_wave(*instance, NOTE_LOOKUP[i]);
			count_note = count_note + 1;
		}
	}
	if (count_note > 0) *signal = (total * volume) / (10 * count_note); 
	else *signal = 0.0;
    *instance = (*instance + 1) % 48000;
}
