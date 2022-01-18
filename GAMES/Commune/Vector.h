#ifndef VECTOR_H
#define VECTOR_H

struct Vector2u{
    private :
    unsigned int x;
    unsigned int y;



    public:

    Vector2u(unsigned int x = 0, unsigned int y = 0)
    {
        this->setX(x);
        this->setY(y);
    }
    unsigned int getX() const{return x;}
    void setX(unsigned int newX){x = newX;}

    unsigned int getY() const{return y;}
    void setY(unsigned int newY){y = newY;}


};

struct Vector2i{
    private :
    int x;
    int y;



    public:

    Vector2i( int x = 0,  int y = 0)
    {
        this->setX(x);
        this->setY(y);
    }
    int getX() const{return x;}
    void setX(int newX){x = newX;}

    int getY() const{return y;}
    void setY(int newY){y = newY;}
};

struct Vector2d{
private :
    double x;
    double y;



    public:
    Vector2d(double x = 0, double y = 0)
    {
        this->setX(x);
        this->setY(y);
    }
    double getX() const{return x;}
    void setX(double newX){x = newX;}

    double getY() const{return y;}
    void setY(double newY){y = newY;}
};

struct Vector2f{
    private :
    float x;
    float y;



    public:
    Vector2f(float x = 0, float y = 0)
    {
        this->setX(x);
        this->setY(y);
    }
    float getX() const{return x;}
    void setX(float newX){x = newX;}

    float getY() const{return y;}
    void setY(float newY){y = newY;}
};

#endif // VECTOR_H
