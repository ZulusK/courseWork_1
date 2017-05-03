//
// пример базовых морфологических преобразований
// cvErode() и cvDilate()
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* dst = 0;

IplImage* erode = 0;
IplImage* dilate = 0;

int radius = 1;
int radius_max=10;

//
// функция-обработчик ползунка -
// радиус ядра
void myTrackbarRadius(int pos) {
    radius = pos;
}

int iterations = 1;
int iterations_max = 10;

//
// функция-обработчик ползунка -
// число итераций
void myTrackbarIterations(int pos) {
    iterations = pos;
}

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    char* filename = (char*)(argc == 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    image = cvLoadImage(filename,1);
    // клонируем картинку
    dst = cvCloneImage(image);
    erode = cvCloneImage(image);
    dilate = cvCloneImage(image);

    printf("[i] image: %s\n", filename);
    assert( image != 0 );

    // окно для отображения картинки
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("erode",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("dilate",CV_WINDOW_AUTOSIZE);

    cvCreateTrackbar("Radius", "original", &radius, radius_max, myTrackbarRadius);
    cvCreateTrackbar("Iterations", "original", &iterations, iterations_max, myTrackbarIterations);


    while(1){

        // показываем картинку
        cvShowImage("original",image);

        // создаём ядро
        IplConvKernel* Kern = cvCreateStructuringElementEx(radius*2+1, radius*2+1, radius, radius, CV_SHAPE_ELLIPSE);

        // выполняем преобразования
        cvErode(image, erode, Kern, iterations);
        cvDilate(image, dilate, Kern, iterations);

        // показываем результат
        cvShowImage("erode",erode);
        cvShowImage("dilate",dilate);

        cvReleaseStructuringElement(&Kern);

        char c = cvWaitKey(33);
        if (c == 27) { // если нажата ESC - выходим
            break;
        }
    }

    // освобождаем ресурсы
    cvReleaseImage(&image);
    cvReleaseImage(&dst);
    cvReleaseImage(&erode);
    cvReleaseImage(&dilate);
    // удаляем окно
    cvDestroyWindow("original");
    cvDestroyWindow("erode");
    cvDestroyWindow("dilate");
    return 0;
}