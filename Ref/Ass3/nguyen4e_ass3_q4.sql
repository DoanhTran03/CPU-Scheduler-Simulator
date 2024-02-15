SELECT DISTINCT G1.crop, G1.Regionid
FROM Growscrops G1
WHERE EXISTS (
    SELECT *
    FROM Growscrops G2
    WHERE G1.crop = G2.crop
    AND G1.Regionid != G2.Regionid
);

SELECT DISTINCT G1.crop, G1.Regionid
FROM Growscrops G1
WHERE NOT EXISTS (
    SELECT *
    FROM Growscrops G2
    WHERE G1.crop = G2.crop
    AND G1.Regionid != G2.Regionid
);
