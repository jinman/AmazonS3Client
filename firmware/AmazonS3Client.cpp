#include "AWSFoundationalTypes.h"
#include "AWSClient3.h"
#include "AmazonS3Client.h"
#include "Utils.h"
#include <stdlib.h>

static const char* SERVICE = "s3";
static const char* CONTENT_TYPE = "text/plain";
int EXTRACTED_TIMESTAMP_BUFFER_LENGTH = 20;
int FORMATTED_TIMESTAMP_BUFFER_LENGTH = 15;
int MESSAGEID_BUFFER_LENGTH = 1024;

PutOutput::PutOutput() {

}

void PutOutput::setId(MinimalString id) {
    this->id = id;
}

MinimalString PutOutput::getId() const {
    return this->id;
}

PutInput::PutInput() {

}

void PutInput::setBody(MinimalString body) {
    this->body = body;
}

MinimalString PutInput::getBody() const {
    return this->body;
}

AmazonS3Client::AmazonS3Client() : AWSClient3() {
    awsService = SERVICE;
}

PutOutput AmazonS3Client::put(PutInput input, ActionError &actionError) {
    PutOutput output;
    actionError = NONE_ACTIONERROR;
    contentType = CONTENT_TYPE;
    
    MinimalString payload = input.getBody();

    char* request = createRequest(payload);
    char* response = sendData(request);

    delete[] request;
    
    if (response == NULL) {
        actionError = CONNECTION_ACTIONERROR;
        return output;
    }

    int httpStatusCode = findHttpStatusCode(response);
    if (httpStatusCode == 200) {
        char* msgidIdx = strstr(response, "x-amz-id-2: ");
        int msgidPos = msgidIdx - response;

        char* msgid = new char[MESSAGEID_BUFFER_LENGTH]();
        strncpy(msgid, response + msgidPos + 12, MESSAGEID_BUFFER_LENGTH - 1);
        msgid[MESSAGEID_BUFFER_LENGTH - 1] = '\0';
        
        output.setId(msgid);
        return output;
    }

    if (httpStatusCode == 403) {
        char* ts = strstr(response, "<ServerTime>");
        int pos = ts - response;
        
        char* newts = new char[EXTRACTED_TIMESTAMP_BUFFER_LENGTH]();
        strncpy(newts, response + pos + 12, EXTRACTED_TIMESTAMP_BUFFER_LENGTH - 1);
        newts[19] = '\0';

        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;

        char buffer[5];
        sprintf(buffer, "%.4s", newts);
        year = atoi(buffer);
        sprintf(buffer, "%.2s", newts + 5);
        month = atoi(buffer);
        sprintf(buffer, "%.2s", newts + 8);
        day = atoi(buffer);
        sprintf(buffer, "%.2s", newts + 11);
        hour = atoi(buffer);
        sprintf(buffer, "%.2s", newts + 14);
        minute = atoi(buffer);
        sprintf(buffer, "%.2s", newts + 17);
        second = atoi(buffer);

        char* time = new char[FORMATTED_TIMESTAMP_BUFFER_LENGTH]();
        sprintf(time, "%.4d%.2d%.2d%.2d%.2d%.2d", year, month, day, hour, minute, second);
        dateTimeProvider->sync(time);
    }

    return output;
}
