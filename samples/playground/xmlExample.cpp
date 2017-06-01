//
// пример сохранения/загрузки
// данных из XML-файла
// и 3 способа получения элементов матрицы
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

//int main(int argc, char* argv[])
//{
//    // массив, содержащий данные матрицы
//    float kernel[9];
//    kernel[0]=1;
//    kernel[1]=0;
//    kernel[2]=0;
//
//    kernel[3]=0;
//    kernel[4]=2;
//    kernel[5]=0;
//
//    kernel[6]=0;
//    kernel[7]=0;
//    kernel[8]=3;
//
//    // создаём матрицу
//    CvMat kernel_matrix=cvMat(3,3,CV_32FC1,kernel);
//
//    // сохраняем матрицу в XML-файл
//    cvSave("kernel.xml", &kernel_matrix);
//
//    // а теперь загрузим данные из XML-файла
//    CvMat* matrix = (CvMat*)cvLoad("kernel.xml");
//
//    // покажем содержимое матрицы
//    //
//    int i=0, j=0;
//
//    // 1 вариант: с использованием макроса CV_MAT_ELEM
//    for(i=0; i<matrix->rows; i++){
//        for(j=0; j<matrix->cols; j++){
//            printf("%.0f ", CV_MAT_ELEM( *matrix, float, i, j));
//        }
//        printf("\n");
//    }
//    printf("-----\n");
//    // 2 вариант: с использованием cvGet2D(), cvGetReal2D()
//    for(i=0; i<matrix->rows; i++){
//        for(j=0; j<matrix->cols; j++){
//            printf("%.0f ", cvGet2D(matrix, i, j));//cvGetReal2D(matrix, i, j));
//        }
//        printf("\n");
//    }
//    printf("-----\n");
//    // 3 вариант: прямой доступ к элементам
//    for(i=0; i<matrix->rows; i++){
//        float* ptr = (float*)(matrix->data.ptr + i*matrix->step);
//        for(j=0; j<matrix->cols; j++){
//            printf("%.0f ", ptr[j]);
//        }
//        printf("\n");
//    }
//
//    // освобождаем ресурсы
//    cvReleaseMat(&matrix);
//
//    return 0;
//}

// Несколько модифицированный пример Example 3-17.
// демонстрирующий запись значений в xml-файл
//
// из книги:
//   Learning OpenCV: Computer Vision with the OpenCV Library
//     by Gary Bradski and Adrian Kaehler
//     Published by O'Reilly Media, October 3, 2008
// p83

//#include <cv.h>
//#include <highgui.h>
//#include <stdio.h>
//
//int main(int argc, char** argv)
//{
//    CvMat *cmatrix = cvCreateMat(5,5,CV_32FC1);
//    float element_3_2 = 7.7;
//    *((float*)CV_MAT_ELEM_PTR( *cmatrix, 3,2) ) = element_3_2;
//    cvmSet(cmatrix,4,4,0.5000);
//    cvSetReal2D(cmatrix,3,3,0.5000);
//    printf("Example 3_17, writing cfg.xml\n");
//    // открываем файл для записи
//    CvFileStorage* fs = cvOpenFileStorage(
//            "cfg.xml",
//            0,
//            CV_STORAGE_WRITE
//    );
//    // записываем значения
//    cvWriteInt( fs, "frame_count", 10 );
//    cvStartWriteStruct( fs, "frame_size", CV_NODE_SEQ);
//    cvWriteInt( fs, 0, 320 );
//    cvWriteInt( fs, 0, 200 );
//    cvEndWriteStruct(fs);
//    cvWrite( fs, "color_cvt_matrix", cmatrix );
//    cvReleaseFileStorage( &fs );
//    return 0;
//}


// Несколько модифицированный пример Example 3-19.
// демонстрирующий считывание значений из xml-файла
//
// из книги:
//   Learning OpenCV: Computer Vision with the OpenCV Library
//     by Gary Bradski and Adrian Kaehler
//     Published by O'Reilly Media, October 3, 2008
// p84

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    printf("Example 3_19 Reading in cfg.xml\n");

    // открываем файл для чтения
    CvFileStorage* fs = cvOpenFileStorage(
            "cfg.xml",
            0,
            CV_STORAGE_READ
    );

    //
    // считываем значения
    //
    int frame_count = cvReadIntByName(
            fs,
            0,
            "frame_count",
            5 // значение по-умолчанию
    );

    CvSeq* s = cvGetFileNodeByName(fs,0,"frame_size")->data.seq;

    int frame_width = cvReadInt(
            (CvFileNode*)cvGetSeqElem(s,0)
    );

    int frame_height = cvReadInt(
            (CvFileNode*)cvGetSeqElem(s,1)
    );

    CvMat* color_cvt_matrix = (CvMat*) cvRead(
            fs,
            0
    );

    // показываем
    printf("frame_count=%d, frame_width=%d, frame_height=%d\n",frame_count,frame_width,frame_height);

    cvReleaseFileStorage( &fs );
    return 0;
}