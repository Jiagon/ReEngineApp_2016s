#pragma once

class CameraManager {
private:
	CameraManager() {
		//initialize members here
	};
	CameraManager(CameraManager const& other) {
		//Copy Members here

		instance = other.GetInstance();
	};
	CameraManager& operator=(CameraManager const& other) {
		//Copy Members here

		instance = other.GetInstance();
	};
public:
	static CameraManager* instance;
	
	static CameraManager* GetInstance() {
		if (instance == nullptr) {
			instance = new CameraManager();
		}
		return instance;
	}

	static void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
};

CameraManager* CameraManager::instance = nullptr;