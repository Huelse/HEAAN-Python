# PYHEAAN
This is a Python wrapper for HEAAN lib.

[HEAAN](https://github.com/snucrypto/HEAAN) is software library that implements homomorphic encryption (HE) that supports fixed point arithmetics.



## Build

* ### Environment

  CMake (>= 3.10), GNU G++ (>= 6.0) or Clang++ (>= 5.0), Python (>=3.6.8)

  ```shell
  sudo apt-get update && sudo apt-get install git g++ make python3 python3-dev python3.6-pip
  
  git clone https://github.com/Huelse/PYHEAAN.git
  ```

  

* ### NTL 

  [ntl-11.3.2](https://www.shoup.net/ntl/) (with GMP), pThread

  If you downloaded a new ntl package, you need change the `src/DoConfig` SHARED to on.

  ```
  cd NTL/src
  ./configure
  make
  make check
  sudo make install
  ```

  

* ### HEAAN

  #### Notice

  In "Params.h", 'pbnd' value is 59.0 by default. If you are using NTL with "NTL_ENABLE_AVX_FFT=on", This option reduces that small-prime size bound from 60 bits to 50 bits, [see](https://www.shoup.net/ntl/doc/tour-changes.html). For this reason, you need to change the setting to 49.0.

  [HEAAN-2.1](https://github.com/snucrypto/HEAAN)

  ```shell
  cd HEAAN/lib
  make all
  ```

  

* ### pybind11

  ```shell
  pip3 install pytest
  
  cd pybind11
  mkdir build
  cd build
  cmake ..
  make check -j 4
  sudo make install
  ```

  

* ### PYHEAAN

  ```shell
  cd src
  cmake .
  make
  ```

  or `python3 setup.py build_ext -i`

  if success, you will get the dynamic link library in the folder

## Test

```python
python test.py
```



## About

This lib is still in the experimental stage.

If any problems, tell me please.

Join us would be better.