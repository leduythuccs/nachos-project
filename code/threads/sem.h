// #include "synch.h"

class Sem {
   private:
    char name[50];
    Semaphore* sem;

   public:
    Sem(char* na, int i);
    ~Sem();

    void wait();

    void signal();

    char* GetName();
};