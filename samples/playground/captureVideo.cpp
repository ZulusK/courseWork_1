//
// Created by zulus on 20.04.17.
//
//
// Программа получает видео с камеры и записывает в avi файл
//

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    cvNamedWindow("capture");

    // получаем любую подключённую камеру
    CvCapture *capture = cvCreateCameraCapture(CV_CAP_ANY);
    assert(capture!=0);

    const char *filename = "capture.avi";

    // частота кадров
    //double fps = cvGetCaptureProperty (capture, CV_CAP_PROP_FPS);
    double fps = 15;

    // размер картинки
    //CvSize size = cvSize( (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH), (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT));
    CvSize size = cvSize(640, 480);

    CvVideoWriter *writer = cvCreateVideoWriter(filename, CV_FOURCC('D', 'I', 'V', 'X') , fps, size, 0);
    assert(writer!=0);

    IplImage *frame=0;

    while(true){
        // получаем кадр
        frame = cvQueryFrame( capture );

        // сохраняем в файл
        cvWriteFrame(writer, frame);

        // показываем
        cvShowImage("capture", frame);
        char c = cvWaitKey(1);
        if (c == 27) { // если нажата ESC - выходим
            break;
        }
    }

    // освобождаем ресурсы
    cvReleaseCapture( &capture );
    cvReleaseVideoWriter(&writer);
    cvDestroyWindow("capture");
    return 0;
}
