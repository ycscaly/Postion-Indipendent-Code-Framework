
#include "definitions.h"

#pragma optimize( "", off ) // *** Disable all optimizations - we need code "as is"!
#pragma code_seg(".extcd")  // *** Lets put all functions in a separated code segment

int  LogicEntryPoint(PMY_DATA resolvedFunctionPointers, PARGUMENTS arguments){

	//Introduce logic here, using resolvedFunctionPointers's functions, and not any other winapi calls or globals or strings.

	//E.g.,
	resolvedFunctionPointers->MessageBoxA(NULL, arguments->MessageBoxText, arguments->MessageBoxTitle, MB_OK);
	resolvedFunctionPointers->ExitProcess(0);
	return 0;

}

#pragma code_seg()
#pragma optimize( "", on )