#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <string.h>
#include<iostream>

#define MAX_PH 5;//哲学家最大的人数


//哲学家的三种行为
void eating(int);

void thinking(int);

void hungry(int);


void take_forks(int);

void put_forks(int);

void philosopher(int i);