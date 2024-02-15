INSERT INTO FARMER (Ssn, Name, Age, Regionid) VALUES (10, 'Jobe Bata', 65, 1);
INSERT INTO FARMER (Ssn, Name, Age, Regionid) VALUES (20, 'Monica Kap', 80, 1);
INSERT INTO FARMER (Ssn, Name, Age, Regionid) VALUES (30, 'Peter Good', 22, 2);
INSERT INTO FARMER (Ssn, Name, Age, Regionid) VALUES (40, 'Kate Lee', 47, 3);
INSERT INTO FARMER (Ssn, Name, Age, Regionid) VALUES (50, 'Ted Tam', 50, 4);

INSERT INTO REGION (Regionid, Regname, Cropbudget, managerid) VALUES (1, 'SWO', 5.00, 10);
INSERT INTO REGION (Regionid, Regname, Cropbudget, managerid) VALUES (2, 'EO', 4.00, 10);
INSERT INTO REGION (Regionid, Regname, Cropbudget, managerid) VALUES (3, 'SC', 9.00, 50);
INSERT INTO REGION (Regionid, Regname, Cropbudget, managerid) VALUES (4, 'SEO', 6.00, 50);

INSERT INTO RCONTACT (Regionid, Fullname, RPhone) VALUES (1, 'Southwest Ontario', NULL);
INSERT INTO RCONTACT (Regionid, Fullname, RPhone) VALUES (2, 'Eastern Ontario', '1(733)524-0100');
INSERT INTO RCONTACT (Regionid, Fullname, RPhone) VALUES (3, 'Southcentral Ontario', '1(866)663 3161');
INSERT INTO RCONTACT (Regionid, Fullname, RPhone) VALUES (4, 'Southeastern Ontario', '1(877)633-2000');

INSERT INTO Growscrops (Ssn, Regionid, crop, Revenue) VALUES (10, 1, 'corn', 2.50);
INSERT INTO Growscrops (Ssn, Regionid, crop, Revenue) VALUES (10, 1, 'carrots', 4.00);
INSERT INTO Growscrops (Ssn, Regionid, crop, Revenue) VALUES (20, 1, 'potatoes', 9.00);
INSERT INTO Growscrops (Ssn, Regionid, crop, Revenue) VALUES (30, 2, 'potatoes', 11.00);
INSERT INTO Growscrops (Ssn, Regionid, crop, Revenue) VALUES (40, 3, 'peas', 15.30);
INSERT INTO Growscrops (Ssn, Regionid, crop, Revenue) VALUES (50, 4, 'potatoes', 10.30);
INSERT INTO Growscrops (Ssn, Regionid, crop, Revenue) VALUES (50, 3, 'peas', 14.00);
