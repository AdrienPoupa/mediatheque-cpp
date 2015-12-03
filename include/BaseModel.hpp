#ifndef BaseModel_hpp
#define BaseModel_hpp

class BaseModel {
    int _id = -1;
    
public:
    BaseModel();
    ~BaseModel();
    
    bool save();
    bool remove();
    
};

#endif