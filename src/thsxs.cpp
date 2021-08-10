#include <thcrap.h>

typedef HANDLE TH_STDCALL CreateMutexA_type(LPSECURITY_ATTRIBUTES, BOOL, LPCSTR);
DETOUR_CHAIN_DEF(CreateMutexA);

HANDLE TH_STDCALL sxs_CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName) {
	return chain_CreateMutexA(lpMutexAttributes, bInitialOwner, NULL);
}

int TH_STDCALL thcrap_plugin_init() {
	detour_chain("kernel32.dll", 1,
		"CreateMutexA", sxs_CreateMutexA, &chain_CreateMutexA,
		NULL
	);
	return 0;
}
