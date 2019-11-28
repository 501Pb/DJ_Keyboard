#include "Recording.h"

// writes the recorded audio data into a .WAV file
void writeWaveFile(const char* filename, SAudioStreamFormat format, void* data)
{	
	if (!data)
	{
		printf("Could not save recorded data to %s, nothing recorded\n", filename);
		return;
	}

	FILE* file = fopen(filename, "wb");

	if (file)
	{
		// write wave header 
		unsigned short formatType =	1;
		unsigned short numChannels = format.ChannelCount;
		unsigned long  sampleRate =	format.SampleRate;
		unsigned short bitsPerChannel = format.getSampleSize() * 8;
		unsigned short bytesPerSample = format.getFrameSize() ;
		unsigned long  bytesPerSecond = format.getBytesPerSecond();
		unsigned long  dataLen = format.getSampleDataSize();
			
		const int fmtChunkLen = 16;
		const int waveHeaderLen = 4 + 8 + fmtChunkLen + 8;

		unsigned long totalLen = waveHeaderLen + dataLen;

		fwrite("RIFF", 4, 1, file);
		fwrite(&totalLen, 4, 1, file);
		fwrite("WAVE", 4, 1, file);
		fwrite("fmt ", 4, 1, file);
		fwrite(&fmtChunkLen, 4, 1, file);
		fwrite(&formatType, 2, 1, file);
		fwrite(&numChannels, 2, 1, file);
		fwrite(&sampleRate, 4, 1, file);
		fwrite(&bytesPerSecond, 4, 1, file);
		fwrite(&bytesPerSample, 2, 1, file);
		fwrite(&bitsPerChannel, 2, 1, file);

		// write data
		fwrite("data", 4, 1, file);
		fwrite(&dataLen, 4, 1, file);
		fwrite(data, dataLen, 1, file);

		// finish
		fclose(file);
	}
	else
		printf("Could not open %s to write audio data\n", filename);
}

void Record(game_status* status, string * filename)
{
	ISoundEngine* engine = createIrrKlangDevice();
	IAudioRecorder* recorder = createIrrKlangAudioRecorder(engine, ESOD_DIRECT_SOUND);

	if (!engine || !recorder)
	{
		printf("Could not create audio engine or audio recoder\n");
		return ;
	}

	if (access("../saveMusic", 0) == -1)
		mkdir("../saveMusic");

	while (*status == game_status::Init)
		Sleep(SLEEPTIME);

	while (*status != game_status::End)
	{
		// start recording
		recorder->startRecordingBufferedAudio();

		while (*status == game_status::Start)
			Sleep(SLEEPTIME);

		// stop recording
		recorder->stopRecordingAudio();

		// save recording
		writeWaveFile(("../saveMusic/" + *filename + ".wav").c_str(), recorder->getAudioFormat(), recorder->getRecordedAudioData());

		while (*status == game_status::GameOver)
			Sleep(SLEEPTIME);
	}

	return;
}