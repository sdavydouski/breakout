#pragma once

#include "../Singleton.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <map>
#include <string>

class AudioManager: public Singleton<AudioManager> {
public:
    void startUp();
    void shutDown();

    void createSource(const std::string& name, const std::string& path, bool isLooping);
    void playSource(const std::string& name);
    void stopSource(const std::string& name);
    void pauseSource(const std::string& name);
private:
    ALCdevice* device_;
    ALCcontext* context_;
    // key: <source, buffer>
    std::map<std::string, std::pair<ALuint, ALuint>> sources_;
};
