//
// пример использования функции cvFloodFill()
// для заливки области
// начальный пиксель области выбирается по клику мышкой
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

// заливка области картинки цветом
void fill(IplImage* src, CvPoint seed, CvScalar color=CV_RGB(255, 0, 0))
{
    assert(src);

    CvConnectedComp comp;

    cvFloodFill( src, seed, color,
                 cvScalarAll(10), // минимальная разность
                 cvScalarAll(10), // максимальная разность
                 &comp,
                 CV_FLOODFILL_FIXED_RANGE + 8,
                 0);

    // покажем площадь заливки
    printf("[filled area] %.2f\n", comp.area);
}

// обработчик событий от мышки
void myMouseCallback( int event, int x, int y, int flags, void* param )
{
    IplImage* img = (IplImage*) param;

    switch( event ){
        case CV_EVENT_MOUSEMOVE:
//            break;

        case CV_EVENT_LBUTTONDOWN:
            printf("%d x %d\n", x, y);

            // вызываем нашу функцию-обёртку вокруг cvFloodFill()
            fill(img, cvPoint(x, y));

            break;

        case CV_EVENT_LBUTTONUP:
            break;
    }
}

int main(int argc, char* argv[])
{
    IplImage *src=0, *dst=0;

    // имя картинки задаётся первым параметром
    char* filename =(char*)( argc >= 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    src = cvLoadImage(filename, 1);

    printf("[i] image: %s\n", filename);
    assert( src != 0 );

    // покажем изображение
    cvNamedWindow( "original", 1 );

    // вешаем обработчик мышки
    cvSetMouseCallback( "original", myMouseCallback, (void*) src);

    while(1){
        // показываем картинку
        cvShowImage( "original", src );

        char c = cvWaitKey(33);
        if (c == 27) { // если нажата ESC - выходим
            break;
        }
    }

    // освобождаем ресурсы
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
    // удаляем окна
    cvDestroyAllWindows();
    return 0;
}