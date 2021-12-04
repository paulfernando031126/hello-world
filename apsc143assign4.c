//This program analyzes a reaction between ammonia and oxygen.

#include <stdio.h>
#include <math.h>

//Define the constant values in the program
#define K 0.0114
#define timeStep 0.01

int main(){

    //Let's declare the required variables as doubles, the decimal places required will be large and things will get
    //sticky as float variables might get narrowed to doubles.
    //The first variables we declare are all based on the provided equations [1] and [2] on the assignment sheet.
    //We also need variables for the user inputted initial concentrations of Ammonia and Oxygen
    //equation [1] = rate = K*[Ammonia]*[Oxygen]^2
    //equation [2] = rate = -[changeInConcentrationAmmonia]/4*time = -[changeInConcentrationOxygen]/3*time
    //equation [2 continued] = rate = [changeInConcentrationNitrogen]/2*time = [changeInConcentrationWater]/6*time
    //We also know that there are two constant values K - the rate constant as well as the time increment of 0.01s,
    //so we'll declare two const. variables as doubles in order to keep all the variables as the double type.
    //We also need to declare an iteration counter, i, in order to add the total times and can also be manipulated.
    //We will also need to declare a total time passed variable.
    //In order to calculate the average of water concentration, we will also need a variable to represent the sum of
    //the water concentration and the average of the water.
    double inlConcAmm, inlConcOxy, reacRate, curConcAmm, curConcOxy;
    //declare and initialize values that are initially at 0
    double concWat = 0;
    double concNit = 0;
    double i = 0;
    double timePassed;
    double avgWat;
    double sumWater = 0;

    //request user input for initial concentrations
    printf("Enter initial ammonia & oxygen concentrations:");
    scanf("%lf %lf", &inlConcAmm, &inlConcOxy);

    reacRate = K * inlConcAmm * pow(inlConcOxy, 2);

    //Update conc values with scanned values;
    curConcAmm = inlConcAmm;
    curConcOxy = inlConcOxy;

    //While loop will continuously calculate reaction rates and concentrations until the reaction rate drops
    //below 0.040mol/Ls. This way we can get a time value at that end point where it drops below 0.040.
    while (reacRate >= 0.04) {

        //This if statement could have been printed further down the actual loop, but it creates an error
        //of like 0.006mol/L, not sure why, since it works here I will leave it here.
        if(i == 38){
            printf("Concentration of ammonia after 0.38s = %0.3lf mol/L\n", curConcAmm);
        }

        //Update the iteration counter after every loop by one.
        i += 1;

        //compute the reaction rate with the initial concentrations
        reacRate = K * curConcAmm * pow(curConcOxy, 2);

        //Using the rate compute concentrations rearranging equation 2
        curConcAmm = curConcAmm + (-(reacRate*4*timeStep));
        curConcOxy = curConcOxy + (-(reacRate*3*timeStep));
        //These updated values are calculated and looped back into the reaction rate formula.

        //Compute the nitrogen and oxygen reaction using the updated reaction rate.
        concNit = concNit + (reacRate*2*timeStep);
        concWat = concWat + (reacRate*6*timeStep);

        //As part of computing the average water concentration we need the sum of the water concentration that needs
        //to be updated every iteration.
        sumWater += concWat;

    }

    //Using the iteration counter outside of the loop calculate the total time passed for the reaction
    //rate to drop below 50%
    timePassed = i*timeStep;

    //Calculate the average water
    avgWat = sumWater/i;

    //Using the available data we can print the next lines
    printf("%0.2lfs required for rate to drop below 0.040 mol/(L*s)\n", timePassed);
    printf("Concentration of nitrogen gas after %0.2lfs = %0.3lf mol/L\n", timePassed, concNit);
    printf("Average concentration of water after %0.2lfs = %0.3lf mol/L\n", timePassed, avgWat);

    //if statement to determine if the reaction has passed 50% completion at the time at which the reaction rate hits
    //0.040mol/Ls. We check if the reaction has passed 50% completion by checking whether either of the products
    //concentrations were 50% of their initial.
    if(curConcAmm < 0.5 * inlConcAmm){
        printf("Reaction has passed 50%% completion\n");
    }
    else{
        printf("Reaction has not passed 50%% completion\n");
    }



}
