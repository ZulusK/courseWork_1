//
// Прикольный эффект с использованием детектора Кенни:
// находятся контуры и вычитаются из изображения
//
// robocraft.ru
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>


int xorder = 10;
int xorder_max = 255;

int yorder = 100;
int yorder_max = 255;

//
// функция-обработчик ползунка -
// порядок производной по X
void myTrackbarXorder(int pos) {
    xorder = pos;
}

//
// функция-обработчик ползунка -
// порядок производной по Y
void myTrackbarYorder(int pos) {
    yorder = pos;
}


int main(int argc, char *argv[]) {
    IplImage *src = 0, *r_plane = 0, *g_plane = 0, *b_plane = 0;
    IplImage *g_bin = 0, *r_bin = 0, *b_bin = 0, *bin = 0, *smooth=0;

    // получаем любую подключённую камеру
    CvCapture *capture = cvCreateCameraCapture(CV_CAP_ANY); //cvCaptureFromCAM( 0 );
    assert(capture);
//    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 1280);//1280);
//    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 960);//960);
    // узнаем ширину и высоту кадра
    double width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    double height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);

    cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("comics", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("bin", CV_WINDOW_AUTOSIZE);
    cvCreateTrackbar("xorder", "capture", &xorder, xorder_max, myTrackbarXorder);
    cvCreateTrackbar("yorder", "capture", &yorder, yorder_max, myTrackbarYorder);
    src = cvQueryFrame(capture);
    smooth=cvCloneImage(src);
    // получим бинарное изображение
    bin = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    g_bin = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    b_bin = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    r_bin = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    r_plane = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    g_plane = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    b_plane = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

    float kernel[9];
    // увеличение чёткости
    kernel[0]=-0.1;
    kernel[1]=-0.1;
    kernel[2]=-0.1;

    kernel[3]=-0.1;
    kernel[4]=2;
    kernel[5]=-0.1;

    kernel[6]=-0.1;
    kernel[7]=-0.1;
    kernel[8]=-0.1;
    // матрица
    CvMat kernel_matrix=cvMat(3,3,CV_32FC1,kernel);

    while (1) {
        src = cvQueryFrame(capture);
        // накладываем фильтр
        cvFilter2D(src, smooth, &kernel_matrix, cvPoint(-1,-1));
        cvShowImage("capture", smooth);
//        cvSmooth(src, smooth, CV_GAUSSIAN, 3,3);

        // проверяем, чтобы порядок производных по X и Y был отличен от 0
        if (xorder == 0 && yorder == 0) {
            printf("[i] Error: bad params for cvSobel() !\n");
        } else {
            // разбиваем на отельные каналы
            cvSplit(smooth, b_plane, g_plane, r_plane, 0);
            // преобразуем в градации серого
            cvCanny(b_plane, b_bin, xorder, yorder);
            cvCanny(r_plane, r_bin, xorder, yorder);
            cvCanny(g_plane, g_bin, xorder, yorder);
            // складываем
            cvAnd(b_bin, g_bin, bin);
            cvAnd(b_bin, bin, bin);

            cvSub(b_plane, bin, b_plane);
            cvSub(r_plane, bin, r_plane);
            cvSub(g_plane, bin, g_plane);
            cvMerge(b_plane, g_plane, r_plane, NULL, smooth);
            cvShowImage("bin", bin);
            cvShowImage("comics", smooth);

        }

        char c = cvWaitKey(33);
        if (c == 27) { // если нажата ESC - выходим
            break;
        }
    }
    // освобождаем ресурсы
    cvReleaseImage(&src);
    cvReleaseImage(&r_bin);
    cvReleaseImage(&g_bin);
    cvReleaseImage(&b_bin);
    cvReleaseImage(&g_plane);
    cvReleaseImage(&b_plane);
    cvReleaseImage(&r_plane);
    // удаляем окна
    cvDestroyAllWindows();
    return 0;
}