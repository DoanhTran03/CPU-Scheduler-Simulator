delete from GROWSCROPS;
delete from RCONTACT;
delete from REGION;
delete from FARMER;
commit;

drop table GROWSCROPS cascade constraints;
drop table RCONTACT cascade constraints;
drop table REGION cascade constraints;
drop table FARMER cascade constraints;
commit;
