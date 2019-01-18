#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <AL/alut.h>
#include <iostream>
#include <map>
#include <vector>
#include "Helper/ILoggable.hpp"

class Audio : public ILoggable
{
	char enumeration;
	const char *devices;
	const char *defaultDeviceName;
    ALCdevice* device;
    ALCcontext* context;
	std::map<std::string, unsigned int> buffers;
	std::map<std::string, unsigned int> sources;
    std::vector<float> listenerOri;

	bool InitAlut();
    bool CreateContext();
    bool OpenDevice(const char* deviceName);
	void GetDefaultDeviceName();
    bool EnumerateDevice();
    void InitListener();
	bool CheckError(std::string functionName, int line = -1,
		std::string filename = "NONE",
		std::string comment = "NONE");
    static void RetrieveDeviceList(const char* devices);
    static int ToALformat(short channels, short samples);
    bool IsError();
public:
    Audio(std::shared_ptr<Logger> logPtr);
	bool Initialize();
	void NewSource(std::string sourceKey);
    bool NewBuffer(std::string audioKey, const char* filePath);
	void Play(std::string sourceKey, std::string audioKey);
	bool CanPlay(std::string sourceKey);
	void End();
};

#endif // AUDIO_HPP
