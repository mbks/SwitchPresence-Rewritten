#pragma once
#include <switch.h>

#define PACKETMAGIC 0xFFAADD23
#define PORT 0xCAFE

struct PACKED titlepacket
{
    u64 magic;
    u64 programId;
    char name[612];
    char player[33];
};

int sendData(u64 programId, const char *name, const char *player);
Result setupSocketServer();
void closeSocketServer();
