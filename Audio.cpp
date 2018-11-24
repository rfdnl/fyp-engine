#include "Audio.hpp"
#include <cstring>

bool Audio::InitAlut(){
	if (!alutInitWithoutContext(NULL, NULL)) {
		CheckAlError("alutInit");
		return false;
	}
	INFO("InitAlut - OK");
	return true;
}

bool Audio::EnumerateDevice(){
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if(enumeration == AL_FALSE){
		WARN("Enumeration not supported");
		return false;
	}
	INFO("Enumeration supported");
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
		ERROR("GetDefaultDeviceName - Fail");
	} else{
		INFO(ss << "Default device name: " << defaultDeviceName);
	}
}

bool Audio::OpenDevice(const ALCchar* deviceName){
	//device = alcOpenDevice(deviceName);
	if (!device){
		ERROR("Cannot open device!");
		return false;
    } else {
		device = alcOpenDevice("OpenAL Soft");
    }
	INFO(ss << "Device open: " << alcGetString(device, ALC_DEVICE_SPECIFIER));
	return true;
}

void Audio::InitListener(){
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);
}

bool Audio::CreateContext(){
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)){
		ERROR("Cannot create context");
		CheckAlError("CreateContext");
		return false;
	}
	INFO("Context created");
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

bool Audio::CheckAlError(std::string functionName, int line, std::string filename, std::string comment){
	ALenum error = alutGetError();
	if (error != AL_NO_ERROR){
		ERROR(ss << functionName << ", filename: " << filename << ", line: " << line << ", error: " << alutGetErrorString(error) << ", comment: " << comment);
		return false;
	}
	return true;
}

bool Audio::Initialize(){
	if (!InitAlut()) return false;
	if (!EnumerateDevice()) return false;
	RetrieveDeviceList(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	GetDefaultDeviceName();
	OpenDevice(defaultDeviceName);
	CheckAlError("Init");
	InitListener();
	return CreateContext();
}

// request new sound ID
void Audio::NewSource(std::string sourceKey){
	ALuint source;
	alGenSources((ALuint)1, &source);
	CheckAlError("NewSource (GenSaus)");
	alSourcef(source, AL_PITCH, 1);
	CheckAlError("NewSource (SetPtch)");
	alSourcef(source, AL_GAIN, 1);
	CheckAlError("NewSource (SetGain)");
	alSource3f(source, AL_POSITION, 0, 0, 0);
	CheckAlError("NewSource (SetPosi)");
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	CheckAlError("NewSource (SetVelo)");
	alSourcei(source, AL_LOOPING, AL_FALSE);
	CheckAlError("NewSource (SetLoop)");
	sources[sourceKey] = source;
}

bool Audio::NewBuffer(std::string audioKey, const char* filePath){
	ALuint buffer = alutCreateBufferFromFile(filePath);
	if (buffer == AL_NONE) {
		return CheckAlError("NewBuffer");
	}
	buffers[audioKey] = buffer;
	INFO(ss << "<" << filePath << "> loaded!");
	return true;
}

void Audio::Play(std::string sourceKey, std::string audioKey){
	alSourcei(sources[sourceKey], AL_BUFFER, buffers[audioKey]);
	CheckAlError("Play - Binding buffer");
	alSourcePlay(sources[sourceKey]);
	CheckAlError("Play - Playing source");
}

bool Audio::CanPlay(std::string sourceKey){
	ALint sourceState;
	alGetSourcei(sources[sourceKey], AL_SOURCE_STATE, &sourceState);
	CheckAlError("CanPlay - GetSource");
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

