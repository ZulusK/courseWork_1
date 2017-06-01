//
// пример выборки значений в заданном интервале
// cvInRangeS()
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    IplImage *src=0, *dst=0;

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

    cvInRangeS(src, cvScalar(50), cvScalar(255), dst);

    // показываем результаты
    cvNamedWindow( "cvInRangeS", 1 );
    cvShowImage( "cvInRangeS", dst);

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
    // удаляем окна
    cvDestroyAllWindows();
    return 0;
}