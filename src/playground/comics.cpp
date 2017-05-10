//
// Прикольный эффект с использованием детектора Кенни:
// находятся контуры и вычитаются из изображения
//
// robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>


int xorder = 10;
int xorder_max = 100;

int yorder = 100;
int yorder_max = 200;

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
    IplImage *src=0, *dst=0, *dst2=0;

    // имя картинки задаётся первым параметром
    char* filename = (char*)(argc >= 2 ? argv[1] : "Image0.jpg");
    // получаем картинку в градациях серого
    src = cvLoadImage(filename, 0);

    printf("[i] image: %s\n", filename);
    assert( src != 0 );

    // покажем изображение
    cvNamedWindow( "original", 1 );
    cvShowImage( "original", src );

    // получим бинарное изображение
    dst2 = cvCreateImage( cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
    cvCanny(src, dst2, 50, 200);

    cvNamedWindow( "bin", 1 );
    cvShowImage( "bin", dst2);

    //cvScale(src, dst);
    cvSub(src, dst2, dst2);
    cvNamedWindow( "sub", 1 );
    cvShowImage( "sub", dst2);

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
            cvCanny(src, dst2, xorder, yorder);
            cvSub(src, dst2, dst2);
            // преобразуем изображение к 8-битному
            cvShowImage( "sub", dst2);
        }

        char c = cvWaitKey(33);
        if (c == 27) { // если нажата ESC - выходим
            break;
        }
    }

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
    cvReleaseImage(&dst2);
    // удаляем окна
    cvDestroyAllWindows();
    return 0;
}