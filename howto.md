
Do:
~~~
conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"
~~~

Then:
~~~
mkdir build && cd build
conan install ..
cmake ..
~~~

