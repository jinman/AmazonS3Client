# Version 1 of the Experimental AWS SDK for Arduino

An experimental SDK for contacting AWS Services on Arduino-compatible devices. 

##Step 1: Create Amazon S3 Bucket

##Step 2: Create an IAM User with permission to write to this S3 bucket. Also note down the user's AccessKey and SecretKey. 

##Step 3: Edit S3 bucket ACL/ Policy to allow IAM user to write 

##Step 4: Import AmazonS3Client Contributed Library

Sketch > Contributed Libraries "AmazonS3Client"

##Step 5: Open the sample application 

Load the .ino or application.cpp file

##Step 6: Enter the AccessKey and SecretKey in the application file

##Step 7: Enter the bucket name, key name and region in the application file

##Step 8: Verify, Compile and Upload

Wire your connected device. After the wiring is finished, you should be able to connect two cables to your computer via usb, compile and upload the code with the Arduino IDE. 
