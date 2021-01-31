#include<iostream>
#include<cmath>
using namespace std;

double cal_height(double time_range[], double height, double coeff_of_restitution, float gravity, int array_size)
{
    double obj_height,cal_part_1,cal_part_2,V0,time,epsilon = 0.000000001,diff;
    int r1,r2,tr=0;
    cout << "Enter time (in sec) to find height of the object:\n";
    cin >> time;

    while(tr+1 < array_size) //to find tr < time <tr+1
    {
        diff = (time*time-time_range[tr]*time_range[tr])/(time+time_range[tr]);
        if (floor(diff) == 0)
        {
            r1 = tr;
            obj_height = 0;
        }
        else if(time_range[tr] < time && time < time_range[tr+1])
        {
            r1 = tr;
            r2 = tr+1;
            break;
        }
        tr++; 
    }
    if(diff < epsilon)
    {
        cout << "Object height at time: "<< time << " seconds is:\t" << obj_height << " meter";
    }
    else if (0 < time && time < time_range[0]) // for 0 <time <t0;
    {

        obj_height = height - (gravity * pow(time,2)/2);
        cout << "Object height at time: "<< time << " seconds is:\t" << obj_height << " meter";

    }
    else if (time_range[r1] < time && time < time_range[r2]) //for tr < time <tr+1
    {

        V0 = sqrt(2*height*gravity);
        cal_part_1 = pow(coeff_of_restitution,r2)*(time-time_range[r1])*V0;
        cal_part_2 = (gravity*pow((time-time_range[r1]),2))/2;
        obj_height =  cal_part_1 - cal_part_2;
        cout << "Object height at time: "<< time << " seconds is:\t" << obj_height<< " meter";

    }
    else //for time > tr
    {
        cout << "Entered time is out of range, Object may be at rest!";
    }
    
    return 0;   
}

double timerange(double height, double coeff_of_restitution)
{   
    double cal_part_1,cal_part_2;
    int r=100; // Default time range, t0 to t100
    float gravity = 9.8; //meter/sec
    double time_range[r];
    {
        for(int tr=0;tr<r;tr++)
        {
            cal_part_1 = sqrt((2*height)/gravity);
            cal_part_2 = (2*coeff_of_restitution*(1-pow(coeff_of_restitution,tr))/(1-coeff_of_restitution));
            time_range[tr] = cal_part_1*(1+cal_part_2);
        }
    }
    cal_height(time_range,height,coeff_of_restitution,gravity,r);
    return 0;
}

int main()
{
    double height,coeff_of_restitution;
    bool val_check=true;
    cout << "Enter Value of Coeff. of Restituion:\n";
    cin >> coeff_of_restitution;
    while(val_check)
    {
        if (coeff_of_restitution > 0 && coeff_of_restitution < 1)
        {
            val_check = false;
        }
        else
        {
            cout<< "Incorrect Value, Please Try Again\n";
            cout << "Enter Value of Coeff. of Restituion:\n";
            cin >> coeff_of_restitution;
        }
        
    }
    cout << "Enter height (in m) from which object is dropped:\n";
    cin >> height;

    timerange(height,coeff_of_restitution);
    
    return 0;
}