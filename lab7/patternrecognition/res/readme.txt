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
   3200		257120 (u)	4860
   6400		2056960 (u)	20750
  12800	16455680 (u)	87623

u = uppskattning

/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: Vi tror att algoritmen har en värstafallstid i O(n⁴) komplexitet då det är är värstafallstiden för den fyrnästlade loopen. På ungefär detta sätt kommer kan komplexiteten beräknas (n-1)(n-2-i)(n-1-i-j)(n-i-j-k) vilket ger O(n⁴).

Sortering: Vi tror att algoritmen har en värstafallstid i O(n²log(n)) komplexitet. Det beror på att värstafallstiden att sätta in i en map blir O(log(n)) på grund av sorteringen och i den tvånästlade loopen från den värstafallstiden O(n²). 
