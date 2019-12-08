# bfloat16
Inside source directory:
The bfloat16 class is implemented in bfloat16.hpp
a ad-hoc test called test_bfloat16.cpp used to test the implementation
it can be compiled by "g++ -o test_bfloat16 test_bfloat16.cpp"

Inside test directory:
The bfloat16_directed_test is implemented in test folder
it can be compiled by "g++ -o bfloat16_directed_test bfloat16_directed_test.cc"
The generated output files are saved in output directory.

Inside tf_test directory:
To run the TensorFlow bfloat16 inside tf_test folder, setup the python environment following the TensorFlow website: https://www.tensorflow.org/install and type "python tf_bfloat16_directed_test.py" to run the file.
The generated output files are saved in output directory.