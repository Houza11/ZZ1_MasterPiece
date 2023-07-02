#ifndef DEBUG_H
#define DEBUG_H

#define current_file __FILE__
#define current_line __LINE__
#define current_func __func__ 
#define current_time __TIME__ 

#define debug { printf("%s:%i at function %s()\n", current_file, current_line, current_func); }
#define printf_size(type) { printf("%s = %i bytes\n", TO_STRING(type), (int)(sizeof(type))); }

#define crash(msg) { printf("Crash : %s at ", (msg)); debug; exit(EXIT_FAILURE); }
#define check(condTrue) if(!(condTrue)) { crash(TO_STRING(condTrue)); }

#endif