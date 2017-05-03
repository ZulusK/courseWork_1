//
// пример работы с ROI 2
// вывод в ROI другого изображения
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

IplImage *image = 0;
IplImage *src = 0;

int main(int argc, char *argv[]) {
    // имя картинки задаётся первым параметром
    char *filename = (char *) (argc >= 2 ? argv[1] : "Image0.jpg");
    // добавочное изображение
    char *filename2 = (char *) (argc >= 3 ? argv[2] : "eye.jpg");
    // получаем картинку
    image = cvLoadImage(filename, 1);

    printf("[i] image: %s\n", filename);
    printf("[im] image: %s\n", filename2);
    assert(image != 0);

    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("ROI", CV_WINDOW_AUTOSIZE);

    // задаём ROI
    int x = argc >= 3 ? atoi(argv[2]) : 120;
    int y = argc >= 4 ? atoi(argv[3]) : 50;

    src = cvLoadImage(filename2, 1);
    assert(src != 0);

    // размер ROI
    int width = 20;
    int height = 30;

    cvShowImage("origianl", image);
    // устанавливаем ROI
    cvSetImageROI(image, cvRect(x, y, width, height));

    // обнулим изображение
    cvZero(image);

    // копируем изображение
    cvCopy(src, image);

    // сбрасываем ROI
    cvResetImageROI(image);
    // показываем изображение
    cvShowImage("ROI", image);

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(&image);
    cvReleaseImage(&src);
    cvDestroyAllWindows();
    return 0;
}