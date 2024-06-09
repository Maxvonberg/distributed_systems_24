FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    wget \
    g++ \
    git \
    cmake \
    libboost-dev \
    libboost-regex-dev \
    libasio-dev \
    libsqlite3-dev

WORKDIR /backend

RUN git clone https://github.com/CrowCpp/Crow.git
RUN git clone https://github.com/SRombauts/SQLiteCpp.git

WORKDIR /backend/Crow
RUN mkdir build && cd build && cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && make install

WORKDIR /backend/SQLiteCpp
RUN mkdir build && cd build && cmake .. -DBUILD_SHARED_LIBS=ON && make install

WORKDIR /backend

COPY . /backend

ENV LD_LIBRARY_PATH=/usr/local/lib

RUN g++ -o main main.cpp -std=c++20 -lpthread -lSQLiteCpp

EXPOSE 9999

CMD ["./main"]
