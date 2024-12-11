//Desmos: https://www.desmos.com/calculator/rvyg5whraq  alpha trial iterations here 
#include <stdio.h>
#include <math.h>

// Custom formula
int day_cal(int d, int m, int y) {
    return (d + 2 * (m - 1) 
            + (int)floor(m / 2.0) 
            + (int)floor((m - 1.0) / 8.0) * (m % 2) 
            - (int)ceil((m - 2.0) / 12.0) 
            * (2 - ((1 + (int)pow(-1, (int)ceil((y % 4) / 4.0))) / 2) 
            + (1 - (1 + (int)pow(-1, (int)ceil((y % 400) / 400.0))) / 2) 
            * ((1 + (int)pow(-1, (int)ceil((y % 100) / 100.0))) / 2)) 
            + 5 * (((int)floor((y - 1.0) / 100.0)) % 4) 
            + 5 * (int)floor(((y - 1) % 100) / 4.0) 
            + (((y - 1) % 100) % 4)) % 7;
            
            // Return (0 = Sunday, 1= Monday, ..., 6 = Friday)
}

// Zeller's Congruence
int zeller_day(int d, int m, int y) {
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int K = y % 100; // Year within the century
    int J = y / 100; // Century
    int h = (d + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) - 2 * J) % 7;

    // Adjust to match custom formula (0 = Sunday, ..., 6 = Saturday)
    return (h + 6) % 7;
}

int main() {
    // Test cases
    int dates[][3] = {
        {1, 1, 2000}, {29, 2, 2000}, {1, 3, 2000}, {15, 8, 1947}, 
        {26, 1, 1950}, {11, 12, 2024}, {4, 7, 1776}, {31, 12, 2999}, 
        {1, 1, 1900}, {29, 2, 1900}, {25, 12, 2023}, {1, 1, 2100}, 
        {28, 2, 2100}, {1, 3, 2100}, {31, 12, 9999}, {1, 1, 1000}, 
        {1, 1, 1600}, {29, 2, 1600}, {28, 2, 1700}, {1, 1, 1800}, 
        {31, 12, 1999}, {1, 1, 2024}, {29, 2, 2024}, {1, 3, 2024}
    };

    int n = sizeof(dates) / sizeof(dates[0]);

    printf("Comparing day_cal and zeller_day:\n");
    printf("Date\t\tCustom Formula\tZeller's Congruence\tMatch?\n");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int d = dates[i][0];
        int m = dates[i][1];
        int y = dates[i][2];

        int day1 = day_cal(d, m, y);
        int day2 = zeller_day(d, m, y);

        printf("%02d-%02d-%04d\t%10d\t%10d\t\t%s\n", d, m, y, day1, day2, (day1 == day2 ? "Yes" : "No"));
    }

    return 0;
}
