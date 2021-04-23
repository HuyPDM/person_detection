#include "object_detection.h"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>
#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
    std::string pipeline = "v4l2src device=/dev/video1 ! image/jpeg, width=(int)1280, height=(int)720, framerate=30/1 ! jpegdec ! videoconvert ! appsink";
    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    cv::Mat frame;

    ObjectDetection det("../../pedestrian_detection/");
    auto m_StartTime = std::chrono::system_clock::now();
    while(true)
    {
        cap >> frame;
	double fps = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_StartTime).count();
	m_StartTime = std::chrono::system_clock::now();
	cv::putText(frame, to_string(static_cast<int>(1000/fps)) + " FPS", cv::Point(10, 30), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 255), 1, false);
        //std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        //auto recs = det.detectObject(frame);
        //std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        //std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
        //std::cout<<"Optical flow time: " << time_used.count() << "seconds" << std::endl;

        //for(auto rec:recs)
        //{
        //    cv::rectangle(frame, rec, cv::Scalar(0, 255, 0), 2, 1);
        //}

        cv::imshow("detection", frame);
        if(cv::waitKey(1) == 27)
        {
            break;
        }
    }
    cap.release();
    cv::destroyAllWindows() ;
    return 0;
}
