INSERT INTO GROWSCROPS (Ssn, Regionid, crop, Revenue) VALUES (10, 1, 'brocoli', NULL);

UPDATE Region
SET Cropbudget = 20
WHERE Regname = 'SWO';

INSERT INTO FARMER (Ssn, Name, Age, Regionid) VALUES (60, 'Mary Tama', 21, 2);

DELETE FROM GROWSCROPS WHERE Ssn = 20;