#ifndef LOOP_H
#define LOOP_H

#define until(cond) while(!(cond))
#define forever while(true)
// repeat         : for loop from [0, _nbTime[
#define repeat(_varName, _nbTime) for(int _varName = 0; _varName < (int)(_nbTime); _varName++)

#endif