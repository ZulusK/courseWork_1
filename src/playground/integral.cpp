//
// интегральное изображение cvIntegral()
//
// http://robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    IplImage *src=0, *dst=0, *dst2=0, *dst3=0;

    // имя картинки задаётся первым параметром
    const char* filename = argc >= 2 ? argv[1] : "Image0.jpg";
    // получаем картинку
    src = cvLoadImage(filename, 0);

    printf("[i] image: %s\n", filename);
    assert( src != 0 );

    // покажем изображение
    cvNamedWindow( "original", 1 );
    cvShowImage( "original", src );

    dst = cvCreateImage( cvSize(src->width+1, src->height+1), IPL_DEPTH_64F, 1);
    dst2 = cvCreateImage( cvSize(src->width+1, src->height+1), IPL_DEPTH_64F, 1);
    dst3 = cvCreateImage( cvSize(src->width+1, src->height+1), IPL_DEPTH_64F, 1);

    // получаем интегральное изображение
    cvIntegral(src, dst, dst2, dst3);

    cvNamedWindow( "cvIntegral", 1 );
    cvShowImage( "cvIntegral", dst );
    cvNamedWindow( "cvIntegral 2", 1 );
    cvShowImage( "cvIntegral 2", dst2 );
    cvNamedWindow( "cvIntegral tilted");
    cvShowImage( "cvIntegral tilted", dst3 );

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