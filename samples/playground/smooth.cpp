#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* dst = 0;

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    char* filename =(char*)( argc == 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    image = cvLoadImage(filename,1);
    // клонируем картинку
    dst = cvCloneImage(image);

    printf("[i] image: %s\n", filename);
    assert( image != 0 );

    // окно для отображения картинки
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("smooth",CV_WINDOW_AUTOSIZE);

    // сглаживаем исходную картинку
    cvSmooth(image, dst, CV_GAUSSIAN, 25, 3);

    // показываем картинку
    cvShowImage("original",image);
    cvShowImage("smooth",dst);

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(&image);
    cvReleaseImage(&dst);
    // удаляем окно
    cvDestroyWindow("original");
    cvDestroyWindow("smooth");
    return 0;
}