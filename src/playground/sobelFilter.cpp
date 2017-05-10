//
// пример работы оператора Собеля - cvSobel()
//
// robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* dst = 0;
IplImage* dst2 = 0;

int xorder = 1;
int xorder_max = 2;

int yorder = 1;
int yorder_max = 2;

//
// функция-обработчик ползунка - 
// порядок производной по X
void myTrackbarXorder(int pos) {
    xorder = pos;
}

//
// функция-обработчик ползунка - 
// порядок производной по Y
void myTrackbarYorder(int pos) {
    yorder = pos;
}

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    char* filename = (char*)(argc >= 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    image = cvLoadImage(filename, 1);
    // создаём картинки
    dst = cvCreateImage( cvSize(image->width, image->height), IPL_DEPTH_16S, image->nChannels);
    dst2 = cvCreateImage( cvSize(image->width, image->height), image->depth, image->nChannels);

    printf("[i] image: %s\n", filename);
    assert( image != 0 );

    // окно для отображения картинки
    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("sobel", CV_WINDOW_AUTOSIZE);


    int aperture = argc == 3 ? atoi(argv[2]) : 3;

    cvCreateTrackbar("xorder", "original", &xorder, xorder_max, myTrackbarXorder);
    cvCreateTrackbar("yorder", "original", &yorder, yorder_max, myTrackbarYorder);

    while(1){

        // проверяем, чтобы порядок производных по X и Y был отличен от 0
        if(xorder==0 && yorder==0){
            printf("[i] Error: bad params for cvSobel() !\n");
            cvZero(dst2);
        }
        else{
            // применяем оператор Собеля
            cvSobel(image, dst, xorder, yorder, aperture);
            // преобразуем изображение к 8-битному
            cvConvertScale(dst, dst2);
        }

        // показываем картинку
        cvShowImage("original", image);
        cvShowImage("sobel", dst2);

        char c = cvWaitKey(33);
        if (c == 27) { // если нажата ESC - выходим
            break;
        }
    }

    // освобождаем ресурсы
    cvReleaseImage(& image);
    cvReleaseImage(&dst);
    cvReleaseImage(&dst2);
    // удаляем окна
    cvDestroyAllWindows();
    return 0;
}