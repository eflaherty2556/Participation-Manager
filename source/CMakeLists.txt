# project
cmake_minimum_required(VERSION 3.14.3)
project(ParticipationManager)

# settings
set(CMAKE_CXX_STANDARD 17)
#add_compile_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

# requirements
find_package( OpenCV REQUIRED )
find_package( raspicam REQUIRED )
find_package( SQLite3 REQUIRED )

# source files
list(APPEND sources "DatabaseAccessor.cpp" "GetAllUsersRequest.cpp" "GetAllUsersResult.cpp")
list(APPEND sources "GetUserRequest.cpp" "GetUserResult.cpp" "QRScanner.cpp")
list(APPEND sources "Requester.cpp" "UpdateUserRequest.cpp" "UpdateUserResult.cpp")
list(APPEND sources "User.cpp")

# header files
list(APPEND headers "DatabaseAccessor.h" "QRScanner.h" "request.h")
list(APPEND headers "Requester.h" "result.h" "User.h")

# make executable file and link
add_executable( ParticipationManager ${sources} ${headers})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ParticipationManager ${OpenCV_LIBS} ${ZBAR_LIBRARIES}zbar ${raspicam_CV_LIBS} SQLite::SQLite3)
