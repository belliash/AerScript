#ifndef __DUMMY_H__
#define __DUMMY_H__

#include "ph7.h"
#include "ph7int.h"

/* Forward reference & declaration */
PH7_PRIVATE sxi32 initializeModule(ph7_vm *pVm, ph7_real *ver, SyString *desc);

/* Functions provided by DUMMY module */
int psharp_dummy_function(ph7_context *pCtx, int nArg, ph7_value **apArg);

static const ph7_builtin_func dummyFuncList[] = {
	{"dummy_function",    psharp_dummy_function },
};

#endif