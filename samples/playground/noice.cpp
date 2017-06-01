#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* dst = 0;

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    char* filename = (char*)(argc >= 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    image = cvLoadImage(filename,1);
    assert( image != 0 );

    // клонируем картинку
    dst = cvCloneImage(image);

    int count = 0;

    // окно для отображения картинки
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("noise",CV_WINDOW_AUTOSIZE);

    // инициализация состояния ГПСЧ
    CvRNG rng = cvRNG(0xffffffff);

    // пробегаемся по всем пикселям изображения
    for( int y=0; y<dst->height; y++ ) {
        uchar* ptr = (uchar*) (dst->imageData + y * dst->widthStep);
        for( int x=0; x<dst->width; x++ ) {
            if(cvRandInt(&rng)%100>=97){
                // 3 канала
                ptr[3*x] = cvRandInt(&rng)%255; // B
                ptr[3*x+1] = cvRandInt(&rng)%255; // G
                ptr[3*x+2] = cvRandInt(&rng)%255; // R
                count++;
                /**
                // красные пиксели
                ptr[3*x]=0;
                ptr[3*x+1]=0;
                ptr[3*x+2]=255;
                /**/
            }
        }
    }
    printf("[i] noise: %d (%.2f%c)\n", count, (float)count/(dst->height*dst->width)*100, '%');

    // показываем картинку
    cvShowImage("original",image);
    cvShowImage("noise",dst);

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(&image);
    cvReleaseImage(&dst);
    // удаляем окна
    cvDestroyWindow("original");
    cvDestroyWindow("noise");
    return 0;
}