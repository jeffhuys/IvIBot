#ifndef PORT_H
#define PORT_H
#include "includes.h"

extern void initPorts(void);

extern void setPortBIO(BYTE);
extern void setPortECIO(BYTE);
extern void setPortDIO(BYTE);

extern void setPortBData(BYTE);
extern void setPortECData(BYTE);
extern void setPortDData(BYTE);

extern BYTE getPortB(void);
extern BYTE getPortEC(void);
extern BYTE getPortD(void);
extern BYTE getPortEC_TRIS(void);

#endif
