#include "Recording.h"

void Record(int *status)
{
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	irrklang::IAudioRecorder* recorder = irrklang::createIrrKlangAudioRecorder(engine);

	if (!engine || !recorder)
	{
		printf("Could not create audio engine or audio recoder\n");
		return 1;
	}

	// start recording
	recorder->startRecordingBufferedAudio();

	while(status != game_status::End)
	{
		Sleep(200);
	}

	// stop recording and save
	recorder->stopRecordingAudio();
	irrklang::writeWaveFile("music.wav", recorder->getAudioFormat(), recorder->getRecordedAudioData());

	return;
}