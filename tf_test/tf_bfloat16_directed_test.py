import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
import tensorflow as tf
import numpy
import time

dir1 = "../output/tf_test1.txt"
dir2 = "../output/tf_test2.txt"
dir_sub = "../output/tf_test_subtract.txt"
dir_add = "../output/tf_test_add.txt"
dir_divide = "../output/tf_test_divide.txt"
dir_multiply = "../output/tf_test_multiply.txt"

# test the transformation between float32 and bfloat16
def test_float32_to_bfloat16_simple():

    val1 = tf.constant( 1.063 , dtype=tf.float32 )
    val1 = tf.cast(val1, tf.bfloat16)
    
    val2 = tf.constant( 1.0063 , dtype=tf.float32 )
    val2 = tf.cast(val2, tf.bfloat16)
    
    val3 = tf.constant( 1.63 , dtype=tf.float32 )
    val3 = tf.cast(val3, tf.bfloat16)
    
    val4 = tf.constant( 1.000063 , dtype=tf.float32 )
    val4 = tf.cast(val4, tf.bfloat16)


# test the transformation between float32 and bfloat16 in small range
def test_float32_to_bfloat16_small_range():
    outputFile = open(dir1,'w')
    
    for i in numpy.arange(0.12, 20.0, 3.0):
      val1 = tf.constant( i , dtype=tf.float32 )
      val1 = tf.cast(val1, tf.bfloat16)
      outputFile.write(str(val1.numpy())+'\n')
    
    for i in numpy.arange(0.63, 20.0, 3.0):
      val2 = tf.constant( i , dtype=tf.float32 )
      val2 = tf.cast(val2, tf.bfloat16)
      outputFile.write(str(val2.numpy())+'\n')
      
    for i in numpy.arange(0.432, 200.0, 3.0):
      val3 = tf.constant( i , dtype=tf.float32 )
      val3 = tf.cast(val3, tf.bfloat16)
      outputFile.write(str(val3.numpy())+'\n')
    
    for i in numpy.arange(0.736, 200.0, 3.0):
      val4 = tf.constant( i , dtype=tf.float32 )
      val4 = tf.cast(val4, tf.bfloat16)
      outputFile.write(str(val4.numpy())+'\n')
  
    outputFile.close()
    
# test the transformation between float32 and bfloat16 in large range
def test_float32_to_bfloat16_large_range():
    outputFile = open(dir2,'w')
    
    for i in numpy.arange(0.12, 1000.0, 34.0):
      val1 = tf.constant( i , dtype=tf.float32 )
      val1 = tf.cast(val1, tf.bfloat16)
      outputFile.write(str(val1.numpy())+'\n')
    
    for i in numpy.arange(0.63, 1000.0, 47.0):
      val2 = tf.constant( i , dtype=tf.float32 )
      val2 = tf.cast(val2, tf.bfloat16)
      outputFile.write(str(val2.numpy())+'\n')
      
    for i in numpy.arange(0.432, 2000.0, 97.0):
      val3 = tf.constant( i , dtype=tf.float32 )
      val3 = tf.cast(val3, tf.bfloat16)
      outputFile.write(str(val3.numpy())+'\n')
    
    for i in numpy.arange(0.736, 5000.0, 106.0):
      val4 = tf.constant( i , dtype=tf.float32 )
      val4 = tf.cast(val4, tf.bfloat16)
      outputFile.write(str(val4.numpy())+'\n')
  
    outputFile.close()
    
# test the subtraction between bfloat16
def test_bfloat16_subtraction():
    outputFile = open(dir_sub,'w')
    cnt = 0.0
    while(cnt < 1000):
      val1 = (0.63 + cnt)*2.3;
      val2 = (0.37 + cnt)
      val1 = tf.constant( val1 , dtype=tf.float32 )
      val1 = tf.cast(val1, tf.bfloat16)
      val2 = tf.constant( val2 , dtype=tf.float32 )
      val2 = tf.cast(val2, tf.bfloat16)
      res = tf.math.subtract(val1, val2)
      outputFile.write(str(val1.numpy()))
      outputFile.write(" - ");
      outputFile.write(str(val2.numpy()));
      outputFile.write(" = ");
      outputFile.write(str(res.numpy())+'\n');
      cnt += 12.5;
    outputFile.close()

# test the addition between bfloat16
def test_bfloat16_addition():
    outputFile = open(dir_add,'w')
    cnt = 0
    while(cnt < 1000):
      val1 = 0.325 + cnt;
      val2 = 0.872 + cnt;
      val1 = tf.constant( val1 , dtype=tf.float32 )
      val1 = tf.cast(val1, tf.bfloat16)
      val2 = tf.constant( val2 , dtype=tf.float32 )
      val2 = tf.cast(val2, tf.bfloat16)
      res = tf.math.add(val1, val2)
      outputFile.write(str(val1.numpy()))
      outputFile.write(" + ");
      outputFile.write(str(val2.numpy()));
      outputFile.write(" = ");
      outputFile.write(str(res.numpy())+'\n');
      cnt += 3.4;
    outputFile.close() 
    
# test the division between bfloat16
def test_bfloat16_division():
    outputFile = open(dir_divide,'w')
    cnt = 0
    val1 = 2.365 
    val2 = 1.748
    while(cnt < 1000):
      val1 = (cnt + val1);
      val2 = val2 + 1.0;
      v1 = tf.constant( val1 , dtype=tf.float32 )
      v1 = tf.cast(v1, tf.bfloat16)
      v2 = tf.constant( val2 , dtype=tf.float32 )
      v2 = tf.cast(v2, tf.bfloat16)
      res = tf.math.divide(v1, v2)
      outputFile.write(str(v1.numpy()))
      outputFile.write(" / ");
      outputFile.write(str(v2.numpy()));
      outputFile.write(" = ");
      outputFile.write(str(res.numpy())+'\n');
      cnt += 3.5;
    outputFile.close()
    
# test the multiplication between bfloat16
def test_bfloat16_multiply():
    outputFile = open(dir_multiply,'w')
    cnt = 0
    while(cnt < 50):
      val1 = 0.365 + cnt;
      val2 = 0.748 + cnt;
      val1 = tf.constant( val1 , dtype=tf.float32 )
      val1 = tf.cast(val1, tf.bfloat16)
      val2 = tf.constant( val2 , dtype=tf.float32 )
      val2 = tf.cast(val2, tf.bfloat16)
      res = tf.math.multiply(val1, val2)
      outputFile.write(str(val1.numpy()))
      outputFile.write(" * ");
      outputFile.write(str(val2.numpy()));
      outputFile.write(" = ");
      outputFile.write(str(res.numpy())+'\n');
      cnt += 1.4;
    outputFile.close()   

if __name__ == "__main__":  
  start_time = time.time()
  test_float32_to_bfloat16_small_range()
  test_float32_to_bfloat16_large_range()
  test_bfloat16_addition()
  test_bfloat16_subtraction()
  test_bfloat16_multiply()
  test_bfloat16_division()
  print(time.time() - start_time)
  
      
      
      
    