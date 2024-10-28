cmake_minimum_required(VERSION 3.27)
project(kursova)

set(CMAKE_CXX_STANDARD 17)

add_executable(kursova main.cpp
        ProductManager.h
        Human.h
        Product.h
        ElectricalProduct.h
        Employee.h
        Checkout.h
        Logger.h
        Logger.h
)
