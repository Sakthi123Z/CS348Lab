#include <stdio.h> // this is including the standard input/output library

// this is a function that finds and prints all valid scoring combinations for a given NFL score
void find_combinations(int score) {
    int td2 , td1 , td , fg , safety; // this is declaring variables for each type of scoring play
    for (td2 = 0 ; td2 <= score / 8; td2++) { // this is looping over possible counts of 8-point touchdowns (TD + 2pt)
        for (td1 = 0; td1 <= score / 7; td1++) { // this is looping over possible counts of 7-point touchdowns (TD + FG)
            for (td = 0; td <= score / 6; td++) { // this is looping over possible counts of 6-point touchdowns (TD only)
                for (fg = 0; fg <= score / 3; fg++) { // this is looping over possible counts of 3-point field goals
                    for (safety = 0; safety <= score / 2; safety++) { // this is looping over possible counts of 2-point safeties
                        int total = td2 * 8 + td1 * 7 + td * 6 + fg * 3 + safety * 2 ; // this is calculating the total score for this combination
                        if (total == score) { // this is checking if the total matches the target score
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td2, td1, td, fg, safety); // this is printing the valid scoring combination
                        }
                    }
                }
            }
        }
    }
}

// this is the main function where execution starts
int main() {
    int score; // this is declaring the score variable to hold user input
    printf("Add 0 or 1 to STOP\n"); // this is instructing the user how to stop the program
    while (1) { // this is starting an infinite loop 
        printf("Please Type the NFL score ... "); // this is prompting the user to input a score
        scanf("%d", &score); // this is reading the score from the user
        if (score <= 1) break; // this is stopping the loop if the score is 0 or 1
        if (score < 0) { // this is checking if the score is invalid (negative)
            printf("The Score is invalid. Please Type a positive number so > 0 .\n"); // this is printing an error for invalid input
            continue; // this is skipping the rest of the loop and prompting again
        }
        printf("The All possible combinations of scoring plays if a teams score is %d ...\n" , score); // this is showing which score we're evaluating
        find_combinations(score); // this is calling the function to compute and print combinations /...
        // ... 
    }
    return 0; // this is returning 0 to indicate the program ended successfully
} // And This is the final line ! a