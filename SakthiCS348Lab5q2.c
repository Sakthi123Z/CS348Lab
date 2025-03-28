#include <stdio.h> // this is for input and output functions like printf and scanf
#include <stdlib.h> // this is for standard library functions (not used here but included)
#include <string.h> // this is for string functions like strcmp and strlen
#include <ctype.h> // this is for character functions like toupper and tolower

// this is the function to convert celsius to fahrenheit
float celsius_to_fahrenheit(float celsius) {
    return (9.0 / 5.0) * celsius + 32.0;
}

// this is the function to convert fahrenheit to celsius
float fahrenheit_to_celsius(float fahrenheit) {
    return (5.0 / 9.0) * (fahrenheit - 32.0);
}

// this is the function to convert celsius to kelvin
float celsius_to_kelvin(float celsius) {
    return celsius + 273.15;
}

// this is the function to convert kelvin to celsius
float kelvin_to_celsius(float kelvin) {
    return kelvin - 273.15;
}

// this is the function to convert fahrenheit to kelvin
float fahrenheit_to_kelvin(float fahrenheit) {
    return celsius_to_kelvin(fahrenheit_to_celsius(fahrenheit));
}

// this is the function to convert kelvin to fahrenheit
float kelvin_to_fahrenheit(float kelvin) {
    return celsius_to_fahrenheit(kelvin_to_celsius(kelvin)) ; 
}

// this is the function that prints a temperature category  based on celsius ... and this is based on the Canvas Things
void categorize_temperature(float celsius) {
    if (celsius < 0) {
        printf("Freezing\n");
        printf("Wear The heavy jacket(s).\n");
    } else if (celsius >= 0 && celsius < 10) {
        printf("Cold\n");
        printf("Wear The jacket\n");
    } else if (celsius >= 10 && celsius < 25) {
        printf("Comfortable\n");
        printf("Enjoy The weather\n");
    } else if (celsius >= 25 && celsius < 35) {
        printf("Hot\n");
        printf("Stay Hydrated and get water\n");
    } else {
        printf("Extreme Heat\n");
        printf("The Weather is too hot. Stay Inside ... .\n");
    }
}

// this is the function that converts a string to title case
void to_title_case(char *str) {
    if (str[0]) str[0] = toupper(str[0]); // this is capitalizing the first letter
    for (int i = 1; str[i]; i++) str[i] = tolower(str[i]); // this is making the rest lowercase
}

// this is the function that removes newline and trailing spaces from a string
void trim_newline(char *str) {
    int len = strlen(str); // this is getting the length of the string
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == ' ')) {
        str[len - 1] = '\0'; // this is replacing newline/space with null terminator
        len--; // this is decreasing the length
    }
}

int main() {
    float temperature; // this is the variable to store the input temperature
    char input_scale_str[25], target_scale_str[25]; // this is to store the input and target scale strings
    char input_scale, target_scale; // this is to store the final scale letters
    char repeat; // this is to store whether user wants to repeat

    do {
        printf("\nPlease Type the temperature value ... "); // this is prompting the user for temperature
        if (scanf("%f", &temperature) != 1) { // this is checking if a valid float was entered
            printf("Invalid Temperature input.\n");
            while (getchar() != '\n'); // this is clearing the input buffer
            continue; // this is skipping to the next iteration
        }
        while (getchar() != '\n'); // this is clearing any trailing newline

        printf("Please Choose the input scale (Celsius , Fahrenheit , or Kelvin) ... "); // this is prompting for input scale
        fgets(input_scale_str , sizeof(input_scale_str), stdin); // this is reading the input scale
        trim_newline(input_scale_str); // this is trimming newline or spaces
        to_title_case(input_scale_str); // this is formatting input scale to title case

        printf("Please Choose the target scale (Celsius , Fahrenheit , or Kelvin) ... "); // this is prompting for target scale
        fgets(target_scale_str, sizeof(target_scale_str), stdin); // this is reading the target scale
        trim_newline(target_scale_str); // this is trimming newline or spaces
        to_title_case(target_scale_str); // this is formatting target scale to title case

        if (strcmp(input_scale_str, "Celsius") == 0) {
            input_scale = 'C'; // this is setting the input scale to 'C'
        } else if (strcmp(input_scale_str, "Fahrenheit") == 0) {
            input_scale = 'F'; // this is setting the input scale to 'F'
        } else if (strcmp(input_scale_str, "Kelvin") == 0) {
            input_scale = 'K'; // this is setting the input scale to 'K'
        } else {
            printf("Invalid Input scale.\n"); // this is handling invalid scale input
            continue;
        }

        if (strcmp(target_scale_str, "Celsius") == 0) {
            target_scale = 'C'; // this is setting the target scale to 'C'
        } else if (strcmp(target_scale_str, "Fahrenheit") == 0) {
            target_scale = 'F'; // this is setting the target scale to 'F'
        } else if (strcmp(target_scale_str, "Kelvin") == 0) {
            target_scale = 'K'; // this is setting the target scale to 'K'
        } else {
            printf("Invalid Target scale.\n"); // this is handling invalid target input
            continue;
        }

        if (input_scale == 'K' && temperature < 0) {
            printf("Invalid Kelvin temperature (must be non-negative).\n"); // this is checking for valid kelvin
            continue;
        }

        float converted_temperature; // this is to store the converted value
        if (input_scale == target_scale) {
            printf("The first and target scales are the same.\n"); // this is when no conversion needed
            converted_temperature = temperature;
        } else if (input_scale == 'C') {
            converted_temperature = (target_scale == 'F') ? celsius_to_fahrenheit(temperature)
                                  : celsius_to_kelvin(temperature); // this is celsius to f or k
        } else if (input_scale == 'F') {
            converted_temperature = (target_scale == 'C') ? fahrenheit_to_celsius(temperature)
                                  : fahrenheit_to_kelvin(temperature); // this is fahrenheit to c or k
        } else if (input_scale == 'K') {
            converted_temperature = (target_scale == 'C') ? kelvin_to_celsius(temperature)
                                  : kelvin_to_fahrenheit(temperature); // this is kelvin to c or f
        }

        printf("\n--- Conversion Result ---\n"); // this is the section header
        printf("Converted Temperature: %.2f %s\n", converted_temperature, target_scale_str); // this is showing result

        float celsius_equiv = (target_scale == 'C') ? converted_temperature
                            : (target_scale == 'F') ? fahrenheit_to_celsius(converted_temperature)
                            : kelvin_to_celsius(converted_temperature); // this is converting to celsius for category

        printf("\n--- Temperature Category ---\n"); // this is showing category header
        categorize_temperature(celsius_equiv); // this is calling the category function

        printf("\nWould You like to convert another temperature? (Y/N): "); // this is asking to repeat
        scanf(" %c", &repeat); // this is reading user input
        repeat = toupper(repeat); // this is converting input to uppercase
        while (getchar() != '\n'); // this is clearing buffer

    } while (repeat == 'Y'); // this is looping if user enters y

    printf("\nThank You for using the Temperature Converter!\n"); // this is a goodbye message
    return 0; // this is end of the lab 9 
} // And This is the final line !