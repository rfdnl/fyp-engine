#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <AL/alut.h>
#include <iostream>
#include <map>
#include "ILoggable.hpp"


class Audio : public ILoggable
{
	ALboolean enumeration;
	const ALCchar *devices;
	const ALchar *defaultDeviceName;
    ALCdevice* device;
    ALCcontext* context;
	std::map<std::string, ALuint> buffers;
	std::map<std::string, ALuint> sources;
    ALfloat listenerOri[];

    bool CreateContext();
    bool OpenDevice(const ALCchar* deviceName);
	void GetDefaultDeviceName();
    bool EnumerateDevice();
    void InitListener();
	bool CheckAlError(std::string functionName, int line = -1, std::string filename = "NONE", std::string comment = "NONE");
    static void RetrieveDeviceList(const ALchar* devices);
    static ALenum ToALformat(short channels, short samples);
    bool IsError();
public:
    Audio(std::shared_ptr<Logger> logPtr):
        ILoggable(logPtr, "Audio"),
        listenerOri{ 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f }
	{}
	bool Initialize();
	void NewSource(std::string sourceKey);
    bool NewBuffer(std::string audioKey, const char* filePath);
	void Play(std::string sourceKey, std::string audioKey);
	bool CanPlay(std::string sourceKey);
	void End();
};

#endif // AUDIO_HPP
