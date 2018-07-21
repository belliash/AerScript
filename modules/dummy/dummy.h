#ifndef __DUMMY_H__
#define __DUMMY_H__

#include "ph7.h"
#include "ph7int.h"

#define MODULE_DESC "Dummy Module"
#define MODULE_VER 1.0

/* Forward reference & declaration */
PH7_PRIVATE sxi32 initializeModule(ph7_vm *pVm, ph7_real *ver, SyString *desc);

/* Constants provided by DUMMY module */
static void PSHARP_DUMMY_CONSTANT_Const(ph7_value *pVal, void *pUserData);

/* Functions provided by DUMMY module */
int psharp_dummy_function(ph7_context *pCtx, int nArg, ph7_value **apArg);

static const ph7_builtin_constant dummyConstList[] = {
	{"DUMMY_CONSTANT",           PSHARP_DUMMY_CONSTANT_Const},
};

static const ph7_builtin_func dummyFuncList[] = {
	{"dummy_function",    psharp_dummy_function },
};

#endif
