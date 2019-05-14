#ifndef INTRP_H_INCLUDED
#define INTRP_H_INCLUDED
//Statistics library

double ILB(double x,double x1,double x2,double y1,double y2){//Interpolación lineal bidimensional
    //DBG
    //std::cout<<"x: "<<x<<" x_1: "<<x1<<" x_2: "<<x2<<" y_1: "<<y1<<" y_2: "<<y2<<std::endl;
    //DBG

    double y=0;
    
    if(x2-x1!=0){
    y=(((x-x1)/(x2-x1))*(y2-y1))+y1;
    return y;
}
    else
    return y1;//If the interpolation is betwen de same x1 and x2 coordinate, it returns the y1 value
        
}



#endif
