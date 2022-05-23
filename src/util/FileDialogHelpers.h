#pragma once

#include <Windows.h>
#include <MapBuilderCore.h>

/*
Opens a Win32 'Save File' dialog.
Overloaded to take in wchar filename.
*/
inline void getSaveFilepathWIN32(wchar_t* filename, LPCWSTR filter = L"Any File (*.*)\0*.*\0", LPCWSTR defExt = nullptr)
{
	wchar_t loadedFilepath[MBC_MAX_PATH] = {0};

	OPENFILENAME ofn;			// OpenFileName struct
	ZeroMemory(&ofn, sizeof(ofn));						// Zeroes out memory contained in struct
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetActiveWindow();
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = loadedFilepath;
	ofn.lpstrDefExt = defExt;
	ofn.nMaxFile = MBC_MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;

	if (GetSaveFileName(&ofn)) {
		wcscpy_s(filename, MBC_MAX_PATH, loadedFilepath);
	}
}


/*
Opens a Win32 'Save File' dialog.
Overloaded to take in char filename.
*/
inline void getSaveFilepathWIN32(char* filename, LPCWSTR filter = L"Any File (*.*)\0*.*\0", LPCWSTR defExt = nullptr)
{
	wchar_t wideFilepath[MBC_MAX_PATH] = {0};
	getSaveFilepathWIN32(wideFilepath, filter, defExt);
	if (wideFilepath[0] != L'\0')  // Only update if new filepath was chosen
		sprintf_s(filename, MBC_MAX_PATH, "%ws", wideFilepath); // Copy wchar to char
}


// Overloaded to take in wchar filename
inline void getOpenFilepathWIN32(wchar_t* filename, LPCWSTR filter = L"Any File (*.*)\0*.*\0")
{
	wchar_t loadedFilepath[MBC_MAX_PATH] = {0};

	OPENFILENAME ofn;			// OpenFileName struct
	ZeroMemory(&ofn, sizeof(ofn));						// Zeroes out memory contained in struct
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetActiveWindow();
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = loadedFilepath;
	ofn.nMaxFile = MBC_MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn)) {
		wcscpy_s(filename, MBC_MAX_PATH, loadedFilepath);
	}
}
