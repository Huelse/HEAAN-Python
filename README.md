# PYHEAAN
This is a Python wrapper for HEAAN library.

[HEAAN](https://github.com/snucrypto/HEAAN) is a software library that implements homomorphic encryption (HE) that supports fixed point arithmetics. This library supports approximate operations between rational numbers. The approximate error depends on some parameters and almost same with floating point operation errors. The scheme in this library is on the [paper](https://eprint.iacr.org/2016/421.pdf).



## Build

* ### Environment

  CMake (>= 3.12), GNU G++ (>= 6.0) or Clang++ (>= 5.0)

  ```shell
  sudo apt-get update && sudo apt-get install git build-essential cmake python3 python3-dev python3.6-pip
  
  git clone https://github.com/Huelse/HEAAN-Python.git
  ```



* ### GMP

  [gmp-6.1.2](https://gmplib.org/download/gmp/gmp-6.1.2.tar.lz)

  ```shell
  cd gmp-6.1.2
  ./configure SHARED=on # default install in /usr/local, option --prefix=/path/to/extends
  make
  make check  # optional
  make install
  ```



* ### NTL 

  [ntl-11.4.3](https://www.shoup.net/ntl/)

  ```shell
  cd NTL/src
  ./configure SHARED=on  # default install in /usr/local, option DEF_PREFIX=/path/to/extends
  make
  make check  # optional
  sudo make install
  ```



* ### HEAAN

  [HEAAN-2.1](https://github.com/snucrypto/HEAAN)

  In "Params.h", 'pbnd' value is 59.0 by default. If you are using NTL with "NTL_ENABLE_AVX_FFT=on", This option reduces that small-prime size bound from 60 bits to 50 bits, [see](https://www.shoup.net/ntl/doc/tour-changes.html). For this reason, you need to change the setting to 49.0.

  ```shell
  cd HEAAN/lib
  make all
  ```



* ### pybind11

  [pybind11](https://github.com/pybind/pybind11)

  ```shell
  # Option 1 to run setup.py
  pip3 install -r requirements.txt

  # Option 2 to run cmake
  cd pybind11
  mkdir build && cd build
  cmake ..
  make
  sudo make install
  ```



* ### HEAAN-Python

  * Option 1

  ```shell
  python3 setup.py build_ext -i

  python3 setup.py install  # global install
  ```

  * Option 2
  
  ```shell
  cd src
  cmake .
  make
  ```

  If success, you will get the dynamic link library in the folder, which name `HEAAN.cpython-<version>.so`.



## Test

make sure you already installed the library globally or the file `HEAAN.cpython-<version>.so` in the current directory.

```python3
python3 test.py
```



## FAQ

1. ImportError: libntl.so.43: cannot find

    * `export LD_LIBRARY_PATH=/path/to/extends/lib`

    * add the `/path/to/extends/lib` to `/etc/ld.so.conf` and refresh it `sudo ldconfig`

    * install the NTL and gmp in `/usr/local` as default

2. MakeError: /usr/bin/ld: cannot find libntl.so or libHEAAN.a

    Change to absolute path.



## About

This lib is still in the experimental stage.

If any problems, email or [Issue](/Huelse/HEAAN-Python/issues).

Email: [huelse@oini.top](mailto:huelse@oini.top?subject=Github-HEAAN-Python-Issues&cc=5956877@qq.com).



## Contributing

* Professor: [Dr. Chen](https://zhigang-chen.github.io/)
