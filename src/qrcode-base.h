/*
 * QR code base
*/
#ifndef __QRCODE_BASE_H__
#define __QRCODE_BASE_H__

typedef struct
{
    int   nloops;
    float msec;
} qrcode_params;

typedef struct
{
    std::string payload;
} qrcode_payload;

#endif
