/*
 * QR code decode with quirc
*/
#ifndef __QRCODE_QUIRC_H__
#define __QRCODE_QUIRC_H__

#include <opencv2/opencv.hpp>
#include <quirc.h>

#include "qrcode-base.h"

typedef struct
{
    qrcode_params p;
    std::vector<quirc_data> payloads;
} qrcode_params_quirc;


int qrcode_detect_and_decode_quirc(cv::Mat& src, std::vector<cv::Rect>& bbox, qrcode_params_quirc& params);

#endif // __QRCODE_QUIRC_H__
