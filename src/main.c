#include <stdio.h>
#include <math.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cglm/vec3.h>
#include "portaudio.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>

#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (64)

#ifndef M_PI
#define M_PI  (3.14159265)
#endif


#define TABLE_SIZE   (200)
typedef struct
{
    float sine[TABLE_SIZE];
    int left_phase;
    int right_phase;
    char message[20];
}
paTestData;

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int patestCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData) {
    paTestData *data = (paTestData*)userData;
    float* out = (float*)outputBuffer;
    unsigned long i;

    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) inputBuffer;

    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = data->sine[data->left_phase];  /* left */
        *out++ = data->sine[data->right_phase];  /* right */

        data->left_phase += 1;
        if( data->left_phase >= TABLE_SIZE ) data->left_phase -= TABLE_SIZE;
        data->right_phase += 1; /* higher pitch so we can distinguish left and right. */
        if( data->right_phase >= TABLE_SIZE ) data->right_phase -= TABLE_SIZE;
    }

    return paContinue;
}

/*
 * This routine is called by portaudio when playback is done.
 */
static void StreamFinished(void* userData) {
    paTestData *data = (paTestData *) userData;
    printf( "Stream Completed: %s\n", data->message );
}

int Error(int err);

/*******************************************************************/
int main(void) {
    PaStreamParameters outputParameters;
    PaStream* stream;
    PaError err;
    paTestData data;

    int i;

    printf("PortAudio Test: output sine wave. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);

    /* initialise sinusoidal wavetable */
    for (i = 0; i < TABLE_SIZE; i++)
    {
        data.sine[i] = (float)sin(((double)i / (double)TABLE_SIZE) * M_PI * 2.);
    }

    data.left_phase = data.right_phase = 0;

    err = Pa_Initialize();
    if (err != paNoError) return Error(err);

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr, "Error: No default output device.\n");
        return Error(err);
    }

    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
        &stream,
        NULL, /* no input */
        &outputParameters,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,      /* we won't output out of range samples so don't bother clipping them */

        patestCallback,
        &data);

    if (err != paNoError) return Error(err);

    sprintf_s(data.message, 20, "No Message");

    err = Pa_SetStreamFinishedCallback(stream, &StreamFinished);
    if (err != paNoError) return Error(err);

    err = Pa_StartStream(stream);
    if (err != paNoError) return Error(err);

    while (Pa_IsStreamActive(stream)) {
		Pa_Sleep(100);
    }

    err = Pa_StopStream(stream);
    if (err != paNoError) return Error(err);

    err = Pa_CloseStream(stream);
    if (err != paNoError) return Error(err);

    Pa_Terminate();
    printf("Test finished.\n");

    return err;
}

int Error(int err) {
    Pa_Terminate();
    fprintf(stderr, "An error occurred while using the portaudio stream\n");
    fprintf(stderr, "Error number: %d\n", err);
    fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
    return err;
}
