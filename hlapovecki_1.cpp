#include "TXlib.h"


//printf ("\n ax= %d", (*ax));
void boy      (int x, int y, double size,  double rglaz,   double rot, double ylybka, int t);
void boygo2   (int x, int y, int z, double size, double rglaz, double rot, double ylybka);
void fon      ();
void boyright (int* x, int* y, int *vx, int *vy, int *dt, int *ax, int *ay, int *t);
void boll     (int x,   int y);
void bollgo   (int *x, int *y, int *vx, int *vy, int *dt, int *ax, int *ay, int *t);
void control  (int *x, int *y, int *vx, int *vy, int *dt, int *ax, int *ay, int *t);
void prugup   (int *x, int *y, int *vx, int *vy, int *dt, int *ax, int *ay, int *t);
void formyladv (int *x, int *y, int *vx, int *vy, int *dt, int *ax, int *ay);
int main ()
    {
     int dt = 1;
     int vx = 0;
     int vy = 0;
     int x  = 100;
     int y  = 100;
     int ax = 0;
     int ay =  0;
     int t  =  1;

     txCreateWindow (1440, 900);
     fon ();
     boyright (&x, &y, &vx, &vy, &dt, &ax, &ay, &t);

     return 0;
    }

//-----------------------------------------------------------------------------
void boy (int x, int y, double size, double rglaz, double rot, double ylybka, int t)
   {
   txSetColor (TX_BLACK, 2);
   txSetFillColor (RGB (213, 172, 129));
   txCircle (x, y, 60 / size);

   txLine (x , y +  60 / size, x,                                y + 300 / size);
   txLine (x , y +  85 / size, x - 70 / size + 9 * (t%3) / size, y + 200 / size);
   txLine (x , y +  85 / size, x + 70 / size + 9 * (t%3) / size, y + 200 / size);
   txLine (x , y + 300 / size, x - 70 / size + 9 * (t%3) / size, y + 450 / size);
   txLine (x , y + 300 / size, x + 70 / size + 9 * (t%3) / size, y + 450 / size);

   txLine   (x - 25 / rot, y + 20 / ylybka, x + 25 / rot, y + 20 / ylybka);

   txSetColor (TX_BLACK);
   txSetFillColor (TX_BLACK);
   txCircle (x - 25 / size, y - 10 / size, 3 / rglaz);
   txCircle (x + 25 / size, y - 10 / size, 3 / rglaz);

    }

//-----------------------------------------------------------------------------
void fon ()
    {
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 1440, 900);
    }
//-----------------------------------------------------------------------------
void boyright (int* x, int* y, int *vx, int *vy, int *dt, int *ax, int *ay, int *t)
    {
     while (!txGetAsyncKeyState (VK_ESCAPE))

        {
         txClear ();
         fon     ();
         boy     (*x, *y, 3, 1, 2, 2, *t);

         formyladv (x, y, vx, vy, dt, ax, ay);
         control (x, y, vx, vy, dt, ax, ay, t);

         if (txGetAsyncKeyState (VK_SPACE)) prugup (x, y, vx, vy, dt, ax, ay, t);

         txSleep (33);

        }
    }

//-----------------------------------------------------------------------------
void control  (int *x, int *y, int *vx, int *vy, int *dt, int *ax, int *ay, int *t)
   {
   if (txGetAsyncKeyState ('D')) (*ax)++, (*t)++;
   if (txGetAsyncKeyState ('A')) (*ax)--, (*t)++;
   if (txGetAsyncKeyState ('W')) (*ay)--;
   if (txGetAsyncKeyState ('S')) (*ay)++;

   if (!txGetAsyncKeyState ('D') && !txGetAsyncKeyState ('A')) (*ax) = 0, (*t) = 1;
   if (!txGetAsyncKeyState ('S') && !txGetAsyncKeyState ('W') && !txGetAsyncKeyState (VK_SPACE)) (*ay) = 0;

   if (!txGetAsyncKeyState ('D') && !txGetAsyncKeyState ('A')) (*vx) = 0;
   if (!txGetAsyncKeyState ('S') && !txGetAsyncKeyState ('W') && !txGetAsyncKeyState (VK_SPACE)) (*vy) = 0;

   if (*x > 1400)          *vx = -(*vx);
   if (*x <   40)          *vx = -(*vx);
   if (*y <   10)          *vy = +1;
   if (*y >= 745)          *vy = -1;
   }


//-----------------------------------------------------------------------------
void prugup (int *x, int *y, int *vx, int *vy, int *dt, int *ax, int *ay, int *t)
    {
    int r = 0;

    if (*y > 70)
      {
        while (r < 15)
           {
            txClear();
            fon ();
            formyladv (x, y, vx, vy, dt, ax, ay);
            control   (x, y, vx, vy, dt, ax, ay, t);
            boy (*x, *y, 3, 1, 2, 2, *t);
            (*y)-= 10;
            txSleep (25);
            r++;
            }

            r=0;

            while (r < 15)
               {
                txClear();
                fon ();
                formyladv (x, y, vx, vy, dt, ax, ay);
                control (x, y, vx, vy, dt, ax, ay, t);
                boy (*x, *y, 3, 1, 2, 2, *t);
                (*y)+= 10;
                txSleep (25);
                r++;
                }
       }
    }


//-----------------------------------------------------------------------------
void formyladv (int *x, int *y, int *vx, int *vy, int *dt, int *ax, int *ay)
   {
     *x  = *x  +  *vx * (*dt);
     *y  = *y  +  *vy * (*dt);
     *vx = *vx + (*ax) * (*dt);
     *vy = *vy + (*ay) * (*dt);

     if (*ax, *vx * (*dt) >  5) *ax =  5, *vx =  5;
     if (*ax, *vx * (*dt) < -5) *ax = -5, *vx = -5;
     if (*ay, *vy * (*dt) >  5) *ay =  5, *vy =  5;
     if (*ay, *vy * (*dt) < -5) *ay = -5, *vy = -5;

    }







