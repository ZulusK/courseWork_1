cmake_minimum_required(VERSION 2.8.9)
include_directories(src/include)
set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "bin")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
file(GLOB FACECOPE_SOURCES "src/*.cpp" "src/include/*.h")

project(Facecope)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} ${FACECOPE_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})


project(captureVideo)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/captureVideo.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

#`pkg-config opencv --cflags --libs`
project(cascadeClasified)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/cascadeClasified.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(helloWorld)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/helloWorld.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(imdisplay)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/imdisplay.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(immodify)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/immodify.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(picinfo)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/picInfo.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(trackDemo)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/trackDemo.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(videoDemo)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME}  "samples/playground/videoDemo.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(webcam)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/webcam.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(mouseTracking)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/mouseTracking.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(smooth)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/smooth.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(resize)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/resize.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(roi)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/roi.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(roiModify)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/roiModify.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})


project(xmlExample)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/xmlExample.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(noice)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/noice.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(morfologicTrans)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/morTrans.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(fill)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/fill.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(alpha)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/alphaBlending.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(threahold)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/threahold.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(threahold2)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/threahold2.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(threahold3)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/threahold3.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(rgband)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/RGBand.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(hsvand)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/hsvand.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(filter)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/filter.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(sobel)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/sobel.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(sobelFilter)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/sobelFilter.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(laplas)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/lapslasFilter.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})


project(canny)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/canny.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})


project(comics)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/comics.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(houghtTransform)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/HoughTransform.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(integral)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/integral.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(aphine)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/aphineTransfrom.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(contour)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/contour.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(contourCircle)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/contourCircle.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(faceDetector)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/faceDetector.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(fisherface)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "samples/playground/Fisherface.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})