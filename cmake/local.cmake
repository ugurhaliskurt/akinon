set(Sources
src/main.cpp
src/Application.cpp
src/server/RestServer.cpp
)

find_library(CPPREST_LIB cpprest)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(OpenSSL 1.0.0 REQUIRED)

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;checks=-*")
add_executable(${EXE_NAME}
${Sources}
)

target_link_libraries( ${EXE_NAME} PUBLIC
${CPPREST_LIB}
-lcurl
-lpthread
-lcrypto
OpenSSL::SSL
Boost::filesystem
)
# add_coverage(${EXE_NAME})
# add_coverage(${LIB_NAME})
# set_property(TARGET ${LIB_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy    
  ${CMAKE_SOURCE_DIR}/Banner.txt 
  ${CMAKE_BINARY_DIR}/Banner.txt
)  

# some test        
# list(APPEND LCOV_REMOVE_PATTERNS "/usr/")

# Installation
# install(CODE "MESSAGE(\"Installing ${PROJECT_NAME} \")")
# install(TARGETS  ${PROJECT_NAME}
#         RUNTIME DESTINATION bin
#         LIBRARY DESTINATION lib
#         ARCHIVE DESTINATION lib)