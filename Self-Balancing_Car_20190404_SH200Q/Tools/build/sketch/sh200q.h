#ifndef _Sh200Q_H_
#define _Sh200Q_H_

extern int16_t gyro[3];
extern int16_t acc[3];
extern uint8_t rawADC[12];

void sh200q_init(void);
void sh200q_getADC(void);

#endif
