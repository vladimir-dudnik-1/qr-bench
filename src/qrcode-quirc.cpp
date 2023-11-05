/*
 * QR code decode with quirc
*/

#include "qrcode-quirc.h"

int qrcode_detect_and_decode_quirc(cv::Mat& src, std::vector<cv::Rect>& bbox, qrcode_params_quirc& params)
{
    int r;
    struct quirc* qr = NULL;
    cv::TickMeter tm;

    qr = quirc_new();
    if(NULL == qr)
    {
        fprintf(stdout, "QUIRC initialization failed.\n");
        return -1;
    }

    r = quirc_resize(qr, src.cols, src.rows);
    if(0 > r)
    {
        fprintf(stdout, "quirc_resize() failed\n");
        return -1;
    }

    int num_codes;

    tm.start();
    for (int i = 0; i < params.p.nloops; i++)
    {
        uint8_t* img = quirc_begin(qr, &src.cols, &src.rows);
        if(NULL == img)
        {
            fprintf(stdout, "quirc_begin() failed\n");
            return -1;
        }

        cv::Rect rect;
        cv::Mat gray(src.size(), CV_8UC1, img);
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

        quirc_end(qr);

        num_codes = quirc_count(qr);
        for(int n = 0; n < num_codes; n++)
        {
            struct quirc_code code;
            struct quirc_data data;
            quirc_decode_error_t err;

            quirc_extract(qr, n, &code);

            err = quirc_decode(&code, &data);
            if(err)
            {
                fprintf(stdout, "quirc_decode() failed: %s\n", quirc_strerror(err));
                break;
            }
            else
                params.payloads.push_back(data);
        }
    }
    tm.stop();

    params.p.msec = tm.getTimeMilli() / params.p.nloops;

    fprintf(stdout, "qrcode_detect_and_decode_quirc found %d codes at %3.2f msec\n", num_codes, params.p.msec);
    for(int i = 0; i < num_codes; i++)
        fprintf(stdout, "  result[%d/%d]: %s\n", i, num_codes, (const char*)params.payloads[0].payload);

    quirc_destroy(qr);

    return 0;
}
