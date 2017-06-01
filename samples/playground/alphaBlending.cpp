//
// alpha blending
// взвешенная поэлементная сумма двух массивов - cvAddWeighted()
//
//  http://dasl.mem.drexel.edu/~noahKuntz/openCVTut2.html
//

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

IplImage* image = 0;
IplImage* templ = 0;
IplImage* dst = 0;

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    char* filename =(char*)( argc >= 2 ? argv[1] : "Image0.jpg");
    // получаем картинку
    image = cvLoadImage(filename,1);

    printf("[i] image: %s\n", filename);
    assert( image != 0 );

    // шаблон
    char* filename2 =(char*)( argc >= 3 ? argv[2] : "templ.bmp");
    printf("[i] template: %s\n", filename2);

    templ = cvLoadImage(filename2,1);
    assert( templ != 0 );

    cvNamedWindow("origianl", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("template", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("res", CV_WINDOW_AUTOSIZE);

    dst = cvCloneImage(templ);

    // размер шаблона
    int width = templ->width;
    int height = templ->height;

    // оригинал и шаблон
    cvShowImage( "origianl", image);
    cvShowImage( "template", templ);

    int x = 0;
    int y = 0;
    // задаём весовые коэффициенты
    double alpha = 0.5;
    double beta = 0.5;
    // устанавливаем область интереса
    cvSetImageROI(image, cvRect(x,y,width,height));
    // взвешенная сумма
    cvAddWeighted(image, alpha, templ, beta, 0.0, dst);
    // освобождаем область интереса
    cvResetImageROI(image);

    // показываем результат
    cvShowImage( "res", dst);

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage( &image );
    cvReleaseImage( &templ );
    cvReleaseImage( &dst );
    cvDestroyAllWindows();
    return 0;
}
