#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "nanoKONTROL2.h"
#include "board_controller.h"
#include "range.h"



#include <mmdeviceapi.h>
#include <endpointvolume.h>
// https://www.codeproject.com/tips/233484/change-master-volume-in-visual-cplusplus
HRESULT ChangeVolume(const double& nVolume)
{
	HRESULT hr = EXIT_SUCCESS;

	CoInitialize(nullptr);
	IMMDeviceEnumerator *deviceEnumerator = nullptr;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), reinterpret_cast<LPVOID *>(&deviceEnumerator));
	IMMDevice *defaultDevice = nullptr;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = nullptr;

	IAudioEndpointVolume *endpointVolume = nullptr;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, nullptr, reinterpret_cast<LPVOID *>(&endpointVolume));
	defaultDevice->Release();
	defaultDevice = nullptr;

	// -------------------------
	float currentVolume = 0;
	endpointVolume->GetMasterVolumeLevel(&currentVolume);
	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
	hr = endpointVolume->SetMasterVolumeLevelScalar(static_cast<float>(nVolume), NULL);
	endpointVolume->Release();

	CoUninitialize();
	return hr;
}


void master_slider_callback(void* data, void* in, const bool& new_state, const double& deltatime)
{
	auto slider = static_cast<range*>(in);
	std::cout << slider->range_value() << std::endl;
	ChangeVolume(slider->range_value());
}

int main()
{
	nanoKONTROL2 nano_kontrol2 { };
	nano_kontrol2.groups[0]->slider->callback = &master_slider_callback;

	board_controller controller(reinterpret_cast<board*>(&nano_kontrol2), false);

	// Setup
	auto result = controller.setup();
	if (result != EXIT_SUCCESS)
		goto exit_fail;

	result = controller.open();
	if (result != EXIT_SUCCESS)
		goto exit_fail;

	for (;;)
	{
		std::cout << "Press Esc to stop.." << std::endl;
		if (_getch() == VK_ESCAPE)
			return EXIT_SUCCESS;
	}

exit_fail:
	std::cout << "Press a key to exit.." << std::endl;
	std::cin.get();
	exit(EXIT_FAILURE);
}
