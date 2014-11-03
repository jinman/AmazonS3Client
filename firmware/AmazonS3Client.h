#ifndef AMAZONS3CLIENT_H_
#define AMAZONS3CLIENT_H_

#include "AWSFoundationalTypes.h"
#include "AWSClient3.h"

class PutInput {
    MinimalString body;
public:
    PutInput();
    void setBody(MinimalString body);
    MinimalString getBody() const;
};

class PutOutput {
    MinimalString id;
public:
    PutOutput();
    void setId(MinimalString id);
    MinimalString getId() const;
};

class AmazonS3Client : public AWSClient3 {
public:
    AmazonS3Client();
    PutOutput put(PutInput input, ActionError &actionError);
};

#endif /* AMAZONS3CLIENT_H_ */
