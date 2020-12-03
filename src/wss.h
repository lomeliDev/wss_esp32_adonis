
#ifndef WSS_H
#define WSS_H

String converter(uint8_t *str);

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);

void setupWss(void);

void WSTxt(String str);

void WSLoop(void);

void attWSS(void);


#endif