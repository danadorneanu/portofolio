#define NUMBER '0'
#define NEG_NUMBER 'n'
#define ZERO_CONV 0.00000001

/* stack functions */
int getop (char []);
void push (double c);
double pop (void);

/* standard input/output functions */
int getch(void);
void ungetch(int); /* tare smekeră funcţia asta : 
                      face push la o valoare intr-un buffer 
                      pe care il imparte cu getch */


