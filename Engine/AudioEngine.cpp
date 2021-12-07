#include "AudioEngine.h"

namespace Engine
{
	Implementation::Implementation() {
		mpStudioSystem = NULL;
		AudioEngine::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
		AudioEngine::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

		mpSystem = NULL;
		AudioEngine::ErrorCheck(mpStudioSystem->getLowLevelSystem(&mpSystem));
	}

	Implementation::~Implementation() {
		AudioEngine::ErrorCheck(mpStudioSystem->unloadAll());
		AudioEngine::ErrorCheck(mpStudioSystem->release());
	}

	void Implementation::Update() {
		std::vector<ChannelMap::iterator> pStoppedChannels;
		for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
		{
			bool bIsPlaying = false;
			it->second->isPlaying(&bIsPlaying);
			if (!bIsPlaying)
			{
				pStoppedChannels.push_back(it);
			}
		}
		for (auto& it : pStoppedChannels)
		{
			mChannels.erase(it);
		}
		AudioEngine::ErrorCheck(mpStudioSystem->update());
	}

	Implementation* sgpImplementation = nullptr;

	void AudioEngine::Init() {
		sgpImplementation = new Implementation;
	}

	void AudioEngine::Update() {
		sgpImplementation->Update();
	}

	SoundStatus AudioEngine::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
	{
		auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt != sgpImplementation->mSounds.end())
			return SoundStatus::LOADED_BEFORE;
		printf("Loading sound: %s ... ", strSoundName.c_str());
		FMOD_MODE eMode = FMOD_DEFAULT;
		eMode |= b3d ? FMOD_3D : FMOD_2D;
		eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
		FMOD::Sound* pSound = nullptr;
		AudioEngine::ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
		if (pSound) {
			sgpImplementation->mSounds[strSoundName] = pSound;
			printf("   Loaded.\n");
			return SoundStatus::LOADED_NOW;
		}
	}

	void AudioEngine::UnLoadSound(const std::string& strSoundName)
	{
		auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end())
			return;
		printf("Unloading sound: %s ... ", strSoundName.c_str());
		AudioEngine::ErrorCheck(tFoundIt->second->release());
		sgpImplementation->mSounds.erase(tFoundIt);
		printf("   Unoaded.\n");
	}

	int AudioEngine::playSound(const std::string& strSoundName, const Vector3& vPosition, float fVolumedB)
	{
		int nChannelId = sgpImplementation->mnNextChannelId++;
		auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end())
		{
			LoadSound(strSoundName);
			tFoundIt = sgpImplementation->mSounds.find(strSoundName);
			if (tFoundIt == sgpImplementation->mSounds.end())
			{
				return nChannelId;
			}
		}
		FMOD::Channel* pChannel = nullptr;
		AudioEngine::ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
		if (pChannel)
		{
			FMOD_MODE currMode;
			tFoundIt->second->getMode(&currMode);
			if (currMode & FMOD_3D) {
				FMOD_VECTOR position = VectorToFmod(vPosition);
				AudioEngine::ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
			}
			AudioEngine::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
			AudioEngine::ErrorCheck(pChannel->setPaused(false));
			sgpImplementation->mChannels[nChannelId] = pChannel;
		}
		return nChannelId;
	}

	void AudioEngine::SetChannel3dPosition(int nChannelId, const Vector3& vPosition)
	{
		auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
		if (tFoundIt == sgpImplementation->mChannels.end())
			return;

		FMOD_VECTOR position = VectorToFmod(vPosition);
		AudioEngine::ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
	}

	void AudioEngine::SetChannelVolume(int nChannelId, float fVolumedB)
	{
		auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
		if (tFoundIt == sgpImplementation->mChannels.end())
			return;

		AudioEngine::ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
	}

	void AudioEngine::StopChannel(int nChannelId)
	{
		auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
		if (tFoundIt == sgpImplementation->mChannels.end())
			return;

		AudioEngine::ErrorCheck(tFoundIt->second->setPaused(true));
	}

	void AudioEngine::StartChannel(int nChannelId)
	{
		auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
		if (tFoundIt == sgpImplementation->mChannels.end())
			return;

		AudioEngine::ErrorCheck(tFoundIt->second->setPaused(false));
	}

	void AudioEngine::ResetChannelPosition(int channelId)
	{
		auto it = sgpImplementation->mChannels.find(channelId);
		if (it == sgpImplementation->mChannels.end())
			return;

		AudioEngine::ErrorCheck(it->second->setPosition(0, FMOD_TIMEUNIT_MS));
	}

	void AudioEngine::StopAllChannels()
	{
		for (const auto& channel : sgpImplementation->mChannels)
		{
			channel.second->setPaused(true);
		}
	}

	void AudioEngine::StartAllChannels()
	{
		for (const auto& channel : sgpImplementation->mChannels)
		{
			channel.second->setPaused(false);
		}
	}

	void AudioEngine::ResetPositionAllChannels()
	{
		for (const auto& channel : sgpImplementation->mChannels)
		{
			channel.second->setPosition(0, FMOD_TIMEUNIT_MS);
		}
	}

	bool AudioEngine::IsPlaying(int channelId) const
	{
		auto it = sgpImplementation->mChannels.find(channelId);
		if (it == sgpImplementation->mChannels.end())
			return false;

		bool paused;
		AudioEngine::ErrorCheck(it->second->getPaused(&paused));
		return !paused;
	}

	void AudioEngine::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags) {
		auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
		if (tFoundIt != sgpImplementation->mBanks.end())
			return;
		FMOD::Studio::Bank* pBank;
		AudioEngine::ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
		if (pBank) {
			sgpImplementation->mBanks[strBankName] = pBank;
		}
	}

	void AudioEngine::LoadEvent(const std::string& strEventName) {
		auto tFoundit = sgpImplementation->mEvents.find(strEventName);
		if (tFoundit != sgpImplementation->mEvents.end())
			return;
		FMOD::Studio::EventDescription* pEventDescription = NULL;
		AudioEngine::ErrorCheck(sgpImplementation->mpStudioSystem->getEvent(strEventName.c_str(), &pEventDescription));
		if (pEventDescription) {
			FMOD::Studio::EventInstance* pEventInstance = NULL;
			AudioEngine::ErrorCheck(pEventDescription->createInstance(&pEventInstance));
			if (pEventInstance) {
				sgpImplementation->mEvents[strEventName] = pEventInstance;
			}
		}
	}

	void AudioEngine::PlayEvent(const std::string& strEventName) {
		auto tFoundit = sgpImplementation->mEvents.find(strEventName);
		if (tFoundit == sgpImplementation->mEvents.end()) {
			LoadEvent(strEventName);
			tFoundit = sgpImplementation->mEvents.find(strEventName);
			if (tFoundit == sgpImplementation->mEvents.end())
				return;
		}
		tFoundit->second->start();
	}

	void AudioEngine::StopEvent(const std::string& strEventName, bool bImmediate) {
		auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
		if (tFoundIt == sgpImplementation->mEvents.end())
			return;
		FMOD_STUDIO_STOP_MODE eMode;
		eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
		AudioEngine::ErrorCheck(tFoundIt->second->stop(eMode));
	}

	bool AudioEngine::IsEventPlaying(const std::string& strEventName) const {
		auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
		if (tFoundIt == sgpImplementation->mEvents.end())
			return false;

		FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
		if (tFoundIt->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) {
			return true;
		}
		return false;
	}

	void AudioEngine::GetEventParameter(const std::string& strEventName, const std::string& strParameterName, float* parameter) {
		auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
		if (tFoundIt == sgpImplementation->mEvents.end())
			return;
		FMOD::Studio::ParameterInstance* pParameter = NULL;
		AudioEngine::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
		AudioEngine::ErrorCheck(pParameter->getValue(parameter));
	}

	void AudioEngine::SetEventParameter(const std::string& strEventName, const std::string& strParameterName, float fValue) {
		auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
		if (tFoundIt == sgpImplementation->mEvents.end())
			return;
		FMOD::Studio::ParameterInstance* pParameter = NULL;
		AudioEngine::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
		AudioEngine::ErrorCheck(pParameter->setValue(fValue));
	}

	FMOD_VECTOR AudioEngine::VectorToFmod(const Vector3& vPosition) {
		FMOD_VECTOR fVec;
		fVec.x = vPosition.x;
		fVec.y = vPosition.y;
		fVec.z = vPosition.z;
		return fVec;
	}

	int AudioEngine::ErrorCheck(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cout << "FMOD ERROR " << result << std::endl;
			return 1;
		}
		// cout << "FMOD all good" << endl;
		return 0;
	}

	float  AudioEngine::dbToVolume(float dB)
	{
		return powf(10.0f, 0.05f * dB);
	}

	float  AudioEngine::VolumeTodB(float volume)
	{
		return 20.0f * log10f(volume);
	}

	void AudioEngine::Shutdown() {
		delete sgpImplementation;
	}
}