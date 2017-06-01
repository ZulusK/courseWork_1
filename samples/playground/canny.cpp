//
// пример работы детектора границ Кенни - cvCanny()
//
// robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* gray = 0;
IplImage* dst = 0;

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    char* filename = (char*)(argc == 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    image = cvLoadImage(filename,1);

    printf("[i] image: %s\n", filename);
    assert( image != 0 );

    // создаём одноканальные картинки
    gray = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
    dst = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );

    // окно для отображения картинки
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("gray",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("cvCanny",CV_WINDOW_AUTOSIZE);

    // преобразуем в градации серого
    cvCvtColor(image, gray, CV_RGB2GRAY);

    // получаем границы
    cvCanny(gray, dst, 100, 250, 3);

    // показываем картинки
    cvShowImage("original",image);
    cvShowImage("gray",gray);
    cvShowImage("cvCanny", dst );

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(&image);
    cvReleaseImage(&gray);
    cvReleaseImage(&dst);
    // удаляем окна
    cvDestroyAllWindows();
    return 0;
}