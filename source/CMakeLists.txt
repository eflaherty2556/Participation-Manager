cmake_minimum_required(VERSION 2.8)
project(QRScanner)
find_package( OpenCV REQUIRED )
add_executable( QRScanner QRScanner.cpp QRScanner.h )
target_link_libraries( QRScanner ${OpenCV_LIBS} ${ZBAR_LIBRARIES}zbar)