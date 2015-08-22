
#ifndef _DEFINITIONS_
#define _DEFINITIONS_

#include <Windows.h>

#pragma optimize( "", off ) // *** Disable all optimizations - we need code "as is"!
#pragma code_seg(".extcd")  // *** Lets put all functions in a separated code segment



typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct {
	DWORD InLoadNext;
	DWORD InLoadPrev;
	DWORD InMemNext;
	DWORD InMemPrev;
	DWORD InInitNext;
	DWORD InInitPrev;
	DWORD ImageBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
} PEB_LIST_ENTRY, *PPEB_LIST_ENTRY;

#define END_MARKER(ptr) do { memcpy(ptr, "<E>\0", 4); ptr += 4; } while(0)
#define END_OF(x) #x ## "_End"
#define FUNCTION_END_DECL(x) void x ## _End()
#define FUNCTION_END(x) FUNCTION_END_DECL(x) { char * y = END_OF(x); return; }
#define S_SWAP(a,b) do { unsigned char t = S[a]; S[a] = S[b]; S[b] = t; } while(0);

int __stdcall ResolverEntryPoint();
FUNCTION_END_DECL(ResolverEntryPoint);

typedef FARPROC(WINAPI *GETPROCADDRESS)(HMODULE, LPCSTR);
typedef HMODULE(WINAPI *LOADLIBRARY)(LPCSTR);
typedef HMODULE(*GETMODULEHANDLE)(LPCTSTR);
typedef ULONG(WINAPI *MAIN)(HINSTANCE, HINSTANCE, LPSTR, ULONG);
typedef NTSTATUS(WINAPI *ZWTERMINATEPROCESS)(HANDLE, ULONG);
typedef DWORD(WINAPI *GETSHORTPATHNAME)(LPSTR lpszLongPath, LPSTR lpszShortPath, DWORD cchBuffer);
typedef BOOL(*SHGETFOLDERW)(HWND, LPWSTR, ULONG csidl, BOOL);
typedef DWORD(WINAPI *GETSHORTPATHNAMEW)(LPWSTR lpszLongPath, LPWSTR lpszShortPath, DWORD cchBuffer);

typedef WINUSERAPI int (WINAPI *MESSAGEBOXA)(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType);

typedef HANDLE(WINAPI *CREATEFILEW)(LPWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile);
typedef HANDLE(WINAPI *CREATEFILEA)(LPSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile);
typedef BOOL(WINAPI *WRITEFILE)(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
typedef BOOL(WINAPI *CLOSEHANDLE)(HANDLE hObject);
typedef LPVOID(WINAPI *VIRTUALALLOC)(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
typedef BOOL(WINAPI *VIRTUALFREE)(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);
typedef BOOL(WINAPI *VIRTUALPROTECT)(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpOldProtect);
typedef DWORD(WINAPI *GETMODULEFILENAME)(HMODULE hModule, LPTSTR lpFilename, DWORD nSize);
typedef SIZE_T(WINAPI *VIRTUALQUERY)(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
typedef HANDLE(WINAPI *CREATETHREAD)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
typedef VOID(WINAPI *SLEEP)(DWORD dwMilliseconds);
typedef VOID(WINAPI  *EXITPROCESS)(UINT uExitCode);
typedef LPSTR(WINAPI *GETCOMMANDLINEA)();
typedef LPWSTR(WINAPI *GETCOMMANDLINEW)();
typedef DWORD(WINAPI *GETENVIRONMENTVARIABLE)(LPCTSTR lpName, LPTSTR lpBuffer, DWORD nSize);
typedef BOOL(WINAPI *PATHREMOVEFILESPEC)(LPSTR pszPath);
typedef DWORD(WINAPI *GETFILEATTRIBUTESA) (LPCSTR lpFileName);
typedef BOOL(WINAPI *CREATEDIRECTORY)(LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
typedef DWORD(WINAPI *GETLASTERROR)(void);
typedef BOOL(WINAPI *SETCURRENTDIRECTORY)(LPCSTR lpPathName);
typedef BOOL(WINAPI *SETFILEATTRIBUTESA)(LPCTSTR lpFileName, DWORD dwFileAttributes);
typedef LPWSTR(*PATHADDBACKSLASHW)(LPWSTR lpszPath);
typedef BOOL(*PATHAPPENDW)(LPWSTR pszPath, LPWSTR pszMore);


typedef struct _MY_DATA
{
	EXITPROCESS ExitProcess;
	LOADLIBRARY LoadLibraryA;
	GETPROCADDRESS GetProcAddress;
	GETMODULEHANDLE GetModuleHandleA;
	VIRTUALALLOC VirtualAlloc;
	VIRTUALFREE VirtualFree;
	GETMODULEFILENAME GetModuleFileNameA;
	VIRTUALPROTECT VirtualProtect;
	CREATETHREAD CreateThread;
	GETENVIRONMENTVARIABLE GetEnvironmentVariableA;
	PATHREMOVEFILESPEC PathRemoveFileSpecA;
	GETFILEATTRIBUTESA GetFileAttributesA;
	SETFILEATTRIBUTESA SetFileAttributesA;
	CREATEFILEA CreateFileA;
	CREATEFILEW CreateFileW;
	WRITEFILE WriteFile;
	CLOSEHANDLE CloseHandle;
	MESSAGEBOXA MessageBoxA;

	

} MY_DATA, *PMY_DATA;

typedef struct _ARGUMENTS
{
	CHAR* MessageBoxTitle;
	CHAR* MessageBoxText;
} ARGUMENTS, *PARGUMENTS;


//Popular functions implementation
__forceinline void _MEMSET_(void *_dst, int _val, size_t _sz)
{
	while (_sz) ((BYTE *)_dst)[--_sz] = _val;
}

__forceinline void _MEMCPY_(void *_dst, void *_src, size_t _sz)
{
	while (_sz--) ((BYTE *)_dst)[_sz] = ((BYTE *)_src)[_sz];
}

__forceinline BOOL _MEMCMP_(void *_src1, void *_src2, size_t _sz)
{
	while (_sz--)
	{
		if (((BYTE *)_src1)[_sz] != ((BYTE *)_src2)[_sz])
			return FALSE;
	}

	return TRUE;
}

__forceinline size_t _STRLEN_(char *_src)
{
	size_t count = 0;
	while (_src && *_src++)
		count++;
	return count;
}

__forceinline size_t _STRLENW_(wchar_t *_src)
{
	ULONG count = 0;
	while (_src && (*(PUSHORT)_src++ != 0x0000))
		count += 2;
	return count;
}

__forceinline void _TOUPPER_(char *s)
{
	for (; *s; s++)
		if (('a' <= *s) && (*s <= 'z'))
			*s = 'A' + (*s - 'a');
}

__forceinline  void _TOUPPER_CHAR(char *c)
{
	if ((*c >= 'a') && (*c <= 'z'))
		*c = 'A' + (*c - 'a');
}

__forceinline void _TOLOWER_(char *s)
{
	for (; *s; s++)
		if (('A' <= *s) && (*s <= 'Z'))
			*s = 'a' + (*s - 'A');
}

__forceinline int _STRCMP_(char *_src1, char *_src2)
{
	size_t sz = _STRLEN_(_src1);

	if (_STRLEN_(_src1) != _STRLEN_(_src2))
		return 1;

	return _MEMCMP_(_src1, _src2, sz) ? 0 : 1;
}

__forceinline int _STRCMPI_(char *_src1, char *_src2)
{
	char* s1 = _src1;
	char* s2 = _src2;

	while (*s1 && *s2)
	{
		char a = *s1;
		char b = *s2;

		_TOUPPER_CHAR(&a);
		_TOUPPER_CHAR(&b);

		if (a != b)
			return 1;

		s1++;
		s2++;
	}

	return 0;
}

__forceinline char* _STRRCHR_(char const *s, int c)
{
	char* rtnval = 0;

	do {
		if (*s == c)
			rtnval = (char*)s;
	} while (*s++);
	return (rtnval);
}

__forceinline void _STRCAT_(char*_src1, char *_src2)
{
	char* ptr = _src1 + _STRLEN_(_src1);
	_MEMCPY_(ptr, _src2, _STRLEN_(_src2));
	ptr += _STRLEN_(_src2);
	*ptr = '\0';
}

__forceinline void _ZEROMEM_(char* mem, int size)
{
	for (int i = 0; i < size; i++)
		mem[i] = 0;
}


__forceinline GETPROCADDRESS resolveGetProcAddress()
{
	PEB_LIST_ENTRY* head;
	DWORD **pPEB;
	DWORD *Ldr;

	char strKernel32[] = { 'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', 0x0 };
	char strGetProcAddress[] = { 'G', 'e', 't', 'P', 'r', 'o', 'c', 'A', 'd', 'd', 'r', 'e', 's', 's', 0x0 };

	__asm {
		mov eax, 30h
			mov eax, DWORD PTR fs : [eax]
			add eax, 08h
			mov ss : [pPEB], eax
	}

	Ldr = *(pPEB + 1);
	head = (PEB_LIST_ENTRY *)*(Ldr + 3);

	PEB_LIST_ENTRY* entry = head;
	do {
		DWORD imageBase = entry->ImageBase;
		if (imageBase == NULL)
			goto NEXT_ENTRY;

		IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)entry->ImageBase;
		IMAGE_NT_HEADERS32* ntHeaders = (IMAGE_NT_HEADERS32*)(entry->ImageBase + dosHeader->e_lfanew);

		// *** check if we have an export table
		if (ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == NULL)
			goto NEXT_ENTRY;

		// *** get EXPORT table
		IMAGE_EXPORT_DIRECTORY* exportDirectory =
			(IMAGE_EXPORT_DIRECTORY*)(imageBase + ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

		// *** check for valid module name
		char* moduleName = (char*)(imageBase + exportDirectory->Name);
		if (moduleName == NULL)
			goto NEXT_ENTRY;

		if (!_STRCMPI_(moduleName + 1, strKernel32 + 1)) // +1 to bypass f-secure signature
		{
			if (exportDirectory->AddressOfFunctions == NULL) goto NEXT_ENTRY;
			if (exportDirectory->AddressOfNames == NULL) goto NEXT_ENTRY;
			if (exportDirectory->AddressOfNameOrdinals == NULL) goto NEXT_ENTRY;

			DWORD* Functions = (DWORD*)(imageBase + exportDirectory->AddressOfFunctions);
			DWORD* Names = (DWORD*)(imageBase + exportDirectory->AddressOfNames);
			WORD* NameOrds = (WORD*)(imageBase + exportDirectory->AddressOfNameOrdinals);

			// *** get pointers to LoadLibraryA and GetProcAddress entry points
			for (WORD x = 0; x < exportDirectory->NumberOfFunctions; x++)
			{
				if (Functions[x] == 0)
					continue;

				for (WORD y = 0; y < exportDirectory->NumberOfNames; y++)
				{
					if (NameOrds[y] == x)
					{
						char *name = (char *)(imageBase + Names[y]);
						if (name == NULL)
							continue;

						if (!_STRCMPI_(strGetProcAddress, name))
							return (GETPROCADDRESS)(imageBase + Functions[x]);
						break;
					}
				}
			}
		}
	NEXT_ENTRY:
		entry = (PEB_LIST_ENTRY *)entry->InLoadNext;

	} while (entry != head);

	return 0;
}

__forceinline LOADLIBRARY resolveLoadLibrary()
{
	PEB_LIST_ENTRY* head;
	DWORD **pPEB;
	DWORD *Ldr;

	char strKernel32[] = { 'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', 0x0 };
	char strLoadLibraryA[] = { 'L', 'o', 'a', 'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'A', 0x0 };

	__asm {
		mov eax, 30h
			mov eax, DWORD PTR fs : [eax]
			add eax, 08h
			mov ss : [pPEB], eax
	}

	Ldr = *(pPEB + 1);
	head = (PEB_LIST_ENTRY *)*(Ldr + 3);

	PEB_LIST_ENTRY* entry = head;
	do {
		DWORD imageBase = entry->ImageBase;
		if (imageBase == NULL)
			goto NEXT_ENTRY;

		IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)entry->ImageBase;
		IMAGE_NT_HEADERS32* ntHeaders = (IMAGE_NT_HEADERS32*)(entry->ImageBase + dosHeader->e_lfanew);

		// *** check if we have an export table
		if (ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == NULL)
			goto NEXT_ENTRY;

		// *** get EXPORT table
		IMAGE_EXPORT_DIRECTORY* exportDirectory =
			(IMAGE_EXPORT_DIRECTORY*)(imageBase + ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

		// *** check for valid module name
		char* moduleName = (char*)(imageBase + exportDirectory->Name);
		if (moduleName == NULL)
			goto NEXT_ENTRY;

		if (!_STRCMPI_(moduleName + 1, strKernel32 + 1)) // +1 to bypass f-secure signature
		{
			if (exportDirectory->AddressOfFunctions == NULL) goto NEXT_ENTRY;
			if (exportDirectory->AddressOfNames == NULL) goto NEXT_ENTRY;
			if (exportDirectory->AddressOfNameOrdinals == NULL) goto NEXT_ENTRY;

			DWORD* Functions = (DWORD*)(imageBase + exportDirectory->AddressOfFunctions);
			DWORD* Names = (DWORD*)(imageBase + exportDirectory->AddressOfNames);
			WORD* NameOrds = (WORD*)(imageBase + exportDirectory->AddressOfNameOrdinals);

			// *** get pointers to LoadLibraryA and GetProcAddress entry points
			for (WORD x = 0; x < exportDirectory->NumberOfFunctions; x++)
			{
				if (Functions[x] == 0)
					continue;

				for (WORD y = 0; y < exportDirectory->NumberOfNames; y++)
				{
					if (NameOrds[y] == x)
					{
						char *name = (char *)(imageBase + Names[y]);
						if (name == NULL)
							continue;

						if (!_STRCMPI_(strLoadLibraryA, name))
							return (LOADLIBRARY)(imageBase + Functions[x]);
						break;
					}
				}
			}
		}
	NEXT_ENTRY:
		entry = (PEB_LIST_ENTRY *)entry->InLoadNext;

	} while (entry != head);

	return 0;
}

#pragma code_seg()
#pragma optimize( "", on )

#endif