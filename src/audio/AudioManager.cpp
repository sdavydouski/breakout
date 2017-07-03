#include "AudioManager.h"
#include "../utils/AudioFile.h"
#include "../FileManager.h"
#include <iostream>


AudioManager::AudioManager() {
    std::cout << "AudioManager constructor" << std::endl;
}

AudioManager::~AudioManager() {
    std::cout << "AudioManager destructor" << std::endl;
}

void AudioManager::startUp() {
    device_ = alcOpenDevice(nullptr);
    if (!device_) {
        std::cerr << "Cannot open sound device" << std::endl;
    }
    context_ = alcCreateContext(device_, nullptr);
    alcMakeContextCurrent(context_);
}

void AudioManager::shutDown() {
    for (auto& source: sources_) {
        alDeleteSources(1, &source.second.first);
        alDeleteBuffers(1, &source.second.second);
    }

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context_);
    alcCloseDevice(device_);
}

void AudioManager::createSource(const std::string& name, const std::string& path, bool isLooping) {
    AudioFile audioFile = FileManager::Instance().readOggFile(path);
    ALuint source, buffer;

    alGenSources(1, &source);
    alGenBuffers(1, &buffer);

    alBufferData(buffer, audioFile.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, 
        audioFile.data.get(), audioFile.getSampleCount() * sizeof(ALshort), audioFile.sampleRate);

    alSourcei(source, AL_BUFFER, buffer);
    alSourcei(source, AL_LOOPING, isLooping ? AL_TRUE : AL_FALSE);

    sources_[name] = std::make_pair(source, buffer);
}

void AudioManager::playSource(const std::string& name) {
    ALuint source = sources_[name].first;
    alSourcePlay(source);
}
