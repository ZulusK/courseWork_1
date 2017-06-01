////
//// нахождение линий на изображении,
//// с использованием преобразования Хафа cvHoughLines2()
////
//// модифицированный пример samples\c\houghlines.c
////
//// http://robocraft.ru
////
//
//#include <cv.h>
//#include <highgui.h>
//#include <math.h>
//
//int main(int argc, char* argv[])
//{
//    IplImage* src = 0;
//    IplImage* dst=0;
//    IplImage* color_dst=0;
//
//    // имя картинки задаётся первым параметром
//    char* filename = (char*)(argc >= 2 ? argv[1] : "Image0.jpg");
//    // получаем картинку (в градациях серого)
//    src = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
//
//    if( !src ){
//        printf("[!] Error: cant load image: %s \n", filename);
//        return -1;
//    }
//
//    printf("[i] image: %s\n", filename);
//
//
//    // хранилище памяти для хранения найденных линий
//    CvMemStorage* storage = cvCreateMemStorage(0);
//    CvSeq* lines = 0;
//    int i = 0;
//
//
//    dst = cvCreateImage( cvGetSize(src), 8, 1 );
//    color_dst = cvCreateImage( cvGetSize(src), 8, 3 );
//
//    // детектирование границ
//    cvCanny( src, dst, 50, 200, 3 );
//
//    // конвертируем в цветное изображение
//    cvCvtColor( dst, color_dst, CV_GRAY2BGR );
//
//    // нахождение линий
//    lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 50, 50, 10 );
//
//    // нарисуем найденные линии
//    for( i = 0; i < lines->total; i++ ){
//        CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
//        cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 3, CV_AA, 0 );
//    }
//
//    // показываем
//    cvNamedWindow( "Source", 1 );
//    cvShowImage( "Source", src );
//
//    cvNamedWindow( "Hough", 1 );
//    cvShowImage( "Hough", color_dst );
//
//    // ждём нажатия клавиши
//    cvWaitKey(0);
//
//    // освобождаем ресурсы
//    cvReleaseMemStorage(&storage);
//    cvReleaseImage(&src);
//    cvReleaseImage(&dst);
//    cvReleaseImage(&color_dst);
//    cvDestroyAllWindows();
//    return 0;
//}



//
// Несколько модифицированный пример example 6-1 Hough circles
// нахождение кругов на изображении,
// с использованием трансформации Хафа cvHoughCircles()
//
// из книги:
//   Learning OpenCV: Computer Vision with the OpenCV Library
//     by Gary Bradski and Adrian Kaehler
//     Published by O'Reilly Media, October 3, 2008
//
//
// http://robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <math.h>

int main(int argc, char* argv[])
{
    IplImage* image = 0;
    // имя картинки задаётся первым параметром
    char* filename = (char*)(argc >= 2 ? argv[1] : "Image0.jpg");
    // получаем картинку (в градациях серого)
    image = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);

    printf("[i] image: %s\n", filename);
    assert( image != 0 );

    // загрузим оригинальное изображении
    IplImage* src = cvLoadImage(filename );

    // хранилище памяти для кругов
    CvMemStorage* storage = cvCreateMemStorage(0);
    // сглаживаем изображение
    cvSmooth(image, image, CV_GAUSSIAN, 5, 5 );
    // поиск кругов
    CvSeq* results = cvHoughCircles(
            image,
            storage,
            CV_HOUGH_GRADIENT,
            10,
            image->width/5
    );
    // пробегаемся по кругам и рисуем их на оригинальном изображении
    for( int i = 0; i < results->total; i++ ) {
        float* p = (float*) cvGetSeqElem( results, i );
        CvPoint pt = cvPoint( cvRound( p[0] ), cvRound( p[1] ) );
        cvCircle( src, pt, cvRound( p[2] ), CV_RGB(0xff,0,0) );
    }
    // показываем
    cvNamedWindow( "cvHoughCircles", 1 );
    cvShowImage( "cvHoughCircles", src);

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseMemStorage(&storage);
    cvReleaseImage(& image);
    cvReleaseImage(&src);
    cvDestroyAllWindows();
    return 0;
}
