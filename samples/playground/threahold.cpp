//
// пример порогового преобразования
// cvThreshold() и cvAdaptiveThreshold()
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    IplImage *src=0, *dst=0, *dst2=0;

    // имя картинки задаётся первым параметром
        char* filename = (char *)(argc >= 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    src = cvLoadImage(filename, 0);

    printf("[i] image: %s\n", filename);
    assert( src != 0 );

    // покажем изображение
    cvNamedWindow( "original", 1 );
    cvShowImage( "original", src );

    dst = cvCreateImage( cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
    dst2 = cvCreateImage( cvSize(src->width, src->height), IPL_DEPTH_8U, 1);

    cvThreshold(src, dst, 50, 250, CV_THRESH_BINARY);
    cvAdaptiveThreshold(src, dst2, 250, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 7, 1);

    // показываем результаты
    cvNamedWindow( "cvThreshold", 1 );
    cvShowImage( "cvThreshold", dst);
    cvNamedWindow( "cvAdaptiveThreshold", 1 );
    cvShowImage( "cvAdaptiveThreshold", dst2);

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