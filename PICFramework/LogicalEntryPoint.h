

#pragma optimize( "", off ) // *** Disable all optimizations - we need code "as is"!
#pragma code_seg(".extcd")  // *** Lets put all functions in a separated code segment

int  LogicEntryPoint(PMY_DATA resolvedFunctionPointers, PARGUMENTS arguments);


#pragma code_seg()
#pragma optimize( "", on )