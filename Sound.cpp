#include <AL\al.h>
#include <AL\alc.h>
#include <AL\alut.h>
#include <stdio.h>
#include "Sound.h"

//file name
#define FILENAME "sounds/hyrule_field.wav"

void Sound::playSound(){
	
	ALuint buffer, source;
	ALint state;

	//init the environment
	alutInit(0,NULL);

	//error capture
	alGetError();

	//load pcm data into buffer
	buffer = alutCreateBufferFromFile(FILENAME);

	//create source, use buffer to fill it
	alGenSources(1,&source);
	alSourcei(source, AL_BUFFER, buffer);

	//play sound
	alSourcePlay(source);

	//wait till song is over
//	do{
//		alGetSourcei(source, AL_SOURCE_STATE, &state);
//	}while (state = AL_PLAYING);

	//clean up
//	alDeleteSources(1,&source);
//	alDeleteBuffers(1,&buffer);

//	alutExit();
}