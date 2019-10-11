//Orshak Ivan, 2017

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

/* Debug memory allocation support */
#ifdef _DEBUG
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h>
# define SetDbgMemHooks() \
_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
_CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
# define SetDbgMemHooks() ((VOID)0)
#endif /* _DEBUG */

int crpt_txt(char* FilePath, int Key);

#endif /* ENCRYPTION_H */
