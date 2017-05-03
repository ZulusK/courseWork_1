//
// применяем фильтр к изображению при помощи cvFilter2D()
//
// robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* dst = 0;

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    char* filename = (char*)(argc == 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    image = cvLoadImage(filename,1);

    printf("[i] image: %s\n", filename);
    assert( image != 0 );

    // клонируем картинку
    dst = cvCloneImage(image);

    // окно для отображения картинки
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("cvFilter2D",CV_WINDOW_AUTOSIZE);

    float kernel[9];
    kernel[0]=0;
    kernel[1]=0;
    kernel[2]=0;

    kernel[3]=0;
    kernel[4]=1;
    kernel[5]=0;

    kernel[6]=0;
    kernel[7]=1;
    kernel[8]=0;

    // матрица
    CvMat kernel_matrix=cvMat(3,3,CV_32FC1,kernel);

    // накладываем фильтр
    cvFilter2D(image, dst, &kernel_matrix, cvPoint(-1,-1));

    // показываем картинку
    cvShowImage("original",image);
    cvShowImage("cvFilter2D",dst);

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(&image);
    cvReleaseImage(&dst);
    // удаляем окна
    cvDestroyAllWindows();
    return 0;
}