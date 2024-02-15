/*Query 1*/
SELECT R.Fullname, R.RPHONE
FROM RCONTACT R, GROWSCROPS G
WHERE R.REGIONID = G.REGIONID AND G.CROP = 'potatoes';
/* Query result is given below as retrieved from Oracle Sqlplus

FULLNAME                  RPHONE
------------------------- ---------------
Southwest Ontario
Eastern Ontario           1(733)524-0100
Southeastern Ontario      1(877)633-2000

*/

/*Query 2*/
SELECT R.Regname, RC.Fullname, RC.RPHONE
FROM RContact RC, Region R, GROWSCROPS G
WHERE R.Regionid = G.Regionid
AND R.Regionid = RC.Regionid
GROUP BY R.Regname, RC.Fullname, RC.RPHONE
HAVING SUM(G.Revenue) > 10;
/* Query result is:

REGNAME         FULLNAME                  RPHONE
--------------- ------------------------- ---------------
SC              Southcentral Ontario      1(866)663 3161
EO              Eastern Ontario           1(733)524-0100
SWO             Southwest Ontario
SEO             Southeastern Ontario      1(877)633-2000


*/

/*Query 3*/
SELECT R.Regionid, COUNT(DISTINCT F.Ssn) As NumberofFarmer, COUNT(DISTINCT G.crop) As NumberofCrop, SUM(G.Revenue) As Total
FROM REGION R, GROWSCROPS G, FARMER F
WHERE R.Regionid = G.Regionid AND G.Ssn = F.Ssn
GROUP BY R.Regionid;
/* Query result is:

  REGIONID NUMBEROFFARMER NUMBEROFCROP      TOTAL
---------- -------------- ------------ ----------
         1              2            3       15.5
         2              1            1         11
         3              2            1       29.3
         4              1            1       10.3

*/
/*Query 4*/
SELECT DISTINCT F.Name As FarmerName, R.Regname As Regname
FROM REGION R, GROWSCROPS G, FARMER F
WHERE F.Ssn = G.Ssn AND G.Regionid = R.Regionid;
/*  Query result is:

FARMERNAME      REGNAME
--------------- ---------------
Ted Tam         SEO
Monica Kap      SWO
Peter Good      EO
Jobe Bata       SWO
Kate Lee        SC
Ted Tam         SC

*/
/*Query 5*/
SELECT DISTINCT G.crop, G.Regionid, R.Regname
FROM Growscrops G, Region R
WHERE G.Regionid = R.Regionid AND G.crop IN(SELECT G.crop
FROM Growscrops G
GROUP BY G.crop
HAVING COUNT(DISTINCT G.Regionid) = 1);


/*  Query result is:


CROP              REGIONID REGNAME
--------------- ---------- ---------------
carrots                  1 SWO
peas                     3 SC
corn                     1 SWO



*/

