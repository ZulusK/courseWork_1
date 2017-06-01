//
// модифицированный пример Example 6-2. Аффинные трансформации
//
// из книги:
//   Learning OpenCV: Computer Vision with the OpenCV Library
//     by Gary Bradski and Adrian Kaehler
//     Published by O'Reilly Media, October 3, 2008
//
// http://robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    IplImage *src=0, *dst=0;

    // имя картинки задаётся первым параметром
    const char* filename = argc == 2 ? argv[1] : "Image0.jpg";
    // получаем картинку
    src = cvLoadImage(filename,1);

    printf("[i] image: %s\n", filename);
    assert( src != 0 );

    // покажем изображение
    cvNamedWindow( "image", 1 );
    cvShowImage( "image", src );

    CvPoint2D32f srcTri[3], dstTri[3];
    // матрицы трансформации
    CvMat* rot_mat = cvCreateMat(2, 3, CV_32FC1);
    CvMat* warp_mat = cvCreateMat(2, 3, CV_32FC1);

    // клонируем изображение
    dst = cvCloneImage(src);

#if 1

    //
    // трансформация по точкам
    //

    // по заданным точкам
    // вычислим матрицу преобразования
    srcTri[0].x = 0;          //src Top left
    srcTri[0].y = 0;
    srcTri[1].x = src->width - 1;    //src Top right
    srcTri[1].y = 0;
    srcTri[2].x = 0;          //src Bottom left
    srcTri[2].y = src->height - 1;
    //- - - - - - - - - - - - - - -//
    dstTri[0].x = src->width*0.0;    //dst Top left
    dstTri[0].y = src->height*0.33;
    dstTri[1].x = src->width*0.85; //dst Top right
    dstTri[1].y = src->height*0.25;
    dstTri[2].x = src->width*0.15; //dst Bottom left
    dstTri[2].y = src->height*0.7;
    // получаем матрицу
    cvGetAffineTransform(srcTri,dstTri,warp_mat);
    // выполняем трансформацию
    cvWarpAffine(src,dst,warp_mat);
#endif

    // сохраним результат трансформации
    cvCopy(dst, src);

#if 1
    //
    // поворот изображения
    //

    // рассчёт матрицы вращения
    CvPoint2D32f center = cvPoint2D32f(src->width/2, src->height/2);
    double angle = -60.0;   // на 60 градусов по часовой стрелке
    double scale = 0.7;             // масштаб
    cv2DRotationMatrix(center,angle,scale,rot_mat);

    // выполняем вращение
    cvWarpAffine(src, dst, rot_mat);
#endif

    // показываем
    cvNamedWindow( "cvWarpAffine");
    cvShowImage( "cvWarpAffine", dst );

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseMat(&rot_mat);
    cvReleaseMat(&warp_mat);

    cvReleaseImage(&src);
    cvReleaseImage(&dst);

    // удаляем окна
    cvDestroyAllWindows();
    return 0;
}