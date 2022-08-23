#include <errno.h>

#define MSG_IF_ERROR(msg)          if( errno>0 ) { perror((msg)); }
#define RETURN_IF_ERROR(msg, code) if( errno>0 ) { perror((msg)); return (code); }
#define RETURN_IF_ERROR2(msg)      if( errno>0 ) { perror((msg)); return; }
#define EXIT_IF_ERROR(msg)         if( errno>0 ) { perror((msg)); exit(errno); }

#define ERROR_IF_NULL(var, msg, code) if(var==NULL) { printf("%s: null pointer\n", (msg)); (code); }