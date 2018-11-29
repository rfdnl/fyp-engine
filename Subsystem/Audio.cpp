#include "Audio.hpp"
#include <cstring>

bool Audio::Initialize(){
	if (!InitAlut()) return false;
	if (!EnumerateDevice()) return false;
	RetrieveDeviceList(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	GetDefaultDeviceName();
	OpenDevice(defaultDeviceName);
	CheckError("Initialize");
	InitListener();
	return CreateContext();
}

bool Audio::InitAlut(){
	if (!alutInitWithoutContext(NULL, NULL)) {
		CheckError("InitAlut");
		return false;
	}
	INFO("InitAlut - OK");
	return true;
}

bool Audio::EnumerateDevice(){
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if(enumeration == AL_FALSE){
		WARN("EnumerateDevice - FAIL");
		return false;
	}
	INFO("EnumerateDevice - OK");
	return true;
}

void Audio::RetrieveDeviceList(const ALchar* devices){
	const ALchar *device = devices, *next = devices + 1;
	size_t len = 0;
	std::cout << "Device list:" << std::endl;
	std::cout << "------------" << std::endl;
	while(device && *device != '\0' && next && *next != '\0'){
		std::cout << device << std::endl;
		len = strlen(device);
		device += (len+1);
		next += (len+2);
	}
	std::cout << "------------" << std::endl;
}

void Audio::GetDefaultDeviceName(){
	defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	if (!defaultDeviceName){
		ERROR("GetDefaultDeviceName - FAIL");
	} else {
		INFO(ss << "GetDefaultDeviceName: " << defaultDeviceName);
	}
}

bool Audio::OpenDevice(const ALCchar* deviceName){
	device = alcOpenDevice(deviceName);
	if (!device){
		ERROR("OpenDevice - FAIL");
		return false;
    }
    //device = alcOpenDevice("OpenAL Soft");
	INFO(ss << "OpenDevice: " << alcGetString(device, ALC_DEVICE_SPECIFIER));
	return true;
}

void Audio::InitListener(){
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, &listenerOri[0]);
}

bool Audio::CreateContext(){
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)){
		ERROR("CreateContext - FAIL");
		return false;
	}
	INFO("CreateContext - OK");
	return true;
}

// usage: RetrieveDeviceList(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
// Passsing NULL to alcGetString() indicates that
// we do not want the device specifier of a particular
// device, but all of them.
// The list of devices is organized as a string devices
// are separated with a NULL character and
// the list is terminated by two NULL characters
ALenum Audio::ToALformat(short channels, short bitdepth){
	bool stereo = (channels > 1);

	switch (bitdepth) {
	case 16:
		if (stereo)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
	default:
		return -1;
	}
}

bool Audio::CheckError(std::string functionName, int line, std::string filename, std::string comment){
	ALenum error = alutGetError();
	if (error != AL_NO_ERROR){
		ERROR(ss << functionName << ", filename: " << filename << ", line: " << line << ", error: " << alutGetErrorString(error) << ", comment: " << comment);
		return false;
	}
	return true;
}

// request new sound ID
void Audio::NewSource(std::string sourceKey){
	ALuint source;
	alGenSources((ALuint)1, &source);
	CheckError("NewSource (GenSaus)");
	alSourcef(source, AL_PITCH, 1);
	CheckError("NewSource (SetPtch)");
	alSourcef(source, AL_GAIN, 1);
	CheckError("NewSource (SetGain)");
	alSource3f(source, AL_POSITION, 0, 0, 0);
	CheckError("NewSource (SetPosi)");
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	CheckError("NewSource (SetVelo)");
	alSourcei(source, AL_LOOPING, AL_FALSE);
	CheckError("NewSource (SetLoop)");
	sources[sourceKey] = source;
}

bool Audio::NewBuffer(std::string audioKey, const char* filePath){
	ALuint buffer = alutCreateBufferFromFile(filePath);
	if (buffer == AL_NONE) {
		return CheckError("NewBuffer");
	}
	buffers[audioKey] = buffer;
	INFO(ss << "<" << filePath << "> loaded!");
	return true;
}

void Audio::Play(std::string sourceKey, std::string audioKey){
	alSourcei(sources[sourceKey], AL_BUFFER, buffers[audioKey]);
	CheckError("Play - Binding buffer");
	alSourcePlay(sources[sourceKey]);
	CheckError("Play - Playing source");
}

bool Audio::CanPlay(std::string sourceKey){
	ALint sourceState;
	alGetSourcei(sources[sourceKey], AL_SOURCE_STATE, &sourceState);
	CheckError("CanPlay - GetSource");
	return sourceState != AL_PLAYING;
}

void Audio::End(){
	//INFO(ss << "Clearing Sources: " << sources.size());
	/*
	for(std::map<std::string, ALuint>::iterator iter = sources.begin(); iter != sources.end();){
        //delete iter->second;
        INFO(ss << iter->first << " cleared (" << iter->second << ")");
        alDeleteSources(1, &(iter->second));
        sources.erase(iter);
        INFO(ss << "Sources total: " << sources.size());
        iter = std::next(iter);
    }
    */
    //sources.clear();

	//INFO(ss << "Clearing Buffers: " << buffers.size());
	/*
    for(std::map<std::string, ALuint>::iterator iter = buffers.begin(); iter != buffers.end();){
        //delete iter->second;
        INFO(ss << iter->first << " cleared (" << iter->second << ")");
        alDeleteBuffers(1, &(iter->second));
        buffers.erase(iter);
        INFO(ss << "Buffers total: " << buffers.size());
        iter = std::next(iter);
    }
    */
    //buffers.clear();

    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

