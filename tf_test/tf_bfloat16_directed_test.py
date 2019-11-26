import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
import tensorflow as tf
import numpy



# test the transformation between float32 and bfloat16
def test_float32_to_bfloat16_simple():

    val1 = tf.constant( 1.063 , dtype=tf.float32 )
    val1 = tf.cast(val1, tf.bfloat16)
    print(val1)
    
    val2 = tf.constant( 1.0063 , dtype=tf.float32 )
    val2 = tf.cast(val2, tf.bfloat16)
    print(val2)
    
    val3 = tf.constant( 1.63 , dtype=tf.float32 )
    val3 = tf.cast(val3, tf.bfloat16)
    print(val3)
    
    val4 = tf.constant( 1.000063 , dtype=tf.float32 )
    val4 = tf.cast(val4, tf.bfloat16)
    print(val4)


# test the transformation between float32 and bfloat16
def test_float32_to_bfloat16():
    outputFile = open('test1.txt','w')
     
    for i in numpy.arange(0.12, 20.0, 5.0):
      val1 = tf.constant( i , dtype=tf.float32 )
      val1 = tf.cast(val1, tf.bfloat16)
      outputFile.write('\n')
      outputFile.write(str(val1.numpy()))
    
    for i in numpy.arange(0.63, 20.0, 5.0):
      val2 = tf.constant( i , dtype=tf.float32 )
      val2 = tf.cast(val2, tf.bfloat16)
      outputFile.write('\n')
      outputFile.write(str(val2.numpy()))
      
    for i in numpy.arange(20.432, 130.0, 8.0):
      val3 = tf.constant( i , dtype=tf.float32 )
      val3 = tf.cast(val3, tf.bfloat16)
      outputFile.write('\n')
      outputFile.write(str(val3.numpy()))
    
    for i in numpy.arange(100.283, 1000.0, 33.0):
      val4 = tf.constant( i , dtype=tf.float32 )
      val4 = tf.cast(val4, tf.bfloat16)
      outputFile.write('\n')
      outputFile.write(str(val4.numpy()))
  
    outputFile.close()
    

if __name__ == "__main__":
  test_float32_to_bfloat16_simple()
      
      
      
    