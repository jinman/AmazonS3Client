/*
    Write a string to an S3 object.

    Provide your AWS credentials for awsKeyID and awsSecKey.
    Provide a bucket name. 
    Provide a region. Do not use us-east-1/us-standard at this time. PDX or NRT is a safe choice.
    The client only supports text/plain.
*/

#include "application.h"
#include "AmazonS3Client/AmazonS3Client.h"
#include "AmazonS3Client/SparkAWSImplementations.h"
#include "AmazonS3Client/AWSFoundationalTypes.h"

/* AWS credentials */
const char* awsKeyID = "";
const char* awsSecKey = "";

/* Light the LED while a message is transmitted. */
int led = 13;

/* Device independent implementations required for AmazonS3Client to function. */
SparkHttpClient httpClient;
SparkDateTimeProvider dateTimeProvider;

AmazonS3Client client;
PutInput putInput;
ActionError actionError;

static const char* BUCKET_NAME = ""; // name of the S3 bucket e.g. 'abc' 
static const char* KEY_NAME = ""; // name of the s3 object e.g. 'file.txt'
static const char* AWS_REGION = "";  // us-west-2 etc please use regions other than us-east-1/us-standard
static const char* AWS_ENDPOINT = "amazonaws.com";

void loop() {
    /* Light up the LED. */
    digitalWrite(led, HIGH);
    Serial.println("Start Loop");

    MinimalString dateTime(dateTimeProvider.getDateTime());
    Serial.println(dateTime.getCStr());
    
    /* Text to store into the S3 object. */
    putInput.setBody(dateTime);

    PutOutput output = client.put(putInput, actionError);
    Serial.println(output.getId().getCStr());

    /* Finish loop and turn off the LED. */
    Serial.println("Finished loop");
    delay(1000);
    digitalWrite(led, LOW);
    delay(30000);
}

void setup() {
    /* Begin serial communication. */
    Serial.begin(9600);
    delay(2000);

    pinMode(led, OUTPUT);


    client.setAWSRegion(AWS_REGION);
    client.setAWSEndpoint(AWS_ENDPOINT);
    client.setAWSSecretKey(awsSecKey);
    client.setAWSKeyID(awsKeyID);
    client.setHttpClient(&httpClient);
    client.setDateTimeProvider(&dateTimeProvider);
    client.setBucket(BUCKET_NAME);
    client.setKey(KEY_NAME);
}

