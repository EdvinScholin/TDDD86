/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/

      N       	brute [ms]      	sortering [ms]
 --------------------------------------------------------
    150		28		10
    200		73		33
    300		226		55
    400		526		82
    800		4033		319
   1600		32140		1211
   3200		För lång tid	4860
   6400				20750
  12800			87623


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: Vi tror att algoritmen har en värstafallstid i O(n⁴) komplexitet då det är är värstafallstiden för den fyrnästlade loopen.

Sortering: Vi tror att algoritmen har en värstafallstid i O(n²) komplexitet då det är
värstafallstiden för den tvånästlade loopen.
