#include <stdio.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

#include "gflags/gflags.h"

#include "qrcode-base.h"
#if(WITH_ZXING)
#include "ZXing/ReadBarcode.h"
#include "qrcode-zxing.h"
#endif
#if 0
#include "qrcode-efficientdet-lite.h"
#include "qrcode-opencv.h"
#include "qrcode-wechat.h"
#endif
#include "qrcode-quirc.h"

DEFINE_bool(h, false, "Print usage message");
DEFINE_int32(loop_count, 4, "loop counter");
DEFINE_int32(num_threads, 1, "number of execution threads");
DEFINE_int32(gpu_device, -1, "gpu device id (-1 to disable gpu)");
DEFINE_string(i, "input.jpg", "input image path");
DEFINE_string(m, "model.tflite", "path to model");


void usage(const char* argv0)
{
    gflags::ShowUsageWithFlags(argv0);
    return;
}


void parse(int argc, char** argv)
{
    gflags::ParseCommandLineFlags(&argc, &argv, false);

    if(FLAGS_h || 1 == argc)
    {
        usage(argv[0]);
    }
    return;
}


int main(int argc, char** argv)
{
    parse(argc, argv);

    fprintf(stderr, "num_threads = %d\n", FLAGS_num_threads);
    fprintf(stderr, "gpu_device = %d\n", FLAGS_gpu_device);

    const std::string model_path = FLAGS_m;
    const std::string input_file_name = FLAGS_i;

    fprintf(stdout, "model file: %s\n", model_path.c_str());
    fprintf(stdout, "num threads: %d\n", FLAGS_num_threads);

    if (input_file_name.empty())
    {
        CV_Assert(false && "input_file_name is empty. Please use absolute path for --input=");
    }

    cv::Mat image = cv::imread(input_file_name, cv::IMREAD_COLOR);
    fprintf(stdout, "file: %s, [%dx%dx%d]\n", input_file_name.c_str(), image.cols, image.rows, image.channels());

    std::vector<cv::Rect> bboxes;
#if 0
    qrcode_params_efficientdet_lite params1;
    params1.model_path = FLAGS_m;
    params1.p.nloops = FLAGS_loop_count;
    params1.nthreads = FLAGS_num_threads;
    params1.score_threshold = 0.7f;
    bboxes.clear();
    qrcode_detect_efficientdet_lite(image, bboxes, params1);
#endif
#if 0
    qrcode_params_opencv params2;
    params2.p.nloops = FLAGS_loop_count;
    bboxes.clear();
    qrcode_detect_opencv(image, bboxes, params2);
#endif
#if 0
    qrcode_params_opencv params3;
    params3.p.nloops = FLAGS_loop_count;
    bboxes.clear();
    qrcode_detect_and_decode_opencv(image, bboxes, params3);
#endif
#if 0
    qrcode_params_wechat params4;
    params4.p.nloops = FLAGS_loop_count;
    bboxes.clear();
    qrcode_detect_and_decode_wechat(image, bboxes, params4);
#endif
#if(WITH_ZXING)
    qrcode_params params5;
    params5.nloops = FLAGS_loop_count;
    bboxes.clear();
    qrcode_detect_and_decode_zxing(image, bboxes, params5);
#endif
    qrcode_params_quirc params6;
    params6.p.nloops = FLAGS_loop_count;
    bboxes.clear();
    qrcode_detect_and_decode_quirc(image, bboxes, params6);

    return 0;
}
