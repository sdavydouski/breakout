#include "AudioManager.h"
#include "AudioFile.h"
#include "../utils/FileManager.h"
#include <iostream>

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
    auto audioFile = FileManager::readOggFile(path);
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
    auto source = sources_[name].first;
    alSourcePlay(source);
}

void AudioManager::stopSource(const std::string& name) {
    auto source = sources_[name].first;
    alSourceStop(source);
}

void AudioManager::pauseSource(const std::string& name) {
    auto source = sources_[name].first;
    alSourcePause(source);
}
