#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisySeed hw;
Flanger flanger;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = flanger.Process(in[0][i]);
		// out[1][i] = in[1][i];
	}
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAudio(AudioCallback);

    flanger.Init(hw.AudioSampleRate());
    flanger.SetLfoFreq(0.33f);
    flanger.SetLfoDepth(0.5f);
    flanger.SetFeedback(0.83f);
	while(1) {}
}
