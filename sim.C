#include <iostream>
#include <vector>
#include <cmath>

class Body
{
    
    public:
    double Mass;  //in Kg
    double PosX;
    double PosY;
    double const GConst = 6.6743E-11;

    double VelX;
    double VelY;

    Body(double MyMass, double X,double  Y,double Vx, double Vy)
    {
        Mass = MyMass;
        PosX = X;
        PosY = Y;
        VelX = Vx;
        VelY = Vy;

    }

    double GetDistance(Body OtherBody)
    {
        // Get the distance between this body and a forgien body
        double disX2 = pow((PosX - OtherBody.PosX),2);
        double disY2 = pow((PosY - OtherBody.PosY),2);

        return pow((disX2 + disY2 ),0.5);
    }

    double CalculateVdotX(Body OtherBody)
    {  
        //Calculates the force on a body from One other body in the system.
        double xVdot = -(PosX - OtherBody.PosX)*(GConst * OtherBody.Mass)/pow(GetDistance(OtherBody),3);
        //cout << "Acel X : " << xVdot << endl;
        return xVdot;      
    }

    double CalculateVdotY(Body OtherBody)
    {  
        //Calculates the force on a body from One other body in the system.
        double yVdot = -(PosY - OtherBody.PosY)*(GConst * OtherBody.Mass)/pow(GetDistance(OtherBody),3);
        //cout << "Acel Y : " << yVdot << endl;
        return yVdot;      
    }

    void UpdateVelocity(Body OtherBody)
    {
        // Update the velocity of the body from the influence of another body.
        VelX = VelX + CalculateVdotX(OtherBody);
        //std::cout<<"Vel X: " << VelX << std::endl;
        VelY = VelY + CalculateVdotY(OtherBody);
        //std::cout<<"Vel Y: " <<  VelY << std::endl;
        //Run this on with all Other Bodies to Get resultant force.

    }

    void UpdatePosition(double timeStep = 1)
    {
        //update the position of X and Y by adding the distance traveled at velocity in timestep;
        PosX = PosX + VelX*timeStep;
        PosY = PosY + VelY*timeStep;
    }
};



int main()
{

    //Prepare the Bodies and the List of all

    double TimeStep = 1;
    int NumberOfTimeSteps = 365* 60*60*24;
    int CheckInTime = 60*60*24; // How frequently to print out the time passed, By default its a day.

    std::vector<Body> AllBodies; 

    Body Sun = Body(2E30,0.,0.,0.,0.);
    Body Mercury = Body(3.3E23,0,57E9,47.3E3 ,0);
    Body Venus = Body(4.8E24,0,108E9,35E3 ,0);
    Body Earth = Body(6E24,0,-150E9,-29782 ,0);
    Body Mars = Body(6.4E23,0,227E9,24E3 ,0);

    AllBodies.push_back(Sun);
    AllBodies.push_back(Mercury);
    AllBodies.push_back(Venus);
    AllBodies.push_back(Earth);
    AllBodies.push_back(Mars);



    //Loop through all Bodies and prepare the simulation

    for(int nT = 0; nT < NumberOfTimeSteps ; nT++)
    {
        for(int i =0; i < AllBodies.size(); i++)
            {
                for(int j = 0; j < AllBodies.size(); j++)
                {
                    if( i == j)
                    {
                        continue;
                    }
                    else
                    {
                        AllBodies[i].UpdateVelocity(AllBodies[j]);
                    }
                    
                }
                AllBodies[i].UpdatePosition();
            }

        if(nT % (60*60*24) == 0)
            {
                std::cout << "Time Passed :  " << TimeStep*nT / CheckInTime << " Days " << std::endl;
            }
    }
       
    






    return 1;
}