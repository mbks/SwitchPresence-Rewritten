#pragma once
#include <switch.h>

#define PACKETMAGIC 0xFFAADD23
#define PORT 0xCAFE

struct PACKED titlepacket
{
    u64 magic;
    u64 programId;
    u64 player;
    char name[612];
};

int sendData(u64 programId, const char *name, u64 player);
Result setupSocketServer();
void closeSocketServer();
