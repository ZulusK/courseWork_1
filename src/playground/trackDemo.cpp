#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdlib.h>
#include <stdio.h>

CvCapture *capture = 0;
IplImage *frame = 0;

//
// функция-обработчик ползунка - 
// перематывает на нужный кадр
void myTrackbarCallback(int pos) {
    cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, pos);
}

int main(int argc, char *argv[]) {
    // имя файла задаётся первым параметром
    char *filename = (char *) (argc == 2 ? argv[1] : "test.avi");

    printf("[i] file: %s\n", filename);

    // окно для отображения картинки
    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);

    // получаем информацию о видео-файле
    capture = cvCreateFileCapture(filename);

    // получаем число кадров
    double framesCount = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
    printf("[i] count: %.0f\n", framesCount);
    int frames = (int) framesCount;

    int currentPosition = 0;
    if (frames != 0) {
        // показываем ползунок
        cvCreateTrackbar("Position", "original", &currentPosition, frames, myTrackbarCallback);
    }

    while (1) {
        // получаем следующий кадр
        frame = cvQueryFrame(capture);
        if (!frame) {
            break;
        }

        // здесь можно вставить
        // процедуру обработки

        // показываем кадр
        cvShowImage("original", frame);

        char c = cvWaitKey(33);
        if (c == 27) { // если нажата ESC - выходим
            break;
        } else {
            cvSetTrackbarPos( "Position", "original",c);
        }
    }

    // освобождаем ресурсы
    cvReleaseCapture(&capture);
    // удаляем окно
    cvDestroyWindow("original");
    return 0;
}