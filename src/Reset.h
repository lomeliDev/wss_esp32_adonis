#ifndef RESET_H
#define RESET_H

#define RSTUsiuario     5

#define TimerBotonRST   TIMTimer[8]
#define TiempoBoton     5000

void setupReset(void);

void Reset(void);

void loopReset(void);

#endif