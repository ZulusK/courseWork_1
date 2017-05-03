cmake_minimum_required(VERSION 2.8.9)
include_directories(src/include)
set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "bin")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
file(GLOB FACECOPE_SOURCES "src/main.cpp" "src/playground/*.cpp")

project(facecope)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} ${FACECOPE_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})


project(captureVideo)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/captureVideo.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

#`pkg-config opencv --cflags --libs`
project(cascadeClasified)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/cascadeClasified.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(helloWorld)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/helloWorld.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(imdisplay)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/imdisplay.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(immodify)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/immodify.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(picinfo)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/picInfo.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(trackDemo)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/trackDemo.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(videoDemo)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME}  "src/playground/videoDemo.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(webcam)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/webcam.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(mouseTracking)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/mouseTracking.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(smooth)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/smooth.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(resize)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/resize.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(roi)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/roi.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(roiModify)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/roiModify.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})


project(xmlExample)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/xmlExample.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(noice)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/noice.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(morfologicTrans)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/morTrans.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(fill)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/fill.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(alpha)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/alphaBlending.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(threahold)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/threahold.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(threahold2)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/threahold2.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(threahold3)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/threahold3.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(rgband)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/RGBand.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(hsvand)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/hsvand.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

project(skin)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/skinDetector.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})


project(filter)
find_package( OpenCV REQUIRED )
add_executable(${CMAKE_PROJECT_NAME} "src/playground/filter.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})